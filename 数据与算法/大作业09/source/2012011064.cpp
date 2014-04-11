#include<cstdio>
using namespace std;
int main(int argc,char* argv[])
{
    FILE* input_file=fopen(argv[1],"r");
    if(NULL==input_file)
    {
        fprintf(stderr,"Argument 1 error.\n");
        return -1;
    }
    
    FILE* output_file=fopen(argv[2],"w");
    if(NULL==output_file)
    {
        fprintf(stderr,"Argument 2 error.\n");
        return -2;
    }
    int n;
    fscanf(input_file,"%d",&n);
    int* array_counter=new int[n]();
    int* array=new int[n*n]();  //一维数组模拟二维数组
    int* input=new int[n]();
    int pos=0;
    int temp=-1;
    for(int i=0;i<n;++i)
    {
        fscanf(input_file,"%d",&temp);
        input[i]=temp;
        if(0==pos || temp>array[(pos-1)*n+array_counter[pos-1]-1])
        {
            array[pos*n+array_counter[pos]]=temp;
            ++(array_counter[pos]);
            ++pos;
        }
        else
        {
            int begin=0,end=pos;
            for(int j=end/2;;)
            {
                if(array[j*n+array_counter[j]-1]<=temp)
                {
                    begin=j;
                    j=(begin+end)/2;
                    continue;
                }
                else
                {
                    if(j==0 || array[(j-1)*n+array_counter[j-1]-1]<temp)
                    {
                        array[j*n+array_counter[j]]=temp;
                        ++(array_counter[j]);
                        break;
                    }
                    else
                    {
                        end=j;
                        j=(begin+end)/2;
                        continue;
                    }
                }
            }
        }
        
    }
    fclose(input_file);
    
    fprintf(output_file,"%d\n",pos);
    temp=-1;
    int* result=new int[pos]();
    for(int i=n-1,p=pos-1;i>=0&&p>=0;--i)
    {
        for(int j=array_counter[p]-1;j>=0;--j)
        {
            if(array[p*n+j]==input[i])
            {
                result[p]=input[i];
                --p;
                break;
            }
        }
        
    }
    for(int i=0;i<pos;++i)
    {
        fprintf(output_file,"%d ",result[i]);
    }
    fclose(output_file);
    delete[] result;
    delete[] input;
    delete[] array;
    delete[] array_counter;
    return 0;
}