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

        p = (Node *)malloc(sizeof(Node));
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

void searchtrain(Link I) {
    Node *s[10],*r;
    int sel,k,i=0;
    char str1[5],str2[10];
    if (!I->next) {
        printf("there is not any record!");
        return ;
    }
    printf("choose the way:\n1:according to the number of train ;\n2:according to the city \n ");
    scanf("%d",&sel);
    if (sel==1) {
        printf("input the number of the train :");
        scanf("%d",&str1);
        r=I->next;
        while (r!=NULL) {
            if (strcmp(r->data.num,str1)==0) {
                s[i]=r;
                i++;
                break;
            }
            else
                r=r->next;
        }
    }
    else if (sel==2) {
        printf("input the city you want to go: ");
        scanf("%s",str2);
        r=I->next;
        while (r!=NULL)
            if (strcmp(r->data.startcity,str2)==0) {
                s[i]=r;
                i++;
                r=r->next;
            }
            else
                r=r->next;
    }
    if (i==0)
        printf("can not find!");
    else {
        printheader();
        for (k=0;k<i;k++);
        printdata(s[k]);
    }
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
        while (!feof(fp1)) {
            p = (Node*)malloc(sizeof(Node));
            if (fread(p, sizeof(Node), 1, fp1) == 1) {
                p->next = NULL;
                r->next = p;
                r = p;
            } else {
                free(p); // 读取失败释放内存
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
           // case 3: B00kticket(l, k); break;
          //  case 5: showtrain(l); break;
            case 6: /* 执行保存逻辑 */; break;
            default: printf("Invalid choice!"); break;
        }
        printf("\nPress any key to continue...");
        getch();
    }
    return 0;
}


