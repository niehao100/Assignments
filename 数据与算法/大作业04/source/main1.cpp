#include<cstdio>
#include"binary_search_tree.h"
using namespace std;
FILE* output_file;
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        fprintf(stderr,"参数错误\n");
        return 1;
    }
    
    FILE* input_file=fopen(argv[1],"r");
    if(NULL==input_file)
    {
        fprintf(stderr,"输入文件打开错误\n");
        return 2;
    }
    output_file=fopen(argv[2],"w");
    if(NULL==output_file)
    {
        fprintf(stderr,"输出文件打开错误\n");
        return 3;
    }
    
    ValueType temp=0;
    fscanf(input_file,"%d",&temp);
    BinarySearchTree bst(temp);
    for(;;)
    {
        if(fscanf(input_file,"%d",&temp)!=1)
        {
            break;
        }
        bst.Insert(temp);
    }
    
    PreOrderTraverse(&bst,&PrintValue);
    fprintf(output_file,"\n\n");
    PreOrderTraverse(&bst,&PrintCount);
    fprintf(output_file,"\n\n%d",PrintDepth(&bst));
    fclose(input_file);
    fclose(output_file);
    return 0;
}