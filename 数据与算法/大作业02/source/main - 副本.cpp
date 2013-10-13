#include<cstdio>
#include<cstdlib>
#include<cstring>
typedef int ValueType;
struct Triple
{
    int i;
    int j;
    ValueType value;
};
struct Node
{
    int i;
    int j;
    Node* right;
    Node* down;
    ValueType value;
};
class CrossList
{
public:
    CrossList(Triple*,int n,int row_max,int col_max);   //以n个三元组初始化
    CrossList(const CrossList&);    //深拷贝
    CrossList& operator=(const CrossList&); //深拷贝
    ~CrossList();

    CrossList Transpose() const;
    friend CrossList operator+(const CrossList&,const CrossList&);
    friend CrossList operator*(const CrossList&,const CrossList&);

    int Print() const;

    ValueType& At(int row,int col);
    ValueType Find(int row,int col) const;

private:
    int row_max_;   //稀疏矩阵行数
    int col_max_;   //稀疏矩阵列数
    Node** row_head_ptr_;   //稀疏矩阵行首指针数组[数组长度row_max_]
    Node** col_head_ptr_;   //稀疏矩阵列首指针数组[数组长度col_max_]
};
using namespace std;
int main(int argc,char* argv[])
{
    //既然说了保证没有坏数据那就不检测没有节操的重复节点了，费时间
    int row_max,col_max,element_max;
    scanf("%d%d%d",&row_max,&col_max,&element_max);
    Triple* triple_array=new Triple[element_max];
    for(int iter=0;iter<element_max;++iter)
    {
        scanf("%d%d%d",&(triple_array[iter].i),&(triple_array[iter].j),&(triple_array[iter].value));
    }
    CrossList matrix(triple_array,element_max,row_max,col_max);
    CrossList trans_matrix=matrix.Transpose();
    trans_matrix.Print();
    (matrix+trans_matrix).Print();
    (matrix*trans_matrix).Print();
    return 0;
}

CrossList::CrossList(Triple* triple_ptr,int n,int row_max,int col_max):row_max_(row_max),col_max_(col_max)
{
    row_head_ptr_=new Node*[row_max_]();
    col_head_ptr_=new Node*[col_max_]();
    for(Triple* iter=triple_ptr;iter<triple_ptr+n;++iter)
    {
        Node* node_ptr=new Node(Node{iter->i,iter->j,NULL,NULL,iter->value});
        if((NULL == row_head_ptr_[iter->i])||(node_ptr->j < row_head_ptr_[iter->i]->j))   //元素应插入行首
        {
            Node* next=row_head_ptr_[iter->i];
            row_head_ptr_[iter->i]=node_ptr;
            node_ptr->right=next;
        }
        else
        {
            for(Node* node=row_head_ptr_[iter->i];;)
            {
                if((node->j < node_ptr->j)&&((NULL == node->right)||(node_ptr->j < node->right->j)))
                {
                    Node* next=node->right;
                    node->right=node_ptr;
                    node_ptr->right=next;
                    break;
                }
                node=node->right;
            }
        }
        //列操作同理
        if((NULL == col_head_ptr_[iter->j])||(node_ptr->i < col_head_ptr_[iter->j]->i))
        {
            Node* next=col_head_ptr_[iter->j];
            col_head_ptr_[iter->j]=node_ptr;
            node_ptr->down=next;
        }
        else
        {
            for(Node* node=col_head_ptr_[iter->j];;)
            {
                if((node->i < node_ptr->i)&&((NULL == node->down)||(node_ptr->i < node->down->i)))
                {
                    Node* next=node->down;
                    node->down=node_ptr;
                    node_ptr->down=next;
                    break;
                }
                node=node->down;
            }
        }
    }
}
CrossList::CrossList(const CrossList& matrix):row_max_(matrix.row_max_),col_max_(matrix.col_max_)
{
    row_head_ptr_=new Node*[row_max_]();
    col_head_ptr_=new Node*[col_max_]();
    for(int row=0;row<matrix.row_max_;++row)
    {
        if(matrix.row_head_ptr_[row]!=NULL)
        {
            row_head_ptr_[row]=new Node();
            for(Node* node=matrix.row_head_ptr_[row],* new_node=row_head_ptr_[row];node!=NULL;node=node->right,new_node=new_node->right)
            {
                new_node->i=node->i;
                new_node->j=node->j;
                new_node->right=(NULL == node->right)?NULL:new Node();
                if((NULL == col_head_ptr_[new_node->j])||(new_node->i < col_head_ptr_[new_node->j]->i))
                {
                    Node* next=col_head_ptr_[new_node->j];
                    col_head_ptr_[new_node->j]=new_node;
                    new_node->down=next;
                }
                else
                {
                    for(Node* iter_node=col_head_ptr_[new_node->j];iter_node!=NULL;iter_node=iter_node->down)
                    {
                        if((iter_node->i < new_node->i)&&((NULL == iter_node->down)||(new_node->i < iter_node->down->i)))
                        {
                            Node* next=iter_node->down;
                            iter_node->down=new_node;
                            new_node->down=next;
                            break;
                        }
                    }
                }
                new_node->value=node->value;
            }
        }
    }
}
CrossList& CrossList::operator=(const CrossList& matrix)
{
    for(int row=0;row<row_max_;++row)
    {
        if(row_head_ptr_[row]!=NULL)
        {
            for(Node* node=row_head_ptr_[row];;)
            {
                Node* next=node->right;
                delete node;
                if(NULL == next)
                {
                    break;
                }
                node=next;
            }
        }
    }
    delete[] row_head_ptr_;
    delete[] col_head_ptr_;
    row_max_=matrix.row_max_;
    col_max_=matrix.col_max_;
    row_head_ptr_=new Node*[row_max_]();
    col_head_ptr_=new Node*[col_max_]();
    for(int row=0;row<matrix.row_max_;++row)
    {
        if(matrix.row_head_ptr_[row]!=NULL)
        {
            row_head_ptr_[row]=new Node();
            for(Node* node=matrix.row_head_ptr_[row],* new_node=row_head_ptr_[row];;)
            {
                new_node->i=node->i;
                new_node->j=node->j;
                new_node->right=(NULL == node->right)?NULL:new Node();
                if((NULL == col_head_ptr_[new_node->j])||(new_node->i < col_head_ptr_[new_node->j]->i))
                {
                    Node* next=col_head_ptr_[new_node->j];
                    col_head_ptr_[new_node->j]=new_node;
                    new_node->down=next;
                }
                else
                {
                    for(Node* iter_node=col_head_ptr_[new_node->j];iter_node!=NULL;iter_node=iter_node->down)
                    {
                        if((iter_node->i < new_node->i)&&((NULL == iter_node->down)||(new_node->i < iter_node->down->i)))
                        {
                            Node* next=iter_node->down;
                            iter_node->down=new_node;
                            new_node->down=next;
                            break;
                        }
                    }
                }
                new_node->value=node->value;
                if(NULL == node->right)
                {
                    break;
                }
                node=node->right;
                new_node=new_node->right;
            }
        }
    }
    return *this;
}
CrossList::~CrossList()
{
    for(int row=0;row<row_max_;++row)
    {
        if(row_head_ptr_[row]!=NULL)
        {
            for(Node* node=row_head_ptr_[row];;)
            {
                Node* next=node->right;
                delete node;
                if(NULL == next)
                {
                    break;
                }
                node=next;
            }
        }
    }
    delete[] row_head_ptr_;
    delete[] col_head_ptr_;
}

CrossList CrossList::Transpose() const
{
    CrossList trans=(*this);
    trans.row_max_=col_max_;
    trans.col_max_=row_max_;
    //存储旧的行首指针数组
    Node** temp=new Node*[trans.col_max_];
    memcpy(temp,trans.row_head_ptr_,trans.col_max_*sizeof(ValueType));
    //将旧的列首指针复制到新的行首指针数组中
    delete[] trans.row_head_ptr_;
    trans.row_head_ptr_=new Node*[trans.row_max_];
    memcpy(trans.row_head_ptr_,trans.col_head_ptr_,trans.row_max_*sizeof(ValueType));
    //将旧的行首指针复制到新的列首指针数组中
    delete[] trans.col_head_ptr_;
    trans.col_head_ptr_=new Node*[trans.col_max_];
    memcpy(trans.col_head_ptr_,temp,trans.col_max_*sizeof(ValueType));
    delete[] temp;
    for(int row=0;row<trans.row_max_;++row)
    {
        if(trans.row_head_ptr_[row]!=NULL)
        {
            for(Node* node=trans.row_head_ptr_[row];;)
            {
                int temp=node->i;
                node->i=node->j;
                node->j=temp;
                Node* next=node->down;
                node->down=node->right;
                node->right=next;
                if(NULL == next)
                {
                    break;
                }
                node=next;
            }
        }
    }
    return trans;
}
CrossList operator+(const CrossList& a,const CrossList& b)
{
    if(a.row_max_!=b.row_max_ || a.col_max_!=b.col_max_)
    {
        exit(1);
    }
    CrossList sum(a);
    for(int row=0;row<b.row_max_;++row) //遍历b，将b的节点加到sum里
    {
        if(b.row_head_ptr_[row]!=NULL)
        {
            for(Node* node=b.row_head_ptr_[row];node!=NULL;node=node->right)
            {
                //若已有则value相加，否则添加节点
                if((NULL == sum.row_head_ptr_[row])||(node->j < sum.row_head_ptr_[row]->j))
                {
                    Node* new_node=new Node();
                    new_node->value=node->value;
                    new_node->i=node->i;
                    new_node->j=node->j;
                    new_node->right=sum.row_head_ptr_[row];
                    sum.row_head_ptr_[row]=new_node;
                    if((NULL == sum.col_head_ptr_[node->j])||(node->i < sum.col_head_ptr_[node->j]->i))
                    {
                        new_node->down=sum.col_head_ptr_[node->j];
                        sum.col_head_ptr_[node->j]=new_node;
                    }
                    else
                    {
                        for(Node* col_node=sum.col_head_ptr_[row];col_node!=NULL;col_node=col_node->down)
                        {
                            if((col_node->i < new_node->i)&&((NULL == col_node->down)||(new_node->i < col_node->down->i)))
                            {
                                new_node->down=col_node->down;
                                col_node->down=new_node;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    for(Node* row_node=sum.row_head_ptr_[row];row_node!=NULL;row_node=row_node->right)
                    {
                        if(row_node->j == node->j)  //节点已经存在
                        {
                            row_node->value+=node->value;
                            break;
                        }
                        //节点不存在
                        if((row_node->j < node->j)&&((NULL == row_node->right)||(node->j < row_node->right->j)))
                        {
                            Node* new_node=new Node();
                            new_node->value=node->value;
                            new_node->i=node->i;
                            new_node->j=node->j;
                            new_node->right=row_node->right;
                            row_node->right=new_node;
                            if((NULL == sum.col_head_ptr_[node->j])||(node->i < sum.col_head_ptr_[node->j]->i))
                            {
                                new_node->down=sum.col_head_ptr_[node->j];
                                sum.col_head_ptr_[node->j]=new_node;
                            }
                            else
                            {
                                for(Node* col_node=sum.col_head_ptr_[row];col_node!=NULL;col_node=col_node->down)
                                {
                                    if((col_node->i < new_node->i)&&((NULL == col_node->down)||(new_node->i < col_node->down->i)))
                                    {
                                        new_node->down=col_node->down;
                                        col_node->down=new_node;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return sum;
}
CrossList operator*(const CrossList& a,const CrossList& b)
{
    if(a.col_max_!=b.row_max_)
    {
        exit(3);
    }
    CrossList product(NULL,0,a.row_max_,b.col_max_);
    for(int row=0;row<a.row_max_;++row)
    {
        Node* product_row=product.row_head_ptr_[row];   //记录乘积节点指针，降低遍历复杂度
        for(int col=0;col<b.col_max_;++col)
        {
            Node* product_col=product.col_head_ptr_[col];   //同上
            ValueType sum=0;
            Node* a_row=a.row_head_ptr_[row];
            Node* b_col=b.col_head_ptr_[col];
            while(a_row!=NULL && b_col!=NULL)
            {
                if(a_row->j == b_col->i)
                {
                    sum+=a_row->value * b_col->value;
                    a_row=a_row->right;
                    b_col=b_col->down;
                }
                else
                {
                    a_row->j < b_col->i ? a_row=a_row->right : b_col=b_col->down;
                }
            }
            if(sum!=0)
            {
                if(NULL==product_row)
                {
                    product_row=product.row_head_ptr_[row]=new Node();
                    product_row->value=sum;
                    product_row->i=row;
                    product_row->j=col;
                    if(NULL==product_col)
                    {
                        product_col=product.col_head_ptr_[col]=product_row;
                    }
                    else
                    {
                        product_col->down=product_row;
                        product_col=product_col->down;
                    }
                }
                else
                {
                    product_row->right=new Node();
                    product_row=product_row->right;
                    product_row->value=sum;
                    product_row->i=row;
                    product_row->j=col;
                    if(NULL==product_col)
                    {
                        product_col=product.col_head_ptr_[col]=product_row;
                    }
                    else
                    {
                        product_col->down=product_row;
                        product_col=product_col->down;
                    }
                }
            }
        }
    }
    return product;
}

int CrossList::Print() const
{
    int return_counter=0;
    //遍历
    for(int row=0;row<row_max_;++row)
    {
        if(row_head_ptr_[row]!=NULL)
        {
            for(Node* node=row_head_ptr_[row];node!=NULL;node=node->right)
            {
                return_counter+=( 0==node->value ? 0 : printf("%d %d %d\n",node->i,node->j,node->value));  //非零元素操作
            }
        }
    }
    return return_counter;
}
ValueType CrossList::Find(int row,int col) const
{
    if(row>=row_max_||col>=col_max_)
    {
        return 0;
    }
    if(row_head_ptr_[row]!=NULL)
    {
        for(Node* node=row_head_ptr_[row];node!=NULL;node=node->right)
        {
            if(node->j == col)
            {
                return node->value;
            }
            if(node->j > col)
            {
                return 0;
            }
        }
    }
    return 0;
}
ValueType& CrossList::At(int row,int col)
{
    if(row>=row_max_||col>=col_max_)
    {
        exit(1);
    }
    if(row_head_ptr_[row]!=NULL)    //如果已经存在该元素则直接返回引用，否则插入新的零元素
    {
        for(Node* node=row_head_ptr_[row];node!=NULL;node=node->right)
        {
            if(node->j == col)
            {
                return node->value;
            }
            if((node->j > col)||((node->j < col)&&((NULL == node->right)||(col < node->right->j))))
            {
                Node* new_node=new Node();
                new_node->i=row;
                new_node->j=col;
                new_node->right=node->right;
                node->right=new_node;
                if(NULL==col_head_ptr_[col])
                {
                    col_head_ptr_[col]=new_node;
                }
                else
                {
                    for(Node* col_node=col_head_ptr_[col];col_node!=NULL;col_node=col_node->down)
                    {
                        if((col_node->i < row)&&((NULL == col_node->down)||(row < col_node->down->i)))
                        {
                            new_node->down=col_node->down;
                            col_node->down=new_node;
                        }
                    }
                }
                return new_node->value;
            }
        }
    }
    row_head_ptr_[row]=new Node();
    row_head_ptr_[row]->i=row;
    row_head_ptr_[row]->j=col;
    if(NULL==col_head_ptr_[col])
    {
        col_head_ptr_[col]=row_head_ptr_[row];
    }
    else
    {
        for(Node* col_node=col_head_ptr_[col];col_node!=NULL;col_node=col_node->down)
        {
            if((col_node->i < row)&&((NULL == col_node->down)||(row < col_node->down->i)))
            {
                row_head_ptr_[row]->down=col_node->down;
                col_node->down=row_head_ptr_[row];
            }
        }
    }
    return row_head_ptr_[row]->value;
}
