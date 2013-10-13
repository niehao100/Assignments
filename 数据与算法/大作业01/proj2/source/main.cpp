#include<cstdio>
#include<cctype>
using namespace std;
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        return -1;
    }
    FILE* input_file=fopen(argv[1],"r");
    if(input_file==NULL)
    {
        return -2;
    }
    FILE* output_file=fopen(argv[2],"w");
    if(output_file==NULL)
    {
        return -3;
    }
    for(char c;!feof(input_file);)
    {
        fputc(isalnum(c=fgetc(input_file))?c+5:c-3,output_file);
    }
    fclose(input_file);
    fclose(output_file);
    return 0;
}
