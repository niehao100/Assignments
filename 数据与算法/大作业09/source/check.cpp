#include <cstdio> 
using namespace std;
int main(int argc,char* argv[])
{
    FILE* input_file1=fopen(argv[1],"r");   //1是原始数据
    if(NULL==input_file1)
    {
        fprintf(stderr,"Argument 1 error.\n");
        return -1;
    }
    
    FILE* input_file2=fopen(argv[2],"r");   //2是输出
    if(NULL==input_file2)
    {
        fprintf(stderr,"Argument 2 error.\n");
        return -2;
    }
    int n=-1,pos=-1;
    fscanf(input_file1,"%d",&n);
    if(n<0)
    {
        fprintf(stderr,"File 1 error.\n");
        return -3;
    }
    fscanf(input_file2,"%d",&pos);
    if(pos<0)
    {
        fprintf(stderr,"File 2 error.\n");
        return -4;
    }
    int* input=new int[n]();
    for(int i=0;i<n;++i)
    {
        fscanf(input_file1,"%d",input+i);
    }
    int* array=new int[pos]();
    for(int p=0;p<pos;++p)
    {
        fscanf(input_file2,"%d",array+p);
    }
    for(int i=0,p=0;i<n&&p<pos;)
    {
        if(input[i]==array[p])
        {
            ++p;
        }
        if(p==pos)
        {
            fprintf(stderr,"Fine.\n");
            delete[] input;
            delete[] array;
            return 0;
        }
        ++i;
        if(i==n)
        {
            fprintf(stderr,"Oops.\nStucked at i=%d,p=%d.n=%d,pos=%d\n",i,p,n,pos);
            delete[] input;
            delete[] array;
            return 1;
        }
    }
    return 2;
}