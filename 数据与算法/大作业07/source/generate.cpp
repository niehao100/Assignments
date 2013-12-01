#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;
int main()
{
    clog<<"Input max number of double precision float number:";
    int n=0;
    cin>>n;
    srand(time(NULL));
    printf("0\n0\n0\n1\n%d\n",n);
    for(int i=0;i<n;++i)
    {
        double random_number=(double(rand())/RAND_MAX-0.5)*1e10;
        (rand()%2)&&(random_number*=-1);
        printf("%X %X\n",*((int*)(&random_number)+1),*(int*)(&random_number));
    }
    return 0;
}