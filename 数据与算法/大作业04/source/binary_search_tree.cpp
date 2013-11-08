#include<cstdio>
#include<iostream>
#include"binary_search_tree.h"
using namespace std;
BinarySearchTree::BinarySearchTree(const ValueType& value):value_(value),node_count_(1),left_(NULL),right_(NULL){}
BinarySearchTree* BinarySearchTree::Insert(const ValueType& value)
{
    ++node_count_;
    return value<value_ ?
        ( left_!=NULL ?  left_->Insert(value) :  left_=new BinarySearchTree(value)):
        (right_!=NULL ? right_->Insert(value) : right_=new BinarySearchTree(value));
}
BinarySearchTree::~BinarySearchTree()
{
    delete left_;
    delete right_;
}
int PreOrderTraverse(BinarySearchTree* bst,int (*Operate)(BinarySearchTree*))
{
    Operate(bst);
    bst!=NULL ? PreOrderTraverse(bst-> left_,Operate) : 0;
    bst!=NULL ? PreOrderTraverse(bst->right_,Operate) : 0;
    return 0;
}
int PrintDepth(BinarySearchTree* bst)
{
    if(NULL == bst)
    {
        return 0;
    }
    int  left_depth=PrintDepth(bst-> left_);
    int right_depth=PrintDepth(bst->right_);
    return 1+(left_depth<right_depth ? right_depth : left_depth);
}

int MatchNode(BinarySearchTree* parent,BinarySearchTree* child)
{
    if(NULL==parent && NULL==child)
    {
        return 1;
    }
    if(NULL==parent || NULL==child)
    {
        return 0;
    }
    if(parent->node_count_ != child->node_count_)
    {
        return 0;
    }
    if(parent->node_count_ == 1)
    {
        return 1;
    }
    return MatchNode(parent->left_,child->left_) && MatchNode(parent->right_,child->right_);
}

int MatchCount(BinarySearchTree* parent,BinarySearchTree* child)
{
    if(NULL==parent && NULL==child)
    {
        return 1;
    }
    if(NULL==parent || NULL==child)
    {
        return 0;
    }
    return MatchNode(parent,child)+MatchCount(parent->left_,child)+MatchCount(parent->right_,child);
}
int MatchOutput(BinarySearchTree* parent,BinarySearchTree* child,int* output,int recursing_time)
{
    
    if(NULL==parent && NULL==child)
    {
        output[0]=0;
        return 1;
    }
    if(NULL==parent || NULL==child)
    {
        return 0;
    }
    if(MatchNode(parent,child))
    {
        output[0]=1+recursing_time;
        return 1;
    }
    int left_match=MatchOutput(parent->left_,child,output,recursing_time+1);
    return left_match+MatchOutput(parent->right_,child,output+left_match,recursing_time+1);
}