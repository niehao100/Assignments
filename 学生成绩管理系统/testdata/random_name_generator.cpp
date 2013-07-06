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
vector<string> family_name_vector={"赵","赵","赵","赵","赵","赵","赵","赵","钱","钱","钱","钱","钱","钱","钱","钱","钱","孙","李","周","吴","郑","王","王","王","王","王","冯","陈","褚","卫","蒋","沈","韩","杨","朱","秦","尤","许","何","吕","施","张","孔","曹","严","华","金","魏","陶","姜","戚","谢","邹","水","窦","章","云","苏","潘","葛","范","彭","鲁","韦","昌","马","苗","凤","花","方","俞","任","袁","柳","鲍","史","唐","费","岑","薛","雷","贺","倪","汤","殷","罗","毕","郝","邬","安","常","乐","于","时","齐","康","伍","余","元","顾","孟","黄","诸葛","夏侯"};
vector<string>   male_name_vector={"刚","强","仁","发","民","国","忠","艺","文","德","志","智","辉","华","军","生","裕","健","炎","宏","毅","坚","石","超","鹏","亮","锦","家","春","磊","勇","正","东","南","斌","武","奎","秋","鑫","伦","朋","隆","宝","靖","俊","杰","友","祖","颂","小","宇","兴","波","荣","峰","祥","思","振","海","凯","远","汉","桥","松","柏","利","大"};
vector<string> female_name_vector={"嘉","华","芳","芬","燕","虹","菁","妃","娟","莘","楠","宜","玉","妙","丹","芸","香","蕾","兰","慧","玲","静","茹","怡","紫"};
int main(int argc,char* argv[])
{
    if(argc!=4) //第一个参数确定输出文件，第二个参数确定输出学号初始值，第三个参数确定随机输出个数
    {
        cerr<<"参数个数不对。。";
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
            cerr<<"第一个参数设置的不对。。";
            return -2;
        }
        if(out_file==NULL)
        {
            cerr<<"文件打开错误。";
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
