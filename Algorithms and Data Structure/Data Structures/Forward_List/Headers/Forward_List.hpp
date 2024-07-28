#include "../Headers/Forward_list.h"
#include "Forward_list.h"


template <typename T>
LinkedList<T>::LinkedList()
    : head(nullptr)
    , l_size(0)
{}

template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& rhv)
    : LinkedList()
{
    if (rhv.head == nullptr) 
    {
        return;
    }

    head = new Node(rhv.head->data);

    Node* current = rhv.head->next;
    Node* newCurrent = head;

    while (current != nullptr)
    {
        newCurrent->next = new Node(current->data);

        newCurrent = newCurrent->next;
        current = current->next;
    }
    l_size = rhv.l_size;
}



template <typename T>
LinkedList<T>::LinkedList(std::initializer_list<T> initlist) 
        : LinkedList()
{
     for(const T& val : initlist)
     {
        push_back(val);
     }
}

template<typename T>
LinkedList<T>::~LinkedList() 
{
    clear();
}

template <typename T>
void LinkedList<T>::push_back(const T& val)
{
    Node* newNode = new Node(val);
    if (head == nullptr)
    {   
        ++l_size;
        head = newNode;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
        ++l_size;
    }
}

template <typename T>
T& LinkedList<T>::front()
{
    return head->data;
}

template <class T>
typename LinkedList<T>::const_referance
LinkedList<T>::front() const
{
    return head->data;
}

template <typename T>
void LinkedList<T>::print_list()
{
    Node* current = this->head;
    while(current) {
        std::cout << current->data << " ---> ";
        current = current->next;
    }
    std::cout << std::endl; 
}   

template <typename T>
void LinkedList<T>::push_front(const_referance val)
{
    Node* newNode = new Node(val);
    newNode->next = this->head;
    head = newNode;
    ++l_size;
}

template <typename T>
void LinkedList<T>::pop_front()
{
    Node* tmp = this->head;
    tmp = this->head->next; 
    delete head; 
    head = nullptr;
    head = tmp;
    --l_size;
}

template<typename T>
typename LinkedList<T>::iterator 
LinkedList<T>::insert_after(const_iterator index, const_referance val) {
    
    if (index == nullptr) {
        throw std::invalid_argument("Invalid iterator");
    }
    
    Node* current = index.ptr; 
    if (current != nullptr) {
        Node* temp = new Node(val); 
        temp->next = current->next; 
        current->next = temp; 
        
        return iterator(temp); 
    } else {
        throw std::out_of_range("Index out of range");
    }
    ++l_size;
}


template<typename T>
typename LinkedList<T>::iterator 
LinkedList<T>::erase_after(const_iterator pos){
    
    Node* current = pos.ptr; 
    if (current != nullptr && current->next != nullptr) {
        Node* toDelete = current->next; 
        current->next = toDelete->next;
        delete toDelete; 
        return iterator(current->next); 
    } else {
        throw std::out_of_range("Index out of range");
    }
    --l_size;

}

template <class T>
void LinkedList<T>::reverse() noexcept
{
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
    next = current->next; 
    current->next = prev;  
    prev = current;        
    current = next;     
}

head = prev;

}

template <class T>
void LinkedList<T>::merge(LinkedList& other)
{
    Node* current1 = this->head;
    Node* current2 = other.head;
    Node* next1;
    Node* next2;

    while (current1 != nullptr && current2 != nullptr) {
        next1 = current1->next;
        next2 = current2->next;

        current1->next = current2;
        current2->next = next1;

        current1 = next1;
        current2 = next2;
    }

    other.head = current2;
    l_size += other.l_size;

}


template <typename T>
bool LinkedList<T>::empty() const noexcept
{
    if (head) {
        return false;
    }
    return true;
}


template <class T>
void LinkedList<T>::unique()
{
    if (head == nullptr) {
        return;
    }

    Node* current = head;

    while (current != nullptr && current->next != nullptr) {
        Node* runner = current;

        while (runner->next != nullptr) {
            if (runner->next->data == current->data) {
                Node* temp = runner->next;
                runner->next = runner->next->next;
                delete temp;
                --l_size;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }

}


template <class T>
void LinkedList<T>::sort()
{
    
}

template<typename T>
void LinkedList<T>::clear() noexcept
{
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    l_size = 0;
}

template <typename T>
T &LinkedList<T>::operator[](const size_t index)
{
    size_t count{};
    Node* curr = this->head;
    while (curr != nullptr){
        if (count == index){
            return curr->data;
        }
        curr = curr->next;
        ++count;
    }
    throw;
    
}

template <typename T>
typename LinkedList<T>::size_type 
LinkedList<T>::Get_size() const
{
    return l_size;
}

template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::begin()
{
    return iterator(head);
}

template <class T>
typename LinkedList<T>::iterator
LinkedList<T>::end()
{
    return iterator(nullptr);
}

template <class T>
typename LinkedList<T>::const_iterator
LinkedList<T>::cbegin() const 
{
    return const_iterator(head);
}


template <class T>
typename LinkedList<T>::const_iterator
LinkedList<T>::cend() const
{
    return const_iterator(nullptr);
}


template <class T>
LinkedList<T>::const_iterator::const_iterator(const Node* ptr)
    : ptr{ptr}
{}


template <class T>
LinkedList<T>::iterator::iterator(Node* ptr)
    : ptr{ptr}
{}

template <typename T>
typename LinkedList<T>::const_iterator&
LinkedList<T>::const_iterator::operator++()
{   
    ptr = ptr->next;
    return *ptr;
}

template <typename T>
typename LinkedList<T>::const_iterator 
LinkedList<T>::const_iterator::operator++(int)
{
    ptr = ptr->next;
    return *ptr;
} 

template <typename T>
typename LinkedList<T>::iterator&
LinkedList<T>::iterator::operator++()
{   
    ptr = ptr->next;
    return *ptr;
}

template <typename T>
typename LinkedList<T>::iterator 
LinkedList<T>::iterator::operator++(int)
{
   
    ptr = ptr->next;
    return *ptr;
} 

template <typename T>
const T& LinkedList<T>::const_iterator::operator*() const
{
    return *ptr;
} 

template <typename T>
T& LinkedList<T>::iterator::operator*() 
{
    return *this->ptr;
} 