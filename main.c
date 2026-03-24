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
    
};
