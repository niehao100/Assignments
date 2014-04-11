﻿#include<cstdint>
#include<cstdio>
using namespace std;
typedef uint32_t Status;
int Decide(Status);      //做最有利决定
int NextEmptyPosition(Status,int start=0);   //下一个空位
Status Put(Status original,int position);    //下棋
bool IsValid(Status);    //先手比后手多1或0个棋子
int WhoWins(Status);     //1表示先手赢 0表示平手 -1表示后手赢
int TurnsCount(Status);  //总的步数
int Print(Status,FILE*out=stdout);       //可视化打印到屏幕

struct Node
{
    Status status;
    Node* next[9];
    int weight;
};
int Init(Node&);
Node node[1<<18];
bool visited[1<<18];
int Save(Node& node_head);

int Init(Node& node_head)
{
    for(int i=0;i<9;++i)
    {
        node_head.next[i]=NULL;
    }
    for(int i=NextEmptyPosition(node_head.status,0);i>=0;\
        i=NextEmptyPosition(node_head.status,i+1))
    {
        Status next=Put(node_head.status,i);
        node_head.next[i]=new Node;
        node_head.next[i]->status=next;
        node_head.next[i]->weight=0;
        if(WhoWins(next)==1)
        {
            node_head.next[i]->weight+=10e8;
        }
        else if(WhoWins(next)==0)
        {
            node_head.next[i]->weight+=5e8;
        }
        else if(WhoWins(next)==-1)
        {
            ;//node_head.next[i]->weight-=1e8;
        }
        else if(WhoWins(next)==-2)
        {
            Init(*node_head.next[i]);
        }
        else
        {
            fprintf(stderr,"Fatal error.\n");
            return -2;
        }
        node_head.weight+=node_head.next[i]->weight/10;
        node[node_head.status]=node_head;
    }
    //Print(node_head.status);
    //printf("Weight:%d\n\n",node_head.weight);
    return 0;
}

Status Put(Status original,int position)
{
    if(!IsValid(original))
    {
        fprintf(stderr,"Invalid input status.\n");
        return -1;
    }
    if(position<0 || position >8 || original&(3<<(2*position)))
    {
        fprintf(stderr,"Invalid position.\n");
        return original;
    }
    if(TurnsCount(original)%2==1) //已有奇数步，轮到后手
    {
        original|=(1<<(2*position));
    }
    else
    {
        original|=(2<<(2*position));
    }
    return original;
}

int NextEmptyPosition(Status status,int start)
{
    for(int i=start;i<9;++i)
    {
        if((status&(3<<(2*i)))==0)
        {
            return i;
        }
    }
    return -1;
}

int Decide(Status status)
{
    if(!IsValid(status))
    {
        return -1;
    }
    int min_weight=(~0)^(1<<(8*sizeof(int)-1));
    int min_i=-1;
    int max_weight=-min_weight-1;
    int max_i=-1;
    for(int i=NextEmptyPosition(status,0);i>=0;i=NextEmptyPosition(status,i+1))
    {
        Status next=Put(status,i);
        if(node[next].weight>max_weight)
        {
            max_weight=node[next].weight;
            max_i=i;
        }
        (node[next].weight<min_weight) &&\
            (min_weight=node[next].weight,min_i=i);//printf("Weight:%d.\n",node[next].weight);
    }
    if(TurnsCount(status)%2==0) //先手
    {
        return max_i;
    }
    else
    {
        return min_i;
    }
    //fprintf(stderr,"status%x,win%d,draw%d,lose%d.\n",status,determined[status][0],determined[status][1],determined[status][2]);
    
    return -1;
}

bool IsValid(Status status)
{
    for(int i=0;i<9;++i)
    {
        if(!((status&(3<<(2*i)))^(3<<(2*i))))
        {
            return false;
        }
    }
    int offensive=0,defensive=0;
    for(int i=0;i<9;++i)
    {
        (status&(1<<(2*i+1))) && (++offensive);
    }
    for(int i=0;i<9;++i)
    {
        (status&(1<<(2*i))) && (++defensive);
    }
    return offensive-defensive==1 || offensive-defensive==0;
}
int Print(Status status,FILE* out)
{
    if(!IsValid(status))
    {
        fprintf(stderr,"Invalid input.\n");
        return 1;
    }
    fprintf(out,"After %d turns, ",TurnsCount(status));
    WhoWins(status)== 1 && fprintf(out,"offensive wins.\n");
    WhoWins(status)==-1 && fprintf(out,"defensive wins.\n");
    WhoWins(status)== 0 && fprintf(out,"it draws.\n");
    WhoWins(status)==-2 && fprintf(out,"it is still not determined.\n");
    WhoWins(status)== 2 && fprintf(out,"it meets invalid input.\n");
    WhoWins(status)== 3 && fprintf(out,"it meets unexpected input.\n");
    WhoWins(status)== 4 && fprintf(out,"it meets unknown error.\n");
    for(int i=0;i<9;++i)
    {
        ((status&(2<<(2*i)))^(2<<(2*i)))==0 && fputc('x',out);    //先手
        ((status&(1<<(2*i)))^(1<<(2*i)))==0 && fputc('o',out);    //后手
        ((status&(2<<(2*i)))^(2<<(2*i)))&&(((status&(1<<(2*i)))^(1<<(2*i))))\
            && fputc('.',out);    //未下
        i%3==2 && fputc('\n',out);
    }
    return 0;
}
bool Wins(Status status,int side)
{
    return
    ((((status&(3<<(2*0)))^(side<<(2*0)))==0) &&\
     (((status&(3<<(2*1)))^(side<<(2*1)))==0) &&\
     (((status&(3<<(2*2)))^(side<<(2*2)))==0)) ||\
    ((((status&(3<<(2*3)))^(side<<(2*3)))==0) &&\
     (((status&(3<<(2*4)))^(side<<(2*4)))==0) &&\
     (((status&(3<<(2*5)))^(side<<(2*5)))==0)) ||\
    ((((status&(3<<(2*6)))^(side<<(2*6)))==0) &&\
     (((status&(3<<(2*7)))^(side<<(2*7)))==0) &&\
     (((status&(3<<(2*8)))^(side<<(2*8)))==0)) ||\
    ((((status&(3<<(2*0)))^(side<<(2*0)))==0) &&\
     (((status&(3<<(2*3)))^(side<<(2*3)))==0) &&\
     (((status&(3<<(2*6)))^(side<<(2*6)))==0)) ||\
    ((((status&(3<<(2*1)))^(side<<(2*1)))==0) &&\
     (((status&(3<<(2*4)))^(side<<(2*4)))==0) &&\
     (((status&(3<<(2*7)))^(side<<(2*7)))==0)) ||\
    ((((status&(3<<(2*2)))^(side<<(2*2)))==0) &&\
     (((status&(3<<(2*5)))^(side<<(2*5)))==0) &&\
     (((status&(3<<(2*8)))^(side<<(2*8)))==0)) ||\
    ((((status&(3<<(2*0)))^(side<<(2*0)))==0) &&\
     (((status&(3<<(2*4)))^(side<<(2*4)))==0) &&\
     (((status&(3<<(2*8)))^(side<<(2*8)))==0)) ||\
    ((((status&(3<<(2*2)))^(side<<(2*2)))==0) &&\
     (((status&(3<<(2*4)))^(side<<(2*4)))==0) &&\
     (((status&(3<<(2*6)))^(side<<(2*6)))==0));
}
int WhoWins(Status status)
{
    if(!IsValid(status))
    {
        return 2;
    }
    if(Wins(status,2))
    {
        if(Wins(status,1))
        {
            return 3;
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if(Wins(status,1))
        {
        
            return -1;
        }
        else
        {
            if(TurnsCount(status)<9)
            {/*
                if(TurnsCount(status)==8)
                {
                    return WhoWins(Put(status,NextEmptyPosition(status)));
                }*/
                return -2;
            }
            return 0;
        }

    }
    return 4;
}
int TurnsCount(Status status)
{
    if(!IsValid(status))
    {
        return -1;
    }
    int counter=0;
    for(int i=0;i<9;++i)
    {
        (status&(3<<(2*i))) && (++counter);
    }
    return counter;
}