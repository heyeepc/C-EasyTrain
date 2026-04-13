#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h> // 用于 getch()
#include "model.h"

int saveflag = 0; // 全局变量定义

void menu()
{
    puts("\n\n");
    puts("\t\t---------------------------------------------------------------------|");
    puts("\t\t|                             Booking Tickets                          ");
    puts("\t\t|                 0:quit the system                                   |");
    puts("\t\t|                 1:insert a train information                         |");
    puts("\t\t|                 2:search a train information                         |");
    puts("\t\t|                 3:Book a train ticket                                |");
    puts("\t\t|                 4:Modify the train information                       |");
    puts("\t\t|                 5:Show the train information                         |");
    puts("\t\t|                 6:save information                                   |");
    puts("\t\t|----------------------------------------------------------------------|");
}

void Traininfo(Link linkhead) {
    Node *p, *r;
    char num[10];
    r = linkhead;
    while (r->next != NULL) r = r->next; // 移到链表末尾

    while (1) {
        printf("Input train number (0-return): ");
        scanf("%s", num);
        if (strcmp(num, "0") == 0) break;

        // 查重逻辑
        Node *s = linkhead->next;
        int exists = 0;
        while (s) {
            if (strcmp(s->data.num, num) == 0) {
                printf("Error: Train %s already exists!\n", num);
                exists = 1;
                break;
            }
            s = s->next;
        }
        if (exists) continue;

        p = (Node *)malloc(sizeof(struct train));
        strcpy(p->data.num, num); // 修正拼写和参数

        printf("Start City: "); scanf("%s", p->data.startcity);
        printf("Reach City: "); scanf("%s", p->data.reachcity);
        printf("Takeoff Time: "); scanf("%s", p->data.takeofftime);
        printf("Price: "); scanf("%d", &p->data.price); // 必须是 %d 和 &
        printf("Tickets: "); scanf("%d", &p->data.ticketnum);

        p->next = NULL;
        r->next = p;
        r = p;
        saveflag = 1;
    }
}

void printheader() {
    printf(HEADER1); // 这里的 HEADER1 展开后自带引号
    printf(HEADER2);
}

void printdata(Node *p) {
    // DATA 宏会自动展开为 p->data.num, p->data.startcity...
    printf(FORMAT, DATA);
}

void searchtrain(Link l) {
    Node *p;
    char search_key[20];
    int sel, found = 0;

    if (l->next == NULL) {
        printf("\nThere is no record to search!\n");
        return;
    }

    printf("\nChoose search method:\n1: By Train Number\n2: By Start City\nYour choice: ");
    if (scanf("%d", &sel) != 1) {
        while (getchar() != '\n'); // 清理非法输入
        return;
    }

    if (sel == 1) {
        printf("Input the train number: ");
        scanf("%s", search_key);
    } else if (sel == 2) {
        printf("Input the start city: ");
        scanf("%s", search_key);
    } else {
        printf("Invalid choice!\n");
        return;
    }

    p = l->next;
    printheader(); // 先打印表头

    while (p != NULL) {
        int match = 0;
        if (sel == 1 && strcmp(p->data.num, search_key) == 0) match = 1;
        if (sel == 2 && strcmp(p->data.startcity, search_key) == 0) match = 1;

        if (match) {
            printdata(p);
            found++;
        }
        p = p->next;
    }

    if (found == 0) {
        printf("\nNo matching records found!\n");
    } else {
        printf("\nTotal %d records found.\n", found);
    }
}

void Bookticket(Link l, bookLink k) {
    Node *r[10], *p;
    char ch[10], tnum[10], str[10], str1[10], str2[10]; // 扩大ch数组防止溢出
    book *q, *h;
    int i = 0, t = 0, flag = 0, dnum;

    q = k;
    while (q->next != NULL) q = q->next;

    printf("input the city you want to go: ");
    scanf("%s", str);

    // 1. 查找匹配的车次
    p = l->next;
    while (p != NULL) {
        if (strcmp(p->data.startcity, str) == 0) {
            if (i < 10) { // 防止数组越界
                r[i] = p;
                i++;
            }
        }
        p = p->next;
    }

    // 2. 检查是否找到
    if (i == 0) {
        printf("\nSorry! Can't find the train for you!\n");
        return; // 直接返回
    }

    // 3. 打印查询到的结果
    printf("\n\nThe number of records found: %d\n", i);
    printheader();
    for (t = 0; t < i; t++) {
        printdata(r[t]);
    }

    // 4. 询问是否订票
    printf("\nDo you want to book a ticket? (y/n): ");
    scanf("%s", ch); // 使用%s更稳健

    if (strcmp(ch, "y") == 0 || strcmp(ch, "Y") == 0) {
        h = (book*)malloc(sizeof(book));
        printf("input your name: ");
        scanf("%s", str1);
        strcpy(h->data.name, str1);

        printf("input your ID: ");
        scanf("%s", str2);
        strcpy(h->data.num, str2);

        printf("please input the number of the train: ");
        scanf("%s", tnum);

        // 5. 在查找到的数组中匹配具体的车次
        flag = 0; // 重置标记
        for (int j = 0; j < i; j++) { // 使用不同的计数器 j
            if (strcmp(r[j]->data.num, tnum) == 0) { // 注意：这里应该是对比车次号
                flag = 1;
                if (r[j]->data.ticketnum < 1) {
                    printf("Sorry, no ticket available!\n");
                    free(h); // 释放未使用的内存
                    return;
                }

                printf("input the number of tickets to book: ");
                scanf("%d", &dnum);

                if (dnum > r[j]->data.ticketnum) {
                    printf("Not enough tickets!\n");
                } else {
                    r[j]->data.ticketnum -= dnum;
                    h->data.bookNum = dnum;
                    h->next = NULL;
                    q->next = h;
                    q = h;
                    printf("\nLucky! You have booked a ticket.");
                    saveflag = 1;
                }
                break; // 找到并处理后退出循环
            }
        }

        if (flag == 0) {
            printf("Train number error or not in the list!\n");
            free(h);
        }
    }
    printf("\nPress any key to continue...");
    getch();
}

void Modify(Link l) {
    Node *p;
    char tnum[10];
    char ch;

    p = l->next;

    if (!p) {
        printf("\nThere is no record to modify!\n");
        return;
    }

    printf("\nDo you want to modify a record? (y/n): ");
    scanf(" %c", &ch);

    if (ch != 'y' && ch != 'Y') {
        return;
    }

    printf("\nInput the train number you want to modify: ");
    scanf("%9s", tnum);

    // 查找目标节点
    while (p != NULL) {
        if (strcmp(p->data.num, tnum) == 0) {
            break;
        }
        p = p->next;
    }

    if (p == NULL) {
        printf("\nCan't find the record!\n");
        return;
    }

    // 找到了，开始修改
    printf("\n--- Modify Train Info ---\n");

    printf("New train number: ");
    scanf("%9s", p->data.num);

    printf("New start city: ");
    scanf("%9s", p->data.startcity);

    printf("New reach city: ");
    scanf("%9s", p->data.reachcity);

    printf("New takeoff time: ");
    scanf("%9s", p->data.takeofftime);

    printf("New receive time: ");
    scanf("%9s", p->data.receivetime);

    printf("New price: ");
    scanf("%d", &p->data.price);

    printf("New ticket number: ");
    scanf("%d", &p->data.ticketnum);

    saveflag = 1;

    printf("\nModify success!\n");
}

void showtrain(Link l) {
    Node *p;
    p=l->next;
    printheader();
    if (l->next == NULL)
        printf("no records!");
    else
        while (p != NULL) {
            printdata(p);
            p = p->next;
            }

}

void SaveTrainlnfo(Link l) {
    FILE *fp;
    Node *p;
    int count = 0;

    // 使用 "wb" (二进制写入) 模式
    fp = fopen("train.txt", "wb");
    if (fp == NULL) {
        printf("\nError: The file 'train.txt' could not be opened for writing!\n");
        return;
    }

    p = l->next;
    while (p != NULL) {
        // 【关键改动】只写入 struct train data 部分，不要写入整个 Node (含 next 指针)
        if (fwrite(&(p->data), sizeof(struct train), 1, fp) == 1) {
            count++;
            p = p->next;
        } else {
            printf("\nError occurred while writing to file!\n");
            break;
        }
    }

    fclose(fp);
    printf("\nSuccessfully saved %d train records!\n", count);
    saveflag = 0; // 保存后重置修改标记
}

void SavaBooklnfo(bookLink k) {
    FILE *fp;
    book *p;
    int count = 0,flag = 1;
    fp = fopen("book.txt", "wb");
    if (fp == NULL) {
        printf("the flie can't be opened!");
        return;
    }
    p=k->next;
    while (p) {
        if (fwrite(p, sizeof(book), 1, fp) == 1) {
            p=p->next;
            count++;
        }
        else {
            flag = 0;
            break;
        }

    }
    if (flag) {
        printf("save %d book records!\n", count);
        saveflag = 0;
    }
    fclose(fp);
}

int main() {
    Node *p, *r;
    Link l;
    bookLink k;
    book *t, *h;
    int sel;

    // --- 初始化链表头结点 ---
    l = (Node*)malloc(sizeof(Node));
    l->next = NULL;
    r = l;

    k = (bookLink)malloc(sizeof(book));
    k->next = NULL;
    h = k;

    // --- 文件读取逻辑 (建议改用 fopen) ---
    FILE *fp1 = fopen("train.txt", "rb+");
    if (fp1 != NULL) {
        while (1) {
            p = (Node*)malloc(sizeof(Node));
            if (fread(p, sizeof(Node), 1, fp1) == 1) {
                p->next = NULL;
                r->next = p;
                r = p;
            } else {
                free(p);
                break;// 读取失败释放内存
            }
        }
        fclose(fp1);
    }

    // --- 主循环 ---
    while (1) {
        system("CLS");
        menu();
        printf("\tPlease choose (0~6): ");
        if (scanf("%d", &sel) != 1) { // 防止输入非数字导致死循环
            while (getchar() != '\n');
            continue;
        }
        system("CLS");

        if (sel == 0) {
            if (saveflag == 1) {
                char ch1;
                printf("\nFile changed! Save it? (y/n): ");
                scanf(" %c", &ch1); // 注意 %c 前有一个空格，用来消耗回车
                if (ch1 == 'y' || ch1 == 'Y') { // 必须用单引号
                   // SaveTrainInfo(l); // 确保函数名拼写一致
                   // SaveBookInfo(k);
                }
            }
            printf("\nThank you for using!\n");
            break;
        }

        // 将 switch 移入循环内部
        switch (sel) {
            case 1: Traininfo(l); break;
            case 2: searchtrain(l); break;
            case 3: Bookticket(l, k); break;
            case 5: showtrain(l); break;
            case 6: /* 执行保存逻辑 */; break;
            default: printf("Invalid choice!"); break;
        }
        printf("\nPress any key to continue...");
        getch();
    }
    return 0;
}
