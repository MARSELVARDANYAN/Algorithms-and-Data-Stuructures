#ifndef __BS_Tree__
#define __BS_Tree__
#include <iostream>
#include <algorithm>

template <class T>
class BST
{
protected:
    struct TreeNode
    {
        TreeNode* left;
        TreeNode* right;
        T data;
        int height;
        TreeNode(T new_data) : left{nullptr}, right{nullptr}, data{new_data}, height(1) {}
    };
    
    TreeNode* root;
    int node_count;

public:
    BST();

    ~BST();
    
    bool isEmpty() const;

    int getHeight() const;

    int getNumberOfNodes();

    virtual T& getRootData();

    void setRootData(T new_data);

    bool add(T newData); 

    TreeNode* remove(const T val);



protected:
    bool add(TreeNode* node, T newData);

    TreeNode* getEntry(TreeNode* root, const T& anEntry) const;

    virtual int __getHeight(TreeNode* node) const;

    TreeNode* __clear(TreeNode* node);

    void __inOrderTraverse(TreeNode* node) const;

    void __preorderTraverse(TreeNode* node)const;

    void __postorderTraverse(TreeNode* node) const;

    void __levelOrderTraverse(TreeNode* node, int level) const;

    TreeNode* get_max(TreeNode* node) const;

    TreeNode* get_min(TreeNode* node) const;

    TreeNode* _remove(TreeNode* node, const T val);


public:
    virtual void clear();

    T getEntry(const T& anEntry) const ;

    bool contains(T data);

    virtual void preOrderTraverse() const;

    virtual void inOrderTraverse() const;

    virtual void postOrderTraverse() const;
    
    virtual void levelOrderTraverse() const;
};


#include "BS_Tree.hpp"
#endif


