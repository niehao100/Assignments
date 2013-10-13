#ifndef SPARSE_MATRIX_H_
#define SPARSE_MATRIX_H_
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
#endif // SPARSE_MATRIX_H_
