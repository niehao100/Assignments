#include<cwchar>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<iostream>
#include<string>
#include<vector>
#include<windows.h>
using namespace std;
vector<string> family_name_vector={"��","��","��","��","��","��","��","��","Ǯ","Ǯ","Ǯ","Ǯ","Ǯ","Ǯ","Ǯ","Ǯ","Ǯ","��","��","��","��","֣","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","ʩ","��","��","��","��","��","��","κ","��","��","��","л","��","ˮ","�","��","��","��","��","��","��","��","³","Τ","��","��","��","��","��","��","��","��","Ԭ","��","��","ʷ","��","��","�","Ѧ","��","��","��","��","��","��","��","��","��","��","��","��","��","ʱ","��","��","��","��","Ԫ","��","��","��","���","�ĺ�"};
vector<string>   male_name_vector={"��","ǿ","��","��","��","��","��","��","��","��","־","��","��","��","��","��","ԣ","��","��","��","��","��","ʯ","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","��","¡","��","��","��","��","��","��","��","С","��","��","��","��","��","��","˼","��","��","��","Զ","��","��","��","��","��","��"};
vector<string> female_name_vector={"��","��","��","��","��","��","ݼ","��","��","ݷ","�","��","��","��","��","ܿ","��","��","��","��","��","��","��","��","��"};
int main(int argc,char* argv[])
{
    if(argc!=4) //��һ������ȷ������ļ����ڶ�������ȷ�����ѧ�ų�ʼֵ������������ȷ������������
    {
        cerr<<"�����������ԡ���";
        return -1;
    }
    else
    {
        FILE* out_file=NULL;
        if(strcmp(argv[1],"-s")==0||strcmp(argv[1],"-S")==0)
        {
            out_file=fopen("student.if.txt","w");
        }
        else if(strcmp(argv[1],"-t")==0||strcmp(argv[1],"-T")==0)
        {
            out_file=fopen("teacher.if.txt","w");
        }
        else
        {
            cerr<<"��һ���������õĲ��ԡ���";
            return -2;
        }
        if(out_file==NULL)
        {
            cerr<<"�ļ��򿪴���";
            return -4;
        }
        else
        {
            uint64_t num=atoll(argv[2]);
            size_t n=atoll(argv[3]);
            srand(time(NULL));
            for(size_t i=0;i<n;++i,++num)
            {
                string family_name=family_name_vector[size_t(double(rand())/RAND_MAX*(family_name_vector.size()-1))];
                string   male_name=  male_name_vector[size_t(double(rand())/RAND_MAX*(  male_name_vector.size()-1))];
                string female_name=female_name_vector[size_t(double(rand())/RAND_MAX*(female_name_vector.size()-1))];
                string  first_name=rand()<(RAND_MAX/3)?female_name:male_name;
                if(first_name==female_name)
                {
                    first_name+=rand()<(RAND_MAX/5)?"":female_name_vector[size_t(double(rand())/RAND_MAX*(female_name_vector.size()-1))];
                }
                if(first_name==  male_name)
                {
                    first_name+=rand()<(RAND_MAX/5)?"":  male_name_vector[size_t(double(rand())/RAND_MAX*(  male_name_vector.size()-1))];
                }
                char num_str[21]={'\0'};
                sprintf(num_str,"%llu",num);
                fprintf(out_file,(family_name+first_name+' '+num_str+'\n').c_str());
            }
            fclose(out_file);
            return 0;
        }
        return 2;
    }
    return 1;
}
