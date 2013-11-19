#include<cstdio>
#include"record.h"
using namespace std;
int main(int argc,char* argv[])
{
    if(argc!=9)
    {
        fprintf(stderr,"Wrong number of parameters(%d/8).\n",argc-1);
        return -1;
    }
/******************************开始读取输入文件1******************************/
    FILE* input_ori=fopen(argv[1],"r");
    if(NULL==input_ori)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[1]);
        return -2;
    }
    int number;
    double math,chinese;
    Record* record_root=NULL;
    for(;;)
    {
        if(fscanf(input_ori,"%*[^0123456789]%d%lf%lf",&number,&math,&chinese)<3)
        {
            break;
        }
        Record* temp=new Record(number,int(math)*100,int(chinese)*100);
        if(NULL==record_root)
        {
            record_root=temp;
        }
        else
        {
            record_root->Insert(temp,kNumber);
            record_root->Insert(temp,kScore);
        }
    }
    fclose(input_ori);
/******************************结束读取输入文件1******************************/
/******************************开始写入输出文件2******************************/
    FILE* output_num=fopen(argv[2],"w");
    if(NULL==output_num)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[2]);
        return -2;
    }
    PrintByNumber(record_root,output_num);
    fclose(output_num);
/******************************结束读取输出文件2******************************/
/******************************开始写入输出文件3******************************/
    FILE* output_scr=fopen(argv[3],"w");
    if(NULL==output_scr)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[3]);
        return -2;
    }
    PrintByScore(record_root,output_scr);
    fclose(output_scr);
/******************************结束读取输出文件3******************************/
/******************************开始写入输出文件4******************************/
    FILE* output_search=fopen(argv[4],"w");
    if(NULL==output_search)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[4]);
        return -2;
    }
    SearchAndPrint(record_root,170,1,3001,output_search);
    fclose(output_search);
/******************************结束读取输出文件4******************************/
/******************************开始读取输入文件5******************************/
    FILE* input_new=fopen(argv[5],"r");
    if(NULL==input_ori)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[5]);
        return -2;
    }
    for(;;)
    {
        if(fscanf(input_new,"%*[^0123456789]%d%lf%lf",&number,&math,&chinese)<3)
        {
            break;
        }
        record_root->Insert(new Record(number,int(math)*100,int(chinese)*100),kNumber);
    }
    fclose(input_new);
/******************************结束读取输入文件5******************************/
/******************************开始写入输出文件6******************************/
    FILE* output_update=fopen(argv[6],"w");
    if(NULL==output_num)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[6]);
        return -2;
    }
    PrintByNumber(record_root,output_update);
    fclose(output_update);
/******************************结束读取输出文件6******************************/
/******************************开始读取输入文件7******************************/
    FILE* input_del=fopen(argv[7],"r");
    if(NULL==input_ori)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[7]);
        return -2;
    }
    for(;;)
    {
        if(fscanf(input_del,"%*[^0123456789]%d%lf%lf",&number,&math,&chinese)<3)
        {
            break;
        }
        Nullify(record_root,number,int(math)*100,int(chinese)*100);
    }
    fclose(input_del);
/******************************结束读取输入文件7******************************/
/******************************开始写入输出文件8******************************/
    FILE* output_del=fopen(argv[8],"w");
    if(NULL==output_num)
    {
        fprintf(stderr,"Failed to open file \"%s\".\n",argv[8]);
        return -2;
    }
    PrintByScore(record_root,output_del);
    fclose(output_del);
/******************************结束读取输出文件8******************************/
    delete record_root;
    return 0;
}