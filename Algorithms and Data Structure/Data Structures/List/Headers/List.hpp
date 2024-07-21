#include "../Headers/List.h"


template <typename T>
List<T>::List() 
    : count{0}
{
    Node* tmp = new Node(0);
    head = tmp;
    tail = tmp;
}

template <typename T>
List<T>::List(const List<T>& rhv)
    : head{nullptr}
{
    if (rhv.head == nullptr) {
        return;
    }
    Node* current = rhv.head;
    while(current != nullptr)
    {
        
        current = current->next;
    }
    tail = rhv.tail;
}

template <typename T>
List<T>::List(std::initializer_list<T> initlist) 
        : List()
{
     for(const T& val : initlist)
     {
        push_back(val);
     }
}

template<typename T>
List<T>::~List() 
{
    clear();
}

template <typename T>
T& List<T>::front()
{
    return *begin();
}

template <class T>
typename List<T>::const_referance
List<T>::front() const
{
    return *begin();
}

template <class T>
typename List<T>::referance
List<T>::back()
{   
	return *end();
}

template <class T>
typename List<T>::const_referance
List<T>::back() const
{
    return *end();
}

template <typename T>
void List<T>::print_list()
{
    Node* current = head;
    while(current != nullptr) {
        std::cout << current->data << " ---> ";
        current = current->next;
    }
    std::cout << std::endl; 
}   

template <typename T>
void List<T>::push_front(const_referance val)
{
    if (!count) {
        push_back(val);
        return;
    }
    
    Node* newNode = new Node(val);
    newNode->next = head;
    head->prew = newNode;
    head = newNode;
    head->prew = nullptr;
    ++count;
}

template <typename T>
void List<T>::pop_front()
{   
    if (!count) {
        pop_back();
        return;
    }
    
    --count;
    if (!count) {
        Node* cur = head;
        Node* tmp = new Node(0);
        head = tmp;
        tail = tmp;
        delete cur;
        head->next = nullptr;
        head->prew = nullptr;
        return;
    }

    Node* curr = head;
    head = head->next;
    delete curr;
    head->prew = nullptr;
}

template <class T>
void List<T>::push_back(const_referance val)
{   
    Node* new_node = new Node(val);
    
    if (!count) {
        Node* cur = head;
        head = new_node;
        tail = new_node;
        ++count;
        delete cur;
        return;
    }
    
    Node* current = head;

    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = new_node;
    new_node->prew = current;
    tail = new_node;
    ++count;

}

template <class T>
void List<T>::pop_back()
{
    if (!count){
        throw std::out_of_range("Index out of range");
    }

    --count;
    if (!count) {
        Node* cur = head;
        Node* tmp = new Node(0);
        head = tmp;
        tail = tmp;
        delete cur;
        return;
    }

    Node* curr = tail;
    tail = tail->prew;
    delete curr;
    tail->next = nullptr;
    
}

template<typename T>
typename List<T>::iterator List<T>::insert_after(iterator pos, const T& val) {
    if (pos.ptr == nullptr) {
        throw std::invalid_argument("Invalid iterator");
    }
    
     
    if (head == nullptr) {
        Node* cur = new Node(val);
        tail = cur;
        delete head;
        head = tail;
        head->next = nullptr;
        return iterator(head);
    }
    Node* current = pos.ptr;
    
    Node* temp = new Node(val); 
    
    temp->next = current->next; 
    current->next = temp;
    
    if (temp->next) {
        temp->next->prew = temp;
    } else {
        tail = temp; 
    }
    
    temp->prew = current;
    
    return iterator(temp); 
}


template<typename T>
typename List<T>::iterator 
List<T>::erase_after(iterator pos){
    
    Node* current = pos.ptr; 
    if (current != nullptr && current->next != nullptr) {
        Node* toDelete = current->next; 
        current->next = toDelete->next;
        delete toDelete; 
        return iterator(current->next); 
    } else {
        throw std::out_of_range("Index out of range");
}

}

template <class T>
void List<T>::reverse() noexcept
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
void List<T>::merge(List& other)
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

}


template <typename T>
bool List<T>::empty() const noexcept
{
    if (count == 0) {
        true;
    }
    return false;
}


template <class T>
void List<T>::unique()
{
    if (!count) {
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
                --count;
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }

}


template <class T>
void List<T>::sort()
{
    
}

template<typename T>
void List<T>::clear() noexcept
{
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
        --count;
    }
    head = nullptr;
}

template <class T>
typename List<T>::iterator
List<T>::begin()
{
    return iterator(head);
}

template <class T>
typename List<T>::iterator
List<T>::end()
{
    return iterator(tail);
}

template <class T>
typename List<T>::const_iterator
List<T>::cbegin() const 
{
    return const_iterator(head);
}


template <class T>
typename List<T>::const_iterator
List<T>::cend() const
{
    return const_iterator(tail);
}

//CONST_ITERATOR
template <class T>
List<T>::const_iterator::const_iterator(const Node* ptr)
    : ptr{ptr}
{}



template <typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator++()
{   
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator 
List<T>::const_iterator::operator++(int)
{   
    const Node* tmp = ptr;
    ptr = ptr->next;
    return tmp;
} 

template <typename T>
typename List<T>::const_iterator&
List<T>::const_iterator::operator--()
{   
    ptr = ptr->prew;
    return *this;
}

template <typename T>
typename List<T>::const_iterator 
List<T>::const_iterator::operator--(int)
{
    const Node* tmp = ptr;
    ptr = ptr->prew;
    return tmp;
} 

template <typename T>
const T& List<T>::const_iterator::operator*() const
{
    return ptr->data;
} 

//ITERATOR
template <class T>
List<T>::iterator::iterator(Node* ptr)
    : ptr{ptr}
{}

template <typename T>
T& List<T>::iterator::operator*() 
{
    return ptr->data;
} 

template <typename T>
typename List<T>::iterator&
List<T>::iterator::operator++()
{   
    ptr = ptr->next;
    return *this;
}

template <typename T>
typename List<T>::iterator 
List<T>::iterator::operator++(int)
{   
    Node* tmp = ptr;
    ptr = ptr->next;
    return tmp;
} 

template <typename T>
typename List<T>::iterator&
List<T>::iterator::operator--() 
{   
    if (ptr) {
        ptr = ptr->prew;
    }
    return *this;
}

template <typename T>
typename List<T>::iterator 
List<T>::iterator::operator--(int)
{
    Node* tmp = ptr;
    ptr = ptr->prew;
    return tmp;
}