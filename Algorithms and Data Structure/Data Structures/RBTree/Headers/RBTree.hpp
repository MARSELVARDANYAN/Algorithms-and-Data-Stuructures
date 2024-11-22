#include "RBTree.h"


template <typename T>
inline RBTree<T>::RBTree(){
    NIL = new TreeNode(0);
    NIL->left = NIL->right = NIL->parent = nullptr;
    root = NIL;
}

template <typename T>
typename RBTree<T>::
TreeNode *RBTree<T>::getMin(TreeNode *node)
{
    if (node == NIL || node->left == NIL) {
        return node; 
    }
    return getMin(node->left);
    
}

template <typename T>
void RBTree<T>::delete_node(T key)
{   
    TreeNode* z = __search(root, key);
    if (z == NIL) {
        throw std::runtime_error("Value not found in the tree.");
    }

    TreeNode* y = z;
    TreeNode* x;
    Color yOriginalColor = y->color;

    if (z->left == NIL) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == NIL) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = getMin(z->right);
        yOriginalColor = y->color;
        x = y->right;
        if (y->parent == z) {
            x->parent = y;
        } else {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;
    if (yOriginalColor == BLACK) {
        deleteFixup(x);
    }
    
}

template <typename T>
typename RBTree<T>::
TreeNode* RBTree<T>::search(const T val)
{
    if (root != NIL) {
        return __search(root, val);
    }
    return root;
}

template <typename T>
void RBTree<T>::clear()
{
    __clear(root);  
}

template <typename T>
void RBTree<T>::preOrder() const
{
    if (root != NIL) {
        __preOrder(root);
        std::cout << std::endl;
    }
    
}

template <typename T>
inline void RBTree<T>::inOrder() const
{
    if (root != NIL) {
        __inOrder(root);
        std::cout << std::endl;
    }
    
}

template <typename T>
void RBTree<T>::postOrder() const
{
    if (root != NIL){
        __postOrder(root);
        std::cout << std::endl;
    }
    
}

template <typename T>
void RBTree<T>::insert(const T& data)
{
    TreeNode* z = new TreeNode(data);
    z->left = NIL;
    z->right = NIL;
    TreeNode* y = NIL;
    TreeNode* x = root;

    while (x != NIL) {
        y = x;
        if (z->val < x->val) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == NIL) {
        root = z; // Tree was empty
    } else if (z->val < y->val) {
        y->left = z;
    } else {
        y->right = z;
    }

    z->color = RED;
    insertFixup(z);
}

template <typename T>
void RBTree<T>::leftRotate(TreeNode *current)
{
    TreeNode* y = current->right;
    current->right = y->left;
    if (y->left != NIL) {
        y->left->parent = current;
    }
    y->parent = current->parent;

    if (current->parent == NIL) {
        root = y;
    }
    else if (current->parent->left == current) {
        current->parent->left = y;
    }
    else{
        current->parent->right = y;
    }

    y->left = current;
    current->parent = y;
    
}

template <typename T>
void RBTree<T>::rightRotate(TreeNode *current)
{
    TreeNode* y = current->left;
    current->left = y->right;

    if (y->right != NIL) {
        y->right->parent = current;
    }

    y->parent = current->parent;

    if (current->parent == NIL) {
        root = y;
    }
    else if (current->parent->left == current) {
        current->parent->left = y;
    }
    else {
        current->parent->right = y;
    }

    y->right = current;
    current->parent = y; 
    
}

template <typename T>
void RBTree<T>::insertFixup(TreeNode *z)
{
    while (z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            TreeNode* y = z->parent->parent->right;
            if (y->color == RED) { // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) { // Case 2
                    z = z->parent;
                    leftRotate(z);
                }
                z->parent->color = BLACK; // Case 3
                z->parent->parent->color = RED;
                rightRotate(z->parent->parent);
            }
        } else {
            TreeNode* y = z->parent->parent->left;
            if (y->color == RED) { // Case 1
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) { // Case 2
                    z = z->parent;
                    rightRotate(z);
                }
                z->parent->color = BLACK; // Case 3
                z->parent->parent->color = RED;
                leftRotate(z->parent->parent);
            }
        }
    }
    root->color = BLACK; 

}

template <typename T>
void RBTree<T>::deleteFixup(TreeNode *x)
{
    while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                TreeNode* w = x->parent->right; // Sibling
                if (w->color == RED) { // Case 1: Sibling is RED
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) { // Case 2: Both children are BLACK
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) { // Case 3: Right child is BLACK
                        w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    // Case 4: Right child is RED
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else { // Symmetric case for right child
                TreeNode* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
}

template <typename T>
inline void RBTree<T>::transplant(TreeNode *current, TreeNode *with)
{
    if (current->parent == NIL) {
        root = with;
    }
    else if (current->parent->left == NIL) {
        with = current->parent->left;
    }
    else{
        with = current->parent->right;
    }
    with->parent = current->parent;
}

template <typename T>
void RBTree<T>::__clear(TreeNode *node)
{
    if (node != NIL) {
        __clear(node->left);
        __clear(node->right);
        delete node;
    }
    
}

template <typename T>
typename RBTree<T>::
TreeNode *RBTree<T>::__search(TreeNode *root, const T value)
{
    if (root->val == value) {
        return root;
    }
    else if (root->val > value) {
        return __search(root->left, value);
    }
    else {
        return __search(root->right, value);
    }
    return NIL;
}

template <typename T>
void RBTree<T>::__preOrder(TreeNode *node) const
{
    if (node != NIL){
        std::cout << node->val << " --> ";
        __preOrder(node->left);
        __preOrder(node->right);
    }
    
}

template <typename T>
void RBTree<T>::__inOrder(TreeNode *node) const
{
    if (node != NIL) {
        __inOrder(node->left);
        std::cout << node->val << " --> ";
        __inOrder(node->right);
    }
    
}

template <typename T>
void RBTree<T>::__postOrder(TreeNode *node) const
{
    if (node != NIL){
        __postOrder(node->left);
        __postOrder(node->right);
        std::cout << node->val << " --> ";
    }
    
}
