#include<iostream>
using namespace std;
unsigned long long partial_sum(unsigned long long *i,float* sum);
int main()
{
    float sum=1,part=0;
/*    for(int i=2;;++i)
    {
        sum+=1.0/i;
        cout<<"i="<<i<<",sum="<<sum<<endl;
        
    }*/
    unsigned long long i=2;
    partial_sum(&i,&sum);
    for(unsigned long long i=2;;++i)
    {
        for(;part<sum;++i)
        {
            part+=1.0/i;
        }
        clog<<"i="<<i<<",part="<<part<<endl;
        sum+=part;
        cout<<"i="<<i<<",sum="<<sum<<endl;
    }
    return 0;
}
unsigned long long partial_sum(unsigned long long* i,float* sum)
{
    float part=0.0;
    if((*sum) > 10.0/ (*i))
    {
        partial_sum(i,&part);
        *sum += part;
        cout<<"i="<<*i<<",sum="<<*sum<<endl;
        return *i;
    }
    for(;part<*sum;++(*i))
    {
        *sum += 1.0/ (*i);
        cout<<"i="<<*i<<",sum="<<*sum<<endl;
    }
    return *i;
}
