#include "BS_Tree.h"

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
   if (root == nullptr) return 0;
        std::queue<TreeNode*> nodeQueue;
        nodeQueue.push(root);
        int height = 0;

        while (!nodeQueue.empty()) {
            int levelSize = nodeQueue.size();
            for (int i = 0; i < levelSize; ++i) {
                TreeNode* node = nodeQueue.front();
                nodeQueue.pop();

                if (node->left) nodeQueue.push(node->left);
                if (node->right) nodeQueue.push(node->right);
            }
            ++height;
        }

        return height;
}

template <class T>
int BST<T>::getNumberOfNodes()
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

}

template <class T>
inline bool BST<T>::add(T newData)
{   

    if (root == nullptr) {
        root = new TreeNode(newData);
        ++node_count;
        return true;
    }
    
    TreeNode* node = root;

    while (node != nullptr) {
        if (node->data > newData) {
            if (node->left == nullptr) {
                node->left = new TreeNode(newData);
                ++node_count;
                return true;
            }
            node = node->left;
        }
        else if (node->data < newData) {
            if (node->right == nullptr) {
                node->right = new TreeNode(newData);
                ++node_count;
                return true;
            } 
            node = node->right;
        }else{
            return false;
        } 
    }
    
    return true;
}

template <class T>
T BST<T>::getEntry(const T &anEntry) const
{   

    if (root == nullptr) {
        throw std::runtime_error("Entry not found");
    }

    TreeNode* node = root;
    
    while (node != nullptr) {
        if (node->data == anEntry) {
            return node->data;
        }
        else if (anEntry < node->data) {
            if (node->left == nullptr) {
                throw std::runtime_error("Entry not found");
            }
            node = node->left;
        }
        else if(anEntry > node->data) {
            if (node->right == nullptr) {
                throw std::runtime_error("Entry not found");
            }
            node = node->right;
        }
    }
    return -1;
}

template <class T>
void BST<T>::clear()
{   
    if (root == nullptr) return;

        std::stack<TreeNode*> nodeStack;
        nodeStack.push(root);

        while (!nodeStack.empty()) {
            TreeNode* node = nodeStack.top();
            nodeStack.pop();

            if (node->left) nodeStack.push(node->left);
            if (node->right) nodeStack.push(node->right);

            delete node;
        }

        root = nullptr;
        node_count = 0;
    
}

template <class T>
void BST<T>::inorderTraverse() const
{
    if (root == nullptr) return;

        std::stack<TreeNode*> stack;
        TreeNode* current = root;

        while (current != nullptr || !stack.empty()) {
            while (current != nullptr) {
                stack.push(current);
                current = current->left;
            }

            current = stack.top();
            stack.pop();

            std::cout << current->data << " --> ";

            current = current->right;
        }
}

template <class T>
inline void BST<T>::postorderTraverse() const
{
    if (root == nullptr) return;

    std::stack<TreeNode*> st(root);
    std::stack<T> out;

    while (!st.empty()) {
        
        TreeNode * node = st.top();
        st.pop();
        out.push(node->data);

        if (node->left != nullptr) {
            st.push(node->left);
        }
        if (node->right != nullptr) {
            st.push(node->right);
        } 
    }
    
    while (!out.empty()) {
        std::cout << out.top() << " ";
        out.pop();
    } 
}

template <class T>
inline void BST<T>::levelOrderTraverse() const
{
    if (root == nullptr) return;

    std::queue<TreeNode*> qu;
    qu.push(root);

    while (!qu.empty()) {
        
        TreeNode* node = qu.front();
        qu.pop();
        std::cout << node->data << " ";

        if (node-left != nullptr) {
            qu.push(node->left);
        }
        if (node->right != nullptr) {
            qu.push(node->right);
        }          
    }
        
}

template <class T>
void BST<T>::preorderTraverse() const 
{
    if (root == nullptr) return;

        std::stack<TreeNode*> stack;
        stack.push(root);

        while (!stack.empty()) {
            TreeNode* node = stack.top();
            stack.pop();

            std::cout << node->data << " --> ";

            if (node->right != nullptr) {
                stack.push(node->right);
            }
            if (node->left != nullptr) {
                stack.push(node->left);
            }
        }
}

template <class T>
inline bool BST<T>::contains(T data)
{   
    if (root == nullptr) {
        return false;
    }
    
    TreeNode* node = root;
    
    while (node != nullptr) {
        if (node->data == data) {
            return true;
        }
        else if(node->data > data) {
            if (node->left == nullptr) {
                return false;
            }
            node = node->left;
        }
        else if (node->data < data) {
            if (node->right == nullptr) {
                return false;
            }
            node = node->right;
        }    
    }
    return true;
}

