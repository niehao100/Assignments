/******************************************************************************
 *                                                                            *
 *  Created by Chi Blaok @ EE,THU                                             *
 *                                                                            *
 *  This work is licensed under a Creative Commons Attribution-NonCommercial- *
 *  ShareAlike 3.0 Unported License.                                          *
 *                                                                            *
 ******************************************************************************/
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<ctime>
#include<algorithm>
using namespace std;
int main(int argc,char* argv[])
{
    //确定问题规模，默认为1000条边完全有向图
    int v=1000;
    argc>1 && sscanf(argv[1],"%d",&v);
    int e=v*(v-1);
    argc>2 && sscanf(argv[2],"%d",&e);
    e>v*(v-1) && (e=v*(v-1)); //e最大是e=v*(v-1)

    fprintf(stderr,"v=%d,e=%d\n",v,e);
    char output_filename[256];
    sprintf(output_filename,"input_v%d_e%d_%lld.txt",v,e,time(NULL));
    FILE* output_file=fopen(output_filename,"w");
    fprintf(output_file,"%d %d\n",v,e);
    int* edge=new int[v*(v-1)]();
    for(int i=0;i<e;++i)
    {
        edge[i]=1;
    }
    srand(time(NULL));
    random_shuffle(edge,edge+v*(v-1));
    random_shuffle(edge,edge+v*(v-1));
    random_shuffle(edge,edge+v*(v-1));
    random_shuffle(edge,edge+v*(v-1));
    random_shuffle(edge,edge+v*(v-1));
    random_shuffle(edge,edge+v*(v-1));
    random_shuffle(edge,edge+v*(v-1));
    //洗牌
    for(int i=0;i<v*(v-1);++i)
    {
        int a=double(rand())*(v*(v-1)-1)/RAND_MAX;
        int t=edge[a];
        edge[a]=edge[i];
        edge[i]=t;
    }
    for(int i=0,counter=0;i<v;++i)
    {
        for(int j=0;j<v;++j)
        {
            if(i==j)
            {
                continue;
            }
            edge[counter] && fprintf(output_file,"%d %d %d\n",i,j,int(double(rand())*(200-1)/RAND_MAX+1));
            ++counter;
        }
    }
    delete[] edge;
    int start=double(rand())*v/RAND_MAX;
    int end=double(rand())*v/RAND_MAX;
    start==end && (end+=double(rand())*v/RAND_MAX,end/=2);
    fprintf(output_file,"%d %d",start,end);
    fprintf(stderr,"Generated %s successfully.\n",output_filename);
    fclose(output_file);
    return 0;
}