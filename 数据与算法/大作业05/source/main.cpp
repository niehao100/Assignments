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
/********************************输出结束********************************/
    for(int i=0;i<v;++i)
    {
        delete[] adjacency_matrix[i];
        adjacency_matrix[i]=NULL;
    }
    delete[] adjacency_matrix;
    adjacency_matrix=NULL;
    return 0;
}

class Stack
{
public:
    typedef int ValueType;
    struct Node
    {
        ValueType value;
        Node* below;
    };
    Stack():top(NULL){}
    ~Stack()
    {
        Clear();
    }
    void Clear()
    {
        for(;!(IsEmpty());)
        {
            Pop();
        }
    }
    void Push(ValueType value)
    {
        Node* new_node=new Node;
        new_node->value=value;
        new_node->below=top;
        top=new_node;
    }
    ValueType Pop()
    {
        if(NULL==top)
        {
            return -1;
        }
        ValueType return_value=top->value;
        Node* next_top=top->below;
        delete top;
        top=next_top;
        return return_value;
    }
    bool IsEmpty()
    {
        return NULL==top;
    }
    bool Contains(ValueType value)
    {
        for(Node* ptr=top;ptr!=NULL;ptr=ptr->below)
        {
            if(ptr->value==value)
            {
                return true;
            }
        }
        return false;
    }
private:
    Node* top;
};
static Stack tarjan_stack;
static int tarjan_index=0; 
static int tarjan_counter=0;
static int** tarjan_adjacency_matrix=NULL;
static bool* tarjan_visited_tag=NULL;
static int tarjan_v=0;
static int* tarjan_dfn=NULL;
static int* tarjan_low=NULL;
bool Tarjan(int current_vertex)
{
    tarjan_visited_tag[current_vertex]=true;
    tarjan_dfn[current_vertex]=tarjan_low[current_vertex]=++tarjan_index;
    tarjan_stack.Push(current_vertex);
    for(int i=0;i<tarjan_v;++i)
    {
        if(i==current_vertex || 0==tarjan_adjacency_matrix[current_vertex][i])
        {
            continue;
        }
        if(tarjan_visited_tag[i]==false)
        {
            Tarjan(i);
            tarjan_low[i]<tarjan_low[current_vertex] && (tarjan_low[current_vertex]=tarjan_low[i]);
        }
        else
        {
            if(tarjan_stack.Contains(i))
            {
            tarjan_low[i]<tarjan_low[current_vertex] && (tarjan_low[current_vertex]=tarjan_dfn[i]);
            }
        }
    }
    if(tarjan_dfn[current_vertex]==tarjan_low[current_vertex])
    {
        for(;;)
        {
            int scc_vertex=tarjan_stack.Pop();
            ++tarjan_counter;
            if(tarjan_counter==tarjan_v)
            {
                return true;
            }
            if(current_vertex==scc_vertex)
            {
                tarjan_counter=0;
                break;
            }
        }
    }
    return false;
}
bool IsStronglyConnected(int** adjacency_matrix,int v)
{
    tarjan_adjacency_matrix=adjacency_matrix;
    tarjan_index=0;
    tarjan_counter=0;
    tarjan_v=v;
    tarjan_visited_tag=new bool[v]();
    tarjan_dfn=new int[v]();
    tarjan_low=new int[v]();
    bool return_value=Tarjan(0);
    delete[] tarjan_low;
    tarjan_low=NULL;
    delete[] tarjan_dfn;
    tarjan_dfn=NULL;
    delete[] tarjan_visited_tag;
    tarjan_visited_tag=NULL;
    tarjan_adjacency_matrix=NULL;
    return return_value;
}
void PrintShortestPathMatrix(int** adjacency_matrix,int v,int** path)
{
    int* weight_matrix=new int[v*v]();
    for(int i=0;i<v;++i)
    {
        for(int j=0;j<v;++j)
        {
            weight_matrix[i*v+j]=(adjacency_matrix[i][j]==0 && i!=j)?INT_MAX:adjacency_matrix[i][j];
            path[i][j]=weight_matrix[i*v+j]==INT_MAX ? -1 : i ;
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
                weight_matrix[i*v+j]>t && (path[i][j]=path[k][j]);
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
    path[start][end]!=end && PrintShortestPath(path,start,path[start][end],false);
    printf("%d ",end);
    return 0;
}
