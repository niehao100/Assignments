#include<cstdint>
#include<cstdio>
using namespace std;
typedef uint32_t Status;
int Decide(Status);      //做最有利决定
int Calculate(Status);   //计算各种决策的后果
int NextEmptyPosition(Status,int start=0);   //下一个空位
Status Put(Status original,int position);    //下棋
bool IsValid(Status);    //先手比后手多1或0个棋子
int WhoWins(Status);     //1表示先手赢 0表示平手 -1表示后手赢
int TurnsCount(Status);  //总的步数
int Print(Status,FILE*out=stdout);       //可视化打印到屏幕
int determined[1<<18][3]={};   //表示先手胜、平、后手胜的次数

struct Node
{
    Status status;
    Node* next[9];
    int weight;
};
int Init(Node&);
Node node[1<<18];
bool visited[1<<18];
int main(int argc,char* argv[])
{
/*
    char input_status[9]={' ',' ',' ',' ',' ',' ',' ',' ',' '};
    for(int i=0;i<argc-1;++i)
    {
        input_status[i]=argv[i+1][0];
    }
    Status output_status=0;
    for(int i=0;i<9;++i)
    {
        if(input_status[i]=='x')
        {
            output_status|=(1<<(2*i+1));
        }
        else if(input_status[i]=='o')
        {
            output_status|=(1<<(2*i));
        }
    }
    
    for(int i=0;i<(1<<18);++i)
    {
        IsValid(i) && WhoWins(i);
        //(status[i]!=0)&&Print(status[i]);
    }
    Calculate(0);
    //Print(output_status,stderr);
    //Print(Put(output_status,6),stderr);
    //Decide(Status);
    for(int i=0;i<(1<<18)-(1<<18)+3;++i)
    {
        IsValid(i) && (WhoWins(i)==1 || WhoWins(i)==-1 || WhoWins(i)==0 || WhoWins(i)==-2) && (Print(i) ,
        printf("%d %d %d\n\n\n",determined[i][0],determined[i][1],determined[i][2]));
    }
    for(int i=0;i<(1<<18);++i)
    {
        IsValid(i) && printf("%6x%8d\t",i,node[i].weight);
    }
    for(int i=0;i<(1<<18);++i)
    {
        node[i].weight=0;
        //node[i].status=i;
    }*/
    Init(node[0]);
    Status s=0;
    Print(s);
    s=Put(s,Decide(s));
    Print(s);
    s=Put(s,Decide(s));
    Print(s);
    s=Put(s,Decide(s));
    Print(s);
    s=Put(s,Decide(s));
    Print(s);
    s=Put(s,Decide(s));
    Print(s);
    
    return 0;
}

int Init(Node& node_head)
{
    visited[node_head.status]=true;
    for(int i=NextEmptyPosition(node_head.status,0);i>=0;\
        i=NextEmptyPosition(node_head.status,i+1))
    {
        Status next=Put(node_head.status,i);    //下一个为node[next]
        node[next].status=next;
        if(WhoWins(next)==1)
        {
            ++node[next].weight;
        }
        else if(WhoWins(next)==0)
        {
            ;
        }
        else if(WhoWins(next)==-1)
        {
            --node[next].weight;
        }
        else if(WhoWins(next)==-2)
        {
            if(visited[next]==false)
            {
                Init(node[next]);
            }
        }
        else
        {
            fprintf(stderr,"Fatal error.\n");
            return -2;
        }
        node_head.weight+=node[next].weight;
    }
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
            (min_weight=node[next].weight,min_i=i);
    }
    if(TurnsCount(status)%2==0) //先手
    {
        return max_i;
    }
    else
    {
        return min_i;
    }
    fprintf(stderr,"status%x,win%d,draw%d,lose%d.\n",status,determined[status][0],determined[status][1],determined[status][2]);
    
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
    WhoWins(status)== 1 && fprintf(out,"Offensive wins.\n");
    WhoWins(status)==-1 && fprintf(out,"Defensive wins.\n");
    WhoWins(status)== 0 && fprintf(out,"Draw.\n");
    WhoWins(status)==-2 && fprintf(out,"Not determined.\n");
    WhoWins(status)== 2 && fprintf(out,"Invalid input.\n");
    WhoWins(status)== 3 && fprintf(out,"Unexpected input.\n");
    WhoWins(status)== 4 && fprintf(out,"Unknown error.\n");
    for(int i=0;i<9;++i)
    {
        ((status&(2<<(2*i)))^(2<<(2*i)))==0 && fputc('x',out);    //先手
        ((status&(1<<(2*i)))^(1<<(2*i)))==0 && fputc('o',out);    //后手
        ((status&(2<<(2*i)))^(2<<(2*i)))&&(((status&(1<<(2*i)))^(1<<(2*i))))\
            && fputc('.',out);    //未下
        i%3==2 && fputc('\n',out);
    }
    fprintf(out,"Totally %d turns.\n\n",TurnsCount(status));
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