#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;
int main()
{
    srand(time(NULL));
    const int i_max=10000;
    FILE* output=fopen("Single.in","w");
    fprintf(output,"1\n%d",rand());
    freopen("Increasing.in","w",output);
    fprintf(output,"%d\n",i_max);
    for(int i=0,random=0;i<i_max;++i)
    {
        random+=rand()*2/RAND_MAX+1;
        fprintf(output,"%d ",random);
    }
    freopen("Decreasing.in","w",output);
    fprintf(output,"%d\n",i_max);
    for(int i=0,random=0;i<i_max;++i)
    {
        random-=rand()*2/RAND_MAX+1;
        fprintf(output,"%d ",random+23456);
    }
    freopen("Random.in","w",output);
    fprintf(output,"%d\n",i_max);
    bool exist[RAND_MAX]={false};
    for(int i=0,random=0;i<i_max;++i)
    {
        random=rand();
        for(;exist[random];)
        {
            random=rand();
        }
        fprintf(output,"%d ",random);
        exist[random]=true;
    }
    return 0;
}