#include <stdio.h>
#include "model.h"
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

//主函数

int main(){
    FILE *fp1,*fp2;
    Node *p,*r;
    char ch1,ch2;
    Link l;
    bookLink k;
    book *t,*h;
    int sel;
    l=(Node*)malloc(sizeof(Node));
    l->next=NULL;
    r=l;
    k=(book*) malloc(sizeof (book));
    k->next=NULL;
    h=k;
    fp1= fdopen("f:\\train.txt","ab+");
    if(fp1==NULL)
    {
        printf("can't open the file!");
        return 0;
    }
    while (!feof(fp1))
    {
        p=(Node*) malloc(sizeof (Node));
        if (fread(p,sizeof (Node),1,fp1)==1)
        {
            p->next=NULL;
            r->next=p;
            r=p;
        }
    }
    fclose(fp1);
    fp2= fdopen("f:\\man.txt","ab+");
    if(fp2==NULL)
    {
        printf("can't opem the file!");
        return 0;
    }
    while (!feof(fp2))
    {
        t = (book*) malloc(sizeof (book));
        if (fread(t,sizeof (book),1,fp2)==1)
        {
            t->next=NULL;
            h->next=t;
            h=t;
        }
    }
    fclose(fp2);
    while (1)
    {
        system("CLS");
        menu();
        printf("\tplease choose(0~6)");
        scanf("%d",&sel);
        system("CLS");
        if(sel==0)
        {
            if(saveflag==1)
            {
                getchar();
                printf("\nthe file have been changed! do you want to save it (y/n)?\n ");
                scanf("%c",&ch1);
                if(ch1=="y"||ch1=="y");
                {
                    SaveBookinfo(k);
                    SaveTrainlnfo(l);
                }
            }
            printf("\nThank you are welcome too");
            break;
        }
    }
    switch (sel) {
        case 1:
            Traininfo(l);
            break;
        case 2:
            Searchtrain(l);
            break;
        case 3:
            B00kticket(l,k);
            break;



    }
};
