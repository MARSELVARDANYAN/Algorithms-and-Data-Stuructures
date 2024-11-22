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
inline int BST<T>::getHeight() const
{
    if (root == nullptr) return 0;
    
    return getHeight(root);
    
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
inline typename BST<T>::TreeNode *BST<T>::remove(const T val)
{   
    if(root == nullptr) return root;
    return _remove(root, val);
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
    if (node == nullptr || node->data == anEntry) return node;
     
    if (anEntry < node->data) {
        return getEntry(node->left, anEntry);
    }
    
    return getEntry(node->right, anEntry);
}

template <class T>
inline int BST<T>::__getHeight(TreeNode *node) const
{
    if (node == nullptr) return 0;
    
    int left_height = __getHeight(node->left);
    int right_height = __getHeight(node->right);

    return 1 + std::max(left_height, right_height);
    
}

template <class T>
typename BST<T>::TreeNode* BST<T>::__clear(TreeNode *node)
{
    if (node == nullptr) return nullptr;
        __clear(node->left);
        __clear(node->right);
        delete node;
        return nullptr;
}

template <class T>
void BST<T>::__inOrderTraverse(TreeNode *node) const
{
    if (node == nullptr) return;
    __inOrderTraverse(node->left);
    std::cout << node->data << " --> ";
    __inOrderTraverse(node->right);
}

template <class T>
void BST<T>::__preorderTraverse(TreeNode* node) const
{
    if (node == nullptr) {
        return;
    }
    std::cout << node->data << " --> " ;
    __preorderTraverse(node->left);
    __preorderTraverse(node->right);
}

template <class T>
inline void BST<T>::__postorderTraverse(TreeNode *node) const
{
    if (node == nullptr) {
        return;
    }
    __preorderTraverse(node->left);
    __preorderTraverse(node->right);
    std::cout << node->data << " --> " ;
}

template <class T>
inline void BST<T>::__levelOrderTraverse(TreeNode *node, int level) const
{
    if (node == nullptr) return;
    
    if (level == 1) {
        std::cout << node->data << " --> ";
    }
    else if (level >= 1) {
        __levelOrderTraverse(node->left, level - 1);
        __levelOrderTraverse(node->right, level - 1);
    }    
}

template <class T>
typename BST<T>::TreeNode* BST<T>::get_max(TreeNode *node) const
{
    if(!node || !node->right) return node;
    return get_max(node->right);
}

template <class T>
inline typename BST<T>::TreeNode *BST<T>::get_min(TreeNode *node) const
{
    if(!node || !node->left) return node;
    return get_min(node->left);
}

template <class T>
inline typename BST<T>::TreeNode* BST<T>::_remove(TreeNode* node, const T val)
{
    if(node == nullptr) return node;

    if (node->data > val){
        node->left = _remove(node->left, val);
    }
    else if(node->data < val){
        node->right = _remove(node->right, val);
    }
    else{
        if (node->left == nullptr) {
            TreeNode* tmp = node->right;
            delete node;
            return tmp;
        }
        else if (node->right == nullptr) {
            TreeNode* tmp = node->left;
            delete node;
            return tmp;
        }

        TreeNode* tmp = get_min(node->right);

        node->data = tmp->data;

        node->right = _remove(node->right, tmp->data);

    }
    return node;
}

template <class T>
inline void BST<T>::clear()
{
    root = __clear(root);
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
inline void BST<T>::preOrderTraverse() const
{
    __preorderTraverse(root);
    std::cout << std::endl;
}

template <class T>
inline void BST<T>::inOrderTraverse() const
{
    __inOrderTraverse(root);
    std::cout << std::endl;
}

template <class T>
inline void BST<T>::postOrderTraverse() const
{
    __postorderTraverse(root);
    std::cout << std::endl;
}

template <class T>
inline void BST<T>::levelOrderTraverse() const
{
    int h = __getHeight(root);

    for (size_t i = 1; i <= h; i++) {
        __levelOrderTraverse(root, i);
    }
    std::cout << std::endl;
}
