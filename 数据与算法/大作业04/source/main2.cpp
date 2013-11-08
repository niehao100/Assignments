#include<cstdio>
#include"binary_search_tree.h"
using namespace std;
FILE* output_file;
void MergeSort(int* array,int n);
int main(int argc,char* argv[])
{
    if(argc!=4)
    {
        fprintf(stderr,"参数错误\n");
        return 1;
    }
    
    FILE* input_file1=fopen(argv[1],"r");
    if(NULL==input_file1)
    {
        fprintf(stderr,"输入文件1打开错误\n");
        return 2;
    }
    FILE* input_file2=fopen(argv[2],"r");
    if(NULL==input_file2)
    {
        fprintf(stderr,"输入文件2打开错误\n");
        return 3;
    }
    output_file=fopen(argv[3],"w");
    if(NULL==output_file)
    {
        fprintf(stderr,"输出文件打开错误\n");
        return 4;
    }
    
    ValueType temp=0;
    fscanf(input_file1,"%d",&temp);
    BinarySearchTree parent(temp);
    for(;;)
    {
        if(fscanf(input_file1,"%d",&temp)!=1)
        {
            break;
        }
        parent.Insert(temp);
    }
    fscanf(input_file2,"%d",&temp);
    BinarySearchTree child(temp);
    for(;;)
    {
        if(fscanf(input_file2,"%d",&temp)!=1)
        {
            break;
        }
        child.Insert(temp);
    }
    int match_number=MatchCount(&parent,&child);
    if(match_number==0)
    {
        fprintf(output_file,"NO");
        fclose(input_file1);
        fclose(input_file2);
        fclose(output_file);
        return 0;
    }
    fprintf(output_file,"YES\n%d\n",match_number);
    int* match_array=new int[match_number]();
    MatchOutput(&parent,&child,match_array);
    MergeSort(match_array,match_number);
    for(int i=0;i<match_number;++i)
    {
        fprintf(output_file,"%d\n",match_array[i]);
    }
    delete match_array;
    fclose(input_file1);
    fclose(input_file2);
    fclose(output_file);
    return 0;
}
void MergeSort(int* array,int n)
{
    if(n>1)
    {
        const int n1=n/2;
        const int n2=n-n1;
        int* array1=new int[n1]();
        int* array2=new int[n2]();
        for(int i=0;i<n1;++i)
        {
            array1[i]=array[i];
        }
        for(int i=0;i<n2;++i)
        {
            array2[i]=array[n1+i];
        }
        MergeSort(array1,n1);
        MergeSort(array2,n2);
        int* ptr1=array1;
        int* ptr2=array2;
        for(int i=0;i<n;++i)
        {
            if(ptr1-array1>=n1)
            {
                array[i]=ptr2[0];
                ++ptr2;
                continue;
            }
            if(ptr2-array2>=n2)
            {
                array[i]=ptr1[0];
                ++ptr1;
                continue;
            }
            if(ptr1[0]<ptr2[0])
            {
                array[i]=ptr1[0];
                ++ptr1;
                continue;
            }
            else
            {
                array[i]=ptr2[0];
                ++ptr2;
                continue;
            }
        }
        delete[] array1;
        delete[] array2;
    }
}