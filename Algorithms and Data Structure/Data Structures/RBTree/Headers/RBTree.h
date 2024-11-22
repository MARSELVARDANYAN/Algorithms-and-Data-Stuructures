#ifndef __RBTREE__
#define __RBTREE__
#include <iostream>


template <typename T>
class RBTree
{
private:
    enum Color{
        RED,
        BLACK
    };

    struct TreeNode
    {   

        Color color;
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        T val;
        TreeNode(T val) : color(RED), val(val), parent(nullptr), left(nullptr), right(nullptr){};
        TreeNode() : color(BLACK), val(T()), parent(nullptr), left(nullptr), right(nullptr){};
    };
    
private:
    TreeNode* root;
    TreeNode* NIL;

private:
    void leftRotate(TreeNode* current);
    void rightRotate(TreeNode* current);
    void insertFixup(TreeNode* new_node);
    void deleteFixup(TreeNode* current);
    void transplant(TreeNode* new_node, TreeNode* with);
    void __clear(TreeNode* node);
    TreeNode* __search(TreeNode* current, const T value);
    TreeNode* getMin(TreeNode* current);
    
    void __preOrder(TreeNode* node) const;
    void __inOrder(TreeNode* node) const;
    void __postOrder(TreeNode* node)const;

public:
    void delete_node(T key);
    TreeNode* search(const T val);
    void clear();
    void preOrder() const;
    void inOrder() const;
    void postOrder() const;
    void insert(const T& data);

    RBTree();

    ~RBTree(){
        __clear(root);
        delete NIL;
    };
};





#include "RBTree.hpp"

#endif // RBTREE


