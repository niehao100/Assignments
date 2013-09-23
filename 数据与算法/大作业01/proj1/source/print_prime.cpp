#include<iostream>
#define L 10000
using namespace std;
int main()
{
    int counter=0;
    int p[L];

    //初始化
    for(int i=1;i<L;i++)
    {
        p[i]=i+1;
    }

    //筛法
    for(int i=1;i<L;i++)
    {
        for(int j=2;j*j<=p[i];j++)
        {
            if(p[i]%j==0)
            {
                p[i]=0;break;
            }
        }
    }

    //输出
    for(int i=1;i<L;i++)
    {
        if(p[i]!=0)
        {
            cout<<p[i];
            counter++;
            if(counter==999)
            {
                return 0;
            }
            cout<<',';
        }
    }

    return -1;  //返回-1说明数组空间不够大
}
