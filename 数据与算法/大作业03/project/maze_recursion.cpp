#include<climits>
#include<cstdio>
using namespace std;

struct Node
{
    int x,y;    //结点坐标
    int G;      //已开销
    int H;      //预测开销
    int F;      //估值函数F=G+H
    Node* prev; //前驱结点
};

enum Flag
{
    kUnvisited=0,
    kOpen=1,
    kClosed=2
};

struct Status
{
    Flag flag;
    Node* node_ptr;    
};

typedef Node* ValueType;
struct PriorQueueNode
{
    PriorQueueNode* prev;
    ValueType value;
};

class PriorQueue
{
public:
    PriorQueue()
    {
        queue_end.prev=NULL;
        queue_end.value=NULL;
    }
    void Push(ValueType value)
    {
        PriorQueueNode* node=new PriorQueueNode;
        node->value=value;
        node->prev=queue_end.prev;
        queue_end.prev=node;
    }
    ValueType GetTop() const
    {
        int F_min=INT_MAX;
        PriorQueueNode* top=NULL;
        for(PriorQueueNode* iter=queue_end.prev;iter!=NULL;iter=iter->prev)
        {
            if(iter->value->F<=F_min)
            {
                F_min=iter->value->F;
                top=iter;
            }
        }
        return NULL==top?NULL:top->value;
    }
    ValueType Pop()
    {
        int F_min=INT_MAX;
        PriorQueueNode* top_next=NULL;
        for(PriorQueueNode* iter=&queue_end;iter->prev!=NULL;iter=iter->prev)
        {
            if(iter->prev->value->F<=F_min)
            {
                F_min=iter->prev->value->F;
                top_next=iter;
            }
        }
        if(NULL==top_next)
        {
            return NULL;
        }
        ValueType return_value=top_next->prev->value;
        top_next->prev=top_next->prev->prev;
        return return_value;
    }
    bool Empty() const
    {
        return NULL == queue_end.prev;
    }
protected:
    PriorQueueNode queue_end;
};

inline int Abs(int a)
{
    return a>0?a:-a;
}

inline int CalculateH(Node* node,int target_x,int target_y)
{
    return node->H=Abs(target_x-node->x)+Abs(target_y=node->y);
}

inline int CalculateF(Node* node)
{
    return node->F=node->G+node->H;
}

void PrintNode(Node* node)
{
    int counter=0;
    for(Node* iter=node;iter!=NULL;iter=iter->prev)
    {
        ++counter;
    }
    int length=counter;
    Node** node_array=new Node*[counter];
    for(Node* iter=node;iter!=NULL;iter=iter->prev)
    {
        --counter;
        node_array[counter]=iter;
    }
    for(int i=0;i<length;++i)
    {
        printf("%d %d\n",node_array[i]->x,node_array[i]->y);
        delete node_array[i];
    }
    delete node_array;
}
int direction[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
int m,n;                //迷宫尺寸
int start_x,start_y;    //起点坐标
int target_x,target_y;  //终点坐标     
char** maze;
Status** status;
bool SolveMaze(PriorQueue& queue)
{
	if(!queue.Empty())
	{
        Node* node=queue.Pop();
        status[node->x][node->y].flag=kClosed;
        for(int i=0;i<4;++i)    //四个方向
        {
            Node* next=new Node;
            next->prev=node;
            next->x=node->x+direction[i][0];
            next->y=node->y+direction[i][1];
			next->G=node->G+1;
            CalculateH(next,target_x,target_y);
            CalculateF(next);
            if(maze[next->x][next->y]!='0' ||                        //撞墙
                kClosed==status[next->x][next->y].flag ||             //封闭
                next->x<0 || next->y<0 || next->x>=m || next->y >= n)   //超出边界
            {
                continue;                                           //直接不予考虑
            }

            if(kUnvisited==status[next->x][next->y].flag)     //遇到没访问的点
            {
                if(next->x==target_x && next->y==target_y)    //看看是不是到地方了
                {
                    PrintNode(next);
                    for(int i=0;i<m;++i)
                    {
                        delete[] status[i];
                        delete[] maze[i];
                    }
                    delete[] status;
                    delete[] maze;
                    return true;
                }
                //没到地方就把它记为开放
                status[next->x][next->y].flag=kOpen;
                status[next->x][next->y].node_ptr=next;
                queue.Push(next);
                continue;
            }

            if(kOpen==status[next->x][next->y].flag)                //遇到已经找过的开放点
            {                                                       //研究一下怎么走比较近
                if(status[next->x][next->y].node_ptr->G<=next->G)   //原来的比较近
                {
                    continue;   //那就不用管
                }
                else    //新找到的这个比较近
                {
                    delete status[next->x][next->y].node_ptr;
                    status[next->x][next->y].node_ptr=next;    //那就挪一挪
                }
            }
        }
		return SolveMaze(queue);
	}
	return false;
}

int main()
{
    //读取迷宫数据
    scanf("%d%d%d%d%d%d\n",&m,&n,&start_x,&start_y,&target_x,&target_y);
    maze=new char*[m]();
    status=new Status*[m]();
    for(int i=0;i<m;++i)
    {
        maze[i]=new char[n+1]();
        status[i]=new Status[n]();
        gets(maze[i]);
    }

    if(start_x==target_x && start_y==target_y)
    {
        printf("%d %d\n",start_x,start_y);
        return 0;
    }

    //A*启发式搜索
    PriorQueue queue;
    Node* start=new Node;
    start->x=start_x,start->y=start_y;
    start->G=0;
    CalculateH(start,target_x,target_y);
    CalculateF(start);
    status[start->x][start->y].flag=kOpen;  //开放
    queue.Push(start);

	if(SolveMaze(queue))    //递归调用
	{
		return 0;
	}

    for(int i=0;i<m;++i)
    {
        delete[] maze[i];
    }
    delete[] maze;
    return 1;
}
