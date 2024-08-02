#include "BS_Tree.h"
#include <deque>

template <class T>
BST<T>::BST() : root{nullptr}, node_count{0} {}

template <class T>
BST<T>::~BST(){}

template <class T>
inline bool BST<T>::isEmpty() const
{
    return root == nullptr;
}

template <class T>
inline int BST<T>::getHeight()
{
    return 0;
}

template <class T>
inline int BST<T>::getNumberOfNodes()
{
    return node_count;
}

template <class T>
inline T &BST<T>::getRootData()
{   
    if (root == nullptr) {
        throw std::runtime_error("Root is not found");
    }
    
    return root->data;
}

template <class T>
inline void BST<T>::setRootData(T new_data)
{   
    if (root == nullptr) {
        root = new TreeNode(new_data);
        ++node_count;
    }

    root->data = new_data;      
}

template <class T>
inline bool BST<T>::add(T newData)
{   
    if (root == nullptr) {
        root = new TreeNode(newData);
        ++node_count;
        return true;
    }
    return add(root, newData);
}

template <class T>
inline bool BST<T>::add(TreeNode *node, T newData)
{
    if (newData < node->data) {
        if (node->left == nullptr) {
            node->left = new TreeNode(newData);
            ++node_count;
            return true;
        }
        return add(node->left, newData);
    }
    else if (newData > node->data) {
        if (node->right == nullptr) {
            node->right = new TreeNode(newData);
            ++node_count;
            return true;
        }
        return add(node->right, newData);
    }
    
    return false;
}

template <class T>
typename BST<T>::TreeNode* BST<T>::getEntry(TreeNode* node, const T &anEntry) const
{   
    if (node == nullptr) {
        return nullptr;
    }
    if (node->data == anEntry) {
        return node;
    }
    else if (anEntry < node->data) {
        return getEntry(node->left, anEntry);
    }
    else /*(anEntry > node->data) */{
        return getEntry(node->right, anEntry);
    }
}

template <class T>
inline int BST<T>::getHeight(TreeNode *root)
{
    return 0;
}

template <class T>
typename BST<T>::TreeNode* BST<T>::clear(TreeNode *node)
{
    if (node == nullptr) return nullptr;
        clear(node->left);
        clear(node->right);
        delete node;
        return nullptr;
}

template <class T>
void BST<T>::inOrderTraverse(TreeNode *node)
{
    if (node == nullptr) return;
    inOrderTraverse(node->left);
    std::cout << node->data << " --> ";
    inOrderTraverse(node->right);
}

template <class T>
void BST<T>::preorderTraverse(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    std::cout << node->data << " --> " ;
    preorderTraverse(node->left);
    preorderTraverse(node->right);
}

template <class T>
inline void BST<T>::postorderTraverse(TreeNode *node)
{
    if (node == nullptr) {
        return;
    }
    preorderTraverse(node->left);
    preorderTraverse(node->right);
    std::cout << node->data << " --> " ;
}

template <class T>
inline void BST<T>::clear()
{
    root = clear(root);
    node_count = 0;  
}

template <class T>
inline T BST<T>::getEntry(const T &anEntry) const
{
    TreeNode* node = getEntry(root, anEntry);
        if (node == nullptr) {
            throw std::runtime_error("Entry not found");
        }
        return node->data;
}

template <class T>
inline bool BST<T>::contains(T data)
{   
    TreeNode* node = root;
    node = getEntry(node, data);
    if (node == nullptr) return false;
    
    return true;
}

template <class T>
inline void BST<T>::preorderTraverse()
{
    preorderTraverse(root);
    std::cout << std::endl;
}

template <class T>
inline void BST<T>::inorderTraverse()
{
    inOrderTraverse(root);
    std::cout << std::endl;
}

template <class T>
inline void BST<T>::postOrderTraverse()
{
    postorderTraverse(root);
    std::cout << std::endl;
}