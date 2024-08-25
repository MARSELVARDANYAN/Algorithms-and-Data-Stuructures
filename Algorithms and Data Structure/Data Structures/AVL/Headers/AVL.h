#ifndef __AVL__
#define __AVL__
#include <iostream>
#include "../../BST/Headers/BS_Tree.h"

template <typename T>
class AVL : private BST<T>
{
private:
    typename BST<T>::TreeNode* root;
    int node_count;

public:
    AVL();
   
    ~AVL();
    
    typename BST<T>::TreeNode* search(int value);

    T& getRootData() override;

    void inOrderTraverse() const override;

    void preOrderTraverse() const override;

    void postOrderTraverse() const override;

    void levelOrderTraverse() const override;

    void insert(const T val);

    void clear() override;

    bool empty() const;

    void deleteValue(const T& value);

private:
    int getBalance(typename BST<T>::TreeNode* node);
   
    typename BST<T>::TreeNode* __insert(typename BST<T>::TreeNode* node, int key);
    
    typename BST<T>::TreeNode* rotateLeft(typename BST<T>::TreeNode* node);

    typename BST<T>::TreeNode* rotateRight(typename BST<T>::TreeNode* node);

    int __getHeight(typename BST<T>::TreeNode* node) const override;

    int maxDepth(typename BST<T>::TreeNode* node) const ;

    void levelOrderHelper(typename BST<T>::TreeNode* node, int level) const;

    typename BST<T>::TreeNode* minValueNode(typename BST<T>::TreeNode* node);

    typename BST<T>::TreeNode* deleteNode(typename BST<T>::TreeNode* root, const T& key);
};


#include "AVL.hpp"

#endif //__AVL__


