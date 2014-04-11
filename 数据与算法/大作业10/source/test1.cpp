#include<cstdint>
#include<cstdio>
#include<cstdlib>
using namespace std;
typedef uint32_t Status;

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

char* StatusToString(char* str,Status s)
{
    for(int j=0;j<9;++j)
    {
        str[2*j]=((s>>(2*j))&1)?'o':(((s>>(2*j))&2)?'x':'0');
    }
    return str;
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
            {
                return -2;
            }
            return 0;
        }

    }
    return 4;
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

int main()  //测试task1
{
    Status initial=0;
    char buf[]="task1.exe 0 0 0 0 0 0 0 0 0 extra";
    const int shift=10;
    for(int i=0;i<9;++i)
    {
        initial=0;
        initial=Put(initial,i); //Step1,x
        initial=Put(initial,system(StatusToString(buf+shift,initial)-shift)); //Step2,o
        for(int j=NextEmptyPosition(initial,0),status;j>=0;j=NextEmptyPosition(initial,j+1))
        {
            status=Put(initial,j); //Step3,x
            status=Put(status,system(StatusToString(buf+shift,status)-shift));    //Step4,o
            
            for(int k=NextEmptyPosition(status,0),statusk;k>=0;k=NextEmptyPosition(status,k+1))
            {
                statusk=Put(status,k);  //Step5,x
                if(WhoWins(statusk)==1)
                {
                    fprintf(stderr,"Damn! Offensive won!\n");
                    Print(statusk,stderr);
                    Print(status,stderr);
                    Print(initial,stderr);
                }
                else if(WhoWins(statusk)==0||WhoWins(statusk)==-1)
                {
                    fprintf(stderr,"Good! Offensive didn't win!\r");
                }
                else if(WhoWins(statusk)==-2)
                {
                    
                    statusk=Put(statusk,system(StatusToString(buf+shift,statusk)-shift));   //Step6,o
                    if(WhoWins(statusk)==1)
                    {
                        fprintf(stderr,"Damn! Offensive won!\n");
                        Print(statusk,stderr);
                        Print(status,stderr);
                        Print(initial,stderr);
                    }
                    else if(WhoWins(statusk)==0||WhoWins(statusk)==-1)
                    {
                        fprintf(stderr,"Good! Offensive didn't win!\r");
                    }
                    else if(WhoWins(statusk)==-2)
                    {
                        for(int l=NextEmptyPosition(statusk,0),statusl;l>=0;l=NextEmptyPosition(statusk,l+1))
                        {
                            statusl=Put(statusk,l);  //Step7,x
                            if(WhoWins(statusl)==1)
                            {
                                fprintf(stderr,"Damn! Offensive won!\n");
                                Print(statusl,stderr);
                                Print(statusk,stderr);
                                Print(status,stderr);
                                Print(initial,stderr);
                            }
                            else if(WhoWins(statusl)==0||WhoWins(statusl)==-1)
                            {
                                fprintf(stderr,"Good! Offensive didn't win!\r");
                            }
                            else if(WhoWins(statusl)==-2)
                            {
                                
                                statusl=Put(statusl,system(StatusToString(buf+shift,statusl)-shift));   //Step8,o
                                if(WhoWins(statusl)==1)
                                {
                                    fprintf(stderr,"Damn! Offensive won!\n");
                                    Print(statusl,stderr);
                                    Print(statusk,stderr);
                                    Print(status,stderr);
                                    Print(initial,stderr);
                                }
                                else if(WhoWins(statusl)==0||WhoWins(statusl)==-1)
                                {
                                    fprintf(stderr,"Good! Offensive didn't win!\r");
                                }
                                else if(WhoWins(statusl)==-2)
                                {
                                    statusl=Put(statusl,NextEmptyPosition(statusl,0));   //Step9,x
                                    if(WhoWins(statusl)==1)
                                    {
                                        fprintf(stderr,"Damn! Offensive won!\n");
                                        Print(statusl,stderr);
                                        Print(statusk,stderr);
                                        Print(status,stderr);
                                        Print(initial,stderr);
                                    }
                                    else if(WhoWins(statusl)==0||WhoWins(statusl)==-1)
                                    {
                                        fprintf(stderr,"Good! Offensive didn't win!\r");
                                    }
                                    else
                                    {
                                        fprintf(stderr,"What the hell! Bug alert!\n");
                                        Print(statusl,stderr);
                                    }
                                }
                                else
                                {
                                    fprintf(stderr,"What the hell! Bug alert!\n");
                                    Print(statusl,stderr);
                                }
                            }
                            else
                            {
                                fprintf(stderr,"What the hell! Bug alert!\n");
                                Print(statusl,stderr);
                            }
                        }
                    }
                }
                else
                {
                    fprintf(stderr,"What the hell! Bug alert!\n");
                    Print(statusk,stderr);
                }
            }
        }
    }
    return 0;
}