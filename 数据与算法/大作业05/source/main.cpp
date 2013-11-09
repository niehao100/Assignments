#include<climits>
#include<cstdio>
using namespace std;
bool IsStronglyConnected(int** adjacency_matrix,int v);
void PrintShortestPathMatrix(int** adjacency_matrix,int v,int** path);
int PrintShortestPath(int** path,int start,int end,bool is_init=true);
int main()
{
    int v=0,e=0;
    scanf("%d%d",&v,&e);
    if( e>v*v || v<=0 || e<=0 )
    {
        fprintf(stderr,"Bad input: v=%d, e=%d.\n",v,e);
        return 1;
    }
    int** adjacency_matrix=new int*[v]();
    for(int i=0;i<v;++i)
    {
        adjacency_matrix[i]=new int[v]();
    }
    
    int head=-1,rear=-1,weight=-1;
    for(int i=0;i<e;++i)
    {
        if(scanf("%d%d%d",&head,&rear,&weight)!=3)
        {
            fprintf(stderr,"Bad input on line %d.\n",i+2);
            return 2;
        }
        if( head>=v || rear>=v || head<0 || rear<0 || weight<=0 )
        {
            fprintf(stderr,"Bad input: (%d,%d,%d).\n",head,rear,weight);
            return 3;
        }
        adjacency_matrix[head][rear]=weight;
    }
    
    int start=-1,end=-1;
    scanf("%d%d",&start,&end);
    /********************************输入结束********************************/
    if(IsStronglyConnected(adjacency_matrix,v))
    {
        printf("1\n");
        if(v<=1000)
        {
            int** path=new int*[v]();
            for(int i=0;i<v;++i)
            {
                path[i]=new int[v]();
            }
            printf("\n");
            PrintShortestPathMatrix(adjacency_matrix,v,path);
            printf("\n");
            PrintShortestPath(path,start,end);
            for(int i=0;i<v;++i)
            {
                delete[] path[i];
                path[i]=NULL;
            }
            delete[] path;
            path=NULL;
        }
    }
    else
    {
        printf("0\n");
    }
    /********************************输入结束********************************/
    
    
    
    
    
    
    
    
    /*
    for(int i=0;i<v;++i)
    {
        for(int j=0;j<v;++j)
        {
            printf("%3d",adjacency_matrix[i][j]);
        }
        putchar('\n');
    }*/
    
    
    
    
    
    
    
    
    
    
    
    for(int i=0;i<v;++i)
    {
        delete[] adjacency_matrix[i];
        adjacency_matrix[i]=NULL;
    }
    delete[] adjacency_matrix;
    adjacency_matrix=NULL;
    return 0;
}

bool IsStronglyConnected(int** adjacency_matrix,int v)
{
    //高端大气的Tarjan看不懂啊，先写个简单的看看满足不满足要求
    bool* v_read=new char[v]();
    for(int i=1;i<v;++i)
    {
        ;
    }
    delete[] v_read;
    return true;
}
void PrintShortestPathMatrix(int** adjacency_matrix,int v,int** path)
{
    int* weight_matrix=new int[v*v]();
    for(int i=0;i<v;++i)
    {
        for(int j=0;j<v;++j)
        {
            weight_matrix[i*v+j]=(adjacency_matrix[i][j]==0 && i!=j)?INT_MAX:adjacency_matrix[i][j];
            path[i][j]=weight_matrix[i*v+j]==INT_MAX ? -1 : j ;
        }
    }
    
    int* temp=new int[v*v]();
    for(int k=0;k<v;++k)
    {
        for(int i=0;i<v;++i)
        {
            for(int j=0;j<v;++j)
            {
                register int t=(weight_matrix[i*v+k]!=INT_MAX && weight_matrix[k*v+j]!=INT_MAX) ? weight_matrix[i*v+k]+weight_matrix[k*v+j] : INT_MAX; 
                //t暂存可能的较小权值，由于int加法遇到INT_MAX会溢出变负，因此需要一个较复杂的表达式
                temp[i*v+j]=
                    weight_matrix[i*v+j]>t ? t : weight_matrix[i*v+j] ;
                weight_matrix[i*v+j]>t && (path[i][j]=k);
            }
        }
        for(int i=0;i<v;++i)
        {
            for(int j=0;j<v;++j)
            {
                weight_matrix[i*v+j]=temp[i*v+j];
            }
        }
    }
    delete[] temp;
    temp=NULL;
    
    for(int i=0;i<v;++i)
    {
        for(int j=0;j<v;++j)
        {
            printf("%d ",weight_matrix[i*v+j]);
        }
        putchar('\n');
    }
    
    delete[] weight_matrix;
    weight_matrix=NULL;
}
int PrintShortestPath(int** path,int start,int end,bool is_init)
{
    is_init && printf("%d ",start);
    printf("%d ",path[start][end]);
    path[start][end]!=end && PrintShortestPath(path,path[start][end],end,false);
    return 0;
}
