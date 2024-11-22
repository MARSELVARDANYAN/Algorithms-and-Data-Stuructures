#include "AVL.h"

template <typename T>
inline AVL<T>::AVL() : root{nullptr}, node_count{0} {}

template <typename T>
inline AVL<T>::~AVL()
{
    this->clear();
}

template <typename T>
inline int AVL<T>::__getHeight(typename BST<T>::TreeNode *node) const
{
    return node == nullptr ? 0 : node->height;
}

template <typename T>
inline int AVL<T>::maxDepth(typename BST<T>::TreeNode *node) const
{
    if (node == nullptr)
            return 0;

        int leftDepth = maxDepth(node->left);
        int rightDepth = maxDepth(node->right);

        return std::max(leftDepth, rightDepth) + 1;
}

template <typename T>
inline void AVL<T>::levelOrderHelper(typename BST<T>::TreeNode *node, int level) const
{
    if (node == nullptr)
            return;

        if (level == 1)
            std::cout << node->data << " --> ";
        else if (level > 1) {
            levelOrderHelper(node->left, level - 1);
            levelOrderHelper(node->right, level - 1);
        }
}

template <typename T>
typename BST<T>::TreeNode* AVL<T>::minValueNode(typename BST<T>::TreeNode *node)
{
    typename BST<T>::TreeNode* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
}

template <typename T>
inline typename BST<T>::TreeNode *AVL<T>::deleteNode(typename BST<T>::TreeNode *root, const T &key)
{
    if (!root) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            typename BST<T>::TreeNode* temp = root->left ? root->left : root->right;

            if (!temp) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp; // Copy the contents of the non-empty child
            delete temp;
        } else {
            // Node with two children
            typename BST<T>::TreeNode* temp = minValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (!root) return root;

    // Step 2: Update the height of the current node
    root->height = 1 + std::max(height(root->left), height(root->right));

    // Step 3: Get the balance factor
    int balance = getBalance(root);

    // Step 4: Balance the tree
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

template <typename T>
inline int AVL<T>::getBalance(typename BST<T>::TreeNode *node)
{
    return node == nullptr ? __getHeight(node->left) - __getHeight(node->right) : 0;
}

template <typename T>
typename BST<T>::TreeNode* AVL<T>::rotateRight(typename BST<T>::TreeNode *node)
{
    typename BST<T>::TreeNode* leftChild = node->left;
    typename BST<T>::TreeNode* T2 = leftChild->right;

    leftChild->right = node;
    node->left = T2;

    node->height = 1 + std::max(__getHeight(node->left), __getHeight(node->right));
    leftChild->height = 1 + std::max(__getHeight(leftChild->left), __getHeight(leftChild->right));

    return leftChild;

}

template <typename T>
typename BST<T>::TreeNode *AVL<T>::rotateLeft(typename BST<T>::TreeNode *node)
{
    typename BST<T>::TreeNode* rightChild = node->right;
    typename BST<T>::TreeNode* leftSubtreeOfRightChild = rightChild->left;
    
    rightChild->left = node;
    node->right = leftSubtreeOfRightChild;
    
    node->height = std::max(__getHeight(node->left), __getHeight(node->right)) + 1;
    rightChild->height = std::max(__getHeight(rightChild->left), __getHeight(rightChild->right)) + 1;
    
    return rightChild;
}

template <typename T>
typename BST<T>::TreeNode *AVL<T>::__insert(typename BST<T>::TreeNode *node, int key)
{
        if (!node) 
            return new typename BST<T>::TreeNode(key);

        if (key < node->data)
            node->left = __insert(node->left, key);
        else if (key > node->data)
            node->right = __insert(node->right, key);
        else
            return node;

        node->height = 1 + std::max(__getHeight(node->left), __getHeight(node->right));

        int balance = getBalance(node);



        if (balance >= 1 && key < node->left->data)
            return rotateRight(node);


        if (balance <= -1 && key > node->right->data)
            return rotateLeft(node);

        if (balance > 1 && key > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

      
        if (balance < -1 && key < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
}

template <typename T>
inline typename BST<T>::TreeNode *AVL<T>::search(int value)
{
    return this->getEntry(root, value);
}

template <typename T>
inline T& AVL<T>::getRootData()
{
    if (root == nullptr) throw std::runtime_error("Root is not found");
    return root->data;    
}

template <typename T>
void AVL<T>::inOrderTraverse() const
{
    this->__inOrderTraverse(root);
    std::cout << std::endl;
}

template <typename T>
inline void AVL<T>::preOrderTraverse() const
{
    this->__preorderTraverse(root);
    std::cout << std::endl;
}

template <typename T>
inline void AVL<T>::postOrderTraverse() const
{
    this->__postorderTraverse(root);
    std::cout << std::endl;
}

template <typename T>
void AVL<T>::levelOrderTraverse() const
{
    int depth = maxDepth(root);
    for (int i = 1; i <= depth; i++) {
        levelOrderHelper(root, i);
    }
    std::cout <<std::endl;
}

template <typename T>
inline void AVL<T>::insert(const T val)
{
    root = __insert(root, val);
    ++node_count;
}

template <typename T>
void AVL<T>::clear()
{
    root = this->__clear(root);
    node_count = 0;  
}

template <typename T>
inline bool AVL<T>::empty() const
{
    return root == nullptr;
}

template <typename T>
inline void AVL<T>::deleteValue(const T &value)
{
    root = deleteNode(root, value);
}
