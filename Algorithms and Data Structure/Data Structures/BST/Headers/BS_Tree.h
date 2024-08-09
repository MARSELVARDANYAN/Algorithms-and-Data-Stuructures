#ifndef __BS_Tree__
#define __BS_Tree__
#include <iostream>
#include <algorithm>

template <class T>
class BST
{
private:
    struct TreeNode
    {
        TreeNode* left;
        TreeNode* right;
        T data;
        TreeNode(T new_data) : left{nullptr}, right{nullptr}, data{new_data} {}
    };
    
    TreeNode* root;
    int node_count;

public:
    BST();

    ~BST();
    
    // Method to check if the tree is empty
    bool isEmpty() const;

    // Method to get the height of the tree
    int getHeight() const;

    // Method to get the number of nodes in the tree
    int getNumberOfNodes();

    // Method to get the data of the root node
    T& getRootData();

    // Method to set the data of the root node
    void setRootData(T new_data);

    // Method to add a new node with the given data
    bool add(T newData); 

private:
    bool add(TreeNode* node, T newData);

    TreeNode* getEntry(TreeNode* root, const T& anEntry) const;

    int getHeight(TreeNode* node) const;

    TreeNode* clear(TreeNode* node);

    void inOrderTraverse(TreeNode* node) const;

    void preorderTraverse(TreeNode* node)const;

    void postorderTraverse(TreeNode* node) const;

    void levelOrderTraverse(TreeNode* node, int level) const;


public:
    // Method to remove all nodes from the tree
    void clear();

    // Method to find an entry in the tree
    T getEntry(const T& anEntry) const ;

    // Method to check if the tree contains a given data
    bool contains(T data);

    // Method to traverse the tree in pre-order
    void preorderTraverse() const;

    // Method to traverse the tree in in-order
    void inorderTraverse() const;

    //Method to traverse the tree in in-order
    void postOrderTraverse() const;
    
    //Method to traverse the tree in in-order
    void levelOrderTraverse() const;
};


#include "BS_Tree.hpp"
#endif


