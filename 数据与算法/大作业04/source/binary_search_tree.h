typedef int ValueType;
class BinarySearchTree
{
public:
    BinarySearchTree(const ValueType& value);
    BinarySearchTree* Insert(const ValueType&);
    ~BinarySearchTree();

    friend int PreOrderTraverse(BinarySearchTree*,int (*Operate)(BinarySearchTree*));
    friend int PrintCount(BinarySearchTree* bst);
    friend int PrintValue(BinarySearchTree* bst);
    friend int PrintDepth(BinarySearchTree* bst);
    friend int MatchCount(BinarySearchTree* parent,BinarySearchTree* child);
    friend int MatchNode(BinarySearchTree* parent,BinarySearchTree* child);
    friend int MatchOutput(BinarySearchTree* parent,BinarySearchTree* child,int* output,int recursing_time=0);
private:
    ValueType value_;
    int node_count_;
    BinarySearchTree* left_;
    BinarySearchTree* right_;
};
extern FILE* output_file;
inline int PrintValue(BinarySearchTree* bst)
{
    bst!=NULL ? fprintf(output_file,"%d ",bst->value_) : fprintf(output_file,"# ");
    return 0;
}
inline int PrintCount(BinarySearchTree* bst)
{
    bst!=NULL ? fprintf(output_file,"%d ",bst->node_count_) : fprintf(output_file,"# ");
    return 0;
}