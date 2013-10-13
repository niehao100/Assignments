#include<cstdio>
#include"sparse_matrix.h"
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

