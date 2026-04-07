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

void printheader() {
    printf(HEADER1);
    printf(HEADER2);
    printf(HEADER3);

}

void printdata( Node *Q) {
    Node*p;
    p=q;
    printf(FORMAT,DATA);
}

void Traininfo(Link linkhead)
{
    struct node *p ,*r ,*s;;
    char num[10];
    r = linkhead;
    s = linkhead->next;
    while (r->next!=NULL)
        r=r->next;
    while (1) {

        printf("please input the number of the train(0-return):");
        scanf("%s",num);
        if (strcmp(num,"0")==0)
            break;
        while (s) {
            if (strcmp(s->name,num)==0) {
                printf("the train ‘%s,is existing !\n",num);
                return;
            }
            s = s->next;
        }
        p = (struct node *)malloc(sizeof(struct node));
        strcpy(p->date,num,num);
        printf("input the clit where the train will start");
        scanf("%s",p->date.startcity);
        printf("input the city where the train will reach");
        scanf("%s",p->date.reachcity);
        printf("input the time which the train take off");
        scanf("%s",p->date.takeoffime);
        printf("input the time which the train erceive");
        scanf("%s",p->date.receivetime);
        printf("input the price of the train");
        scanf("%s",p->date.price);
        printf("input the number of booked tickets:");
        scanf("%d",&p->data.ticketnum);
        p->next=NULL;
        r->next=p;
        r=p;
        saveflag=1;
    }
}

void searchtrain(Link I) {
    Node *S[10],*R;
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
            if (strcmp(r->date.num,str1)==0) {
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
            if (strcmp(r->date.startcity,str2)==0) {
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
            case 4:
                MODIFY(l);
                break;
            case 5:
                showtrain(l);
                break;
            case 6:
                SaveTrainlnfo(l);SaveBookinfo(k);
                break;
            case 0:
                return 0;
        }
    }
    printf("\nplease press any key to continue");
    getch();
};



