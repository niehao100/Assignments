#include<cstdint>
#include<cstdio>
#include<cstdlib>
#include<windows.h>
using namespace std;  
DWORD WINAPI test2(LPVOID argv);//声明一个线程函数   

int main()
{
    HANDLE handles[101];
    char buf[100];
    for(int x=0;x<=100;++x)
    {
        sprintf(buf,"%d",x);
        handles[x]=CreateThread(NULL,0,test2,buf,0,NULL);
        if(x%10==9)
        {
            for(int i=0;i<10;++i)
            {
                WaitForSingleObject(handles[x-i],INFINITE);
                CloseHandle(handles[x-i]);
            }
        }
    }
    WaitForSingleObject(handles[100],INFINITE);
    CloseHandle(handles[100]);
    return 0;
}





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

DWORD WINAPI test2(LPVOID argv)   //测试task2
{
    int x=atoi((char*)argv);
    int who_wins;
    int total=0;
    char buf[]="task2.exe 0 0 0 0 0 0 0 0 0 0.00 extra";
    const int shift=10;
    Status status1=Put(0,system(StatusToString(buf+shift,0)-shift));                //Step1, x
    for(int i=NextEmptyPosition(status1,0);i>=0;i=NextEmptyPosition(status1,i+1))
    {
        Status status2=Put(status1,i);                                                  //Step2, o on position i
        Status status3=Put(status2,system(StatusToString(buf+shift,status2)-shift));    //Step3, x
        for(int j=NextEmptyPosition(status3,0);j>=0;j=NextEmptyPosition(status3,j+1))
        {
            Status status4=Put(status3,j);                                              //Step4, o on position i
            Status status5=Put(status4,system(StatusToString(buf+shift,status4)-shift));    //Step5, x
            who_wins=WhoWins(status5);
            if(who_wins==1)
            {
                total+=100;
                fprintf(stderr,"\r%d",total);
            }
            else if(who_wins==0)
            {
                total+=x;
                fprintf(stderr,"\r%d",total);
            }
            else if(who_wins==-1)
            {
                ;//total+=0;
                fprintf(stderr,"\r%d",total);
            }
            else if(who_wins==-2)
            {
                for(int k=NextEmptyPosition(status5,0);k>=0;k=NextEmptyPosition(status5,k+1))
                {
                    Status status6=Put(status5,k);                                              //Step6, o on position i
                    who_wins=WhoWins(status6);
                    if(who_wins==1)
                    {
                        total+=100;
                        fprintf(stderr,"\r%d",total);
                    }
                    else if(who_wins==0)
                    {
                        total+=x;
                        fprintf(stderr,"\r%d",total);
                    }
                    else if(who_wins==-1)
                    {
                        ;//total+=0;
                        fprintf(stderr,"\r%d",total);
                    }
                    else if(who_wins==-2)
                    {
                        Status status7=Put(status6,system(StatusToString(buf+shift,status6)-shift));    //Step7, x
                        who_wins=WhoWins(status7);
                        if(who_wins==1)
                        {
                            total+=100;
                            fprintf(stderr,"\r%d",total);
                        }
                        else if(who_wins==0)
                        {
                            total+=x;
                            fprintf(stderr,"\r%d",total);
                        }
                        else if(who_wins==-1)
                        {
                            ;//total+=0;
                            fprintf(stderr,"\r%d",total);
                        }
                        else if(who_wins==-2)
                        {
                            for(int l=NextEmptyPosition(status7,0);l>=0;l=NextEmptyPosition(status7,l+1))
                            {
                                Status status8=Put(status7,l);                                              //Step8, o on position i
                                who_wins=WhoWins(status8);
                                if(who_wins==1)
                                {
                                    total+=100;
                                    fprintf(stderr,"\r%d",total);
                                }
                                else if(who_wins==0)
                                {
                                    total+=x;
                                    fprintf(stderr,"\r%d",total);
                                }
                                else if(who_wins==-1)
                                {
                                    ;//total+=0;
                                    fprintf(stderr,"\r%d",total);
                                }
                                else if(who_wins==-2)
                                {
                                    Status status9=Put(status8,system(StatusToString(buf+shift,status8)-shift));    //Step9, x
                                    who_wins=WhoWins(status9);
                                    if(who_wins==1)
                                    {
                                        total+=100;
                                        fprintf(stderr,"\r%d",total);
                                    }
                                    else if(who_wins==0)
                                    {
                                        total+=x;
                                        fprintf(stderr,"\r%d",total);
                                    }
                                    else if(who_wins==-1)
                                    {
                                        ;//total+=0;
                                        fprintf(stderr,"\r%d",total);
                                    }
                                    else
                                    {
                                        fprintf(stderr,"Bug alert!\n");
                                        Print(status9,stderr);
                                        Print(status8,stderr);
                                        Print(status7,stderr);
                                        Print(status6,stderr);
                                        Print(status5,stderr);
                                        Print(status4,stderr);
                                        Print(status3,stderr);
                                        Print(status2,stderr);
                                        Print(status1,stderr);
                                    }
                                }
                                else
                                {
                                    fprintf(stderr,"Bug alert!\n");
                                    Print(status7,stderr);
                                    Print(status6,stderr);
                                    Print(status5,stderr);
                                    Print(status4,stderr);
                                    Print(status3,stderr);
                                    Print(status2,stderr);
                                    Print(status1,stderr);
                                }
                            }
                        }
                        else
                        {
                            fprintf(stderr,"Bug alert!\n");
                            Print(status5,stderr);
                            Print(status4,stderr);
                            Print(status3,stderr);
                            Print(status2,stderr);
                            Print(status1,stderr);
                        }
                    }
                    else
                    {
                        fprintf(stderr,"Bug alert!\n");
                        Print(status3,stderr);
                        Print(status2,stderr);
                        Print(status1,stderr);
                    }
                }

            }
            else
            {
                fprintf(stderr,"Bug alert!\n");
                Print(status1,stderr);
            }
        }
    }
    printf("x=%d,final score=%d.\n",x,total);
    fflush(stderr);
    fflush(stdout);
    return 0;
}