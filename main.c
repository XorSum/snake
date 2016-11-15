#include<stdio.h>
#include<time.h>
#include<stdlib.h>
struct snake
{
    int x;
    int y;
    struct snake*next;
};
struct snake*createsnake()
{
    struct snake*head,*tmp1,*tmp2,*tail;
    head=(struct snake*)malloc(sizeof(struct snake));
    tmp1=(struct snake*)malloc(sizeof(struct snake));
    tmp2=(struct snake*)malloc(sizeof(struct snake));
    tail=(struct snake*)malloc(sizeof(struct snake));
    tail->next=NULL;
    tmp2->next=tail;
    tmp1->next=tmp2;
    head->next=tmp1;
    head->x=9;
    tmp1->x=10;
    tmp2->x=11;
    tail->x=12;
    head->y=8;
    tmp1->y=8;
    tmp2->y=8;
    tail->y=8;
    return head;
}

struct snake*movehead(struct snake*head,char ch)
{
    struct snake*neck,*tmp;
    tmp=(struct snake*)malloc(sizeof(struct snake));
    tmp->x=head->x;
    tmp->y=head->y;
    tmp->next=head->next;
    neck=head->next;
    switch (ch)
    {
    case 'w':
        if (head->y==(neck->y+1))
        {
            head->y++;
            head->next=tmp;
        }
        else
        {
            head->y--;
            head->next=tmp;
        }
        break;
    case 's':
        if (head->y==(neck->y-1))
        {
            head->y--;
            head->next=tmp;
        }
        else
        {
            head->y++;
            head->next=tmp;
        }
        break;
    case 'a':
        if (head->x==(neck->x+1))
        {
            head->x++;
            head->next=tmp;
        }
        else
        {
            head->x--;
            head->next=tmp;
        }
        break;
    case 'd':
        if (head->x==(neck->x-1))
        {
            head->x--;
            head->next=tmp;
        }
        else
        {
            head->x++;
            head->next=tmp;
        }
        break;
    default:
        if (head->x==(neck->x-1))
        {
            head->x--;
            head->next=tmp;
            break;
        }
        if (head->x==(neck->x+1))
        {
            head->x++;
            head->next=tmp;
            break;
        }
        if (head->y==(neck->y-1))
        {
            head->y--;
            head->next=tmp;
            break;
        }
        if (head->y==(neck->y+1))
        {
            head->y++;
            head->next=tmp;
            break;
        }
    }
    if (head->x==16) head->x=0;
    if (head->x==-1) head->x=15;
    if (head->y==16) head->y=0;
    if (head->y==-1) head->y=15;
    return head;
}

struct snake*cuttail(struct snake*head)
{
    struct snake*tmp1,*tmp2;
    tmp1=head->next;
    tmp2=head;
    while (tmp1->next!=NULL)
    {
        tmp1=tmp1->next;
        tmp2=tmp2->next;
    }
    tmp2->next=NULL;
    free(tmp1);
    return head;
}

int biteself(struct snake*head)
{
    struct snake*tmp;
    tmp=head->next;
    while (tmp!=NULL)
    {
        if ((head->x==tmp->x)&&(head->y==tmp->y))
            return 1;
        tmp=tmp->next;
    }
    return 0;
}
void textfood(struct snake*tmp,int *xp,int *yp,int *bp)
{
    if (tmp==NULL) *bp=0;
    else if (tmp->x==*xp&&tmp->y==*yp) *bp=1;
    else textfood(tmp->next,xp,yp,bp);
}

struct snake*putfood(struct snake*head,struct snake*food)
{
    int x,y,book=0;
    srand((unsigned)time(NULL));
    do
    {
        x=((unsigned)rand())%16;
        y=((unsigned)rand())%16;
        textfood(head,&x,&y,&book);
    }
    while(book==1);
    food->x=x;
    food->y=y;
    food->next=NULL;
    return food;
}

void draw(struct snake*head,struct snake*food,int len,int step)
{
    int i,x,y;
    struct snake*tmp;
    tmp=head;
    int picture[256];
    for (i=0; i<256; i++)
        picture[i]=0;
    picture[food->x+food->y*16]=3;
    while(tmp!=NULL)
    {
        picture[tmp->x+tmp->y*16]=1;
        tmp=tmp->next;
    }
    picture[head->x+head->y*16]=2;
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    printf("a lenth:%-8d step:%-10d a\n",len,step);
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
    for (y=0; y<16; y++)
    {
        printf("a");
        for (x=0; x<16; x++)
        {
            switch (picture[x+y*16])
            {
            case 0:
                printf("  ");
                break;
            case 1:
                printf(" *");
                break;
            case 2:
                printf(" H");
                break;
            case 3:
                printf(" F");
                break;
            }
        }
        printf("a\n");
    }
    printf("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n");
}
void freesnake(struct snake *head,struct snake*food)
{
    struct snake *tmp1,*tmp2;
    free(food);
    tmp1=head;
    tmp2=head;
    while (tmp2!=NULL)
    {
        tmp2=tmp2->next;
        free(tmp1);
        tmp1=tmp2;
    }
}
void snake()
{
    char ch;
    int len=4,step=0;
    struct snake *head,*food;
    food=(struct snake*)malloc(sizeof(struct snake));
    food->next=NULL;
    head=createsnake();
    food=putfood(head,food);
    draw(head,food,len,step);
    while(1)
    {
        scanf("%c",&ch);
        getchar();
        if (ch=='w'||ch=='a'||ch=='s'||ch=='d'||ch=='\n')
        {
            head=movehead(head,ch);
            if ((head->x==food->x)&&(head->y==food->y))
            {
                food=putfood(head,food);
                len++;
            }
            else
                head=cuttail(head);
            step++;
            draw(head,food,len,step);
            if (biteself(head)==1)
                break;
        }
        else
            printf("please input wasd\n");
    }
    freesnake(head,food);
}
int main()
{
    snake();
    return 0;
}
