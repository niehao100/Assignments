#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
using namespace std;
int main(int argc,char* argv[])
{
    //确定问题规模，默认为1000条边完全有向图
    int v=1000;
    argc>1 && sscanf(argv[1],"%d",&v);
    int e=v*(v-1)/2;
    argc>2 && sscanf(argv[2],"%d",&e);

    printf("v=%d,e=%d\n",v,e);
    char output_filename[256];
    sprintf(output_filename,"input_v%d_e%d_%d.txt",v,e,time(NULL));
    srand(time(NULL));
    FILE* output_file=fopen(output_filename,"w");
    printf("%s",output_filename);
    fclose(output_file);
    return 0;
}