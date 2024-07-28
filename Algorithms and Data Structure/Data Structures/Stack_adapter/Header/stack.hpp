#include "../Header/stack.h"

template <typename T, typename Container>
Stack<T, Container>::Stack()
    : ob()
{}


template <typename T, typename Container>
Stack<T, Container>::Stack(const Stack& rhv)
    : ob(rhv.ob)
{}


template <typename T, typename Container>
Stack<T, Container>::Stack(Stack&& rhv)
{   
    ob = rhv.ob;
    rhv.ob = {nullptr};
    
}


template <typename T, typename Container>
Stack<T, Container>::Stack(std::initializer_list<T> init)
{
    for (auto &i : init)
    {
        ob.push_back(i);
    }
    
}

template <typename T, typename Container>
template <typename InputIt>
Stack<T, Container>::Stack(InputIt first, InputIt last)
{
    ob.insert(ob.end(), first, last);
}


template <typename T, typename Container>
const Stack<T, Container>& 
Stack<T, Container>::operator=(const Stack& rhv)
{
    if (this != &rhv) {
        ob.clear();
        ob = (rhv.ob);
    }

    return *this;
    
}

template<typename T , typename Container>
Stack<T,Container>& 
Stack<T,Container>::operator=(Stack&& rhv){
    if (this != &rhv) {        
        ob = std::move(rhv.ob);
    }

    return *this; 
}


template <typename T, typename Container>
Stack<T, Container>::~Stack()
{}


template <typename T, typename Container>
void 
Stack<T, Container>::push(const_referance elem)
{
    ob.push_back(elem);
}


template <typename T, typename Container>
void 
Stack<T, Container>::pop()
{
    ob.pop_back();
}


template <typename T, typename Container>
typename Stack<T, Container>::referance
Stack<T, Container>::top()
{
    return ob.back();
}

template <typename T, typename Container>
typename Stack<T, Container>::const_referance 
Stack<T, Container>::top()const
{
    return ob.back();
}

template <typename T, typename Container>
typename Stack<T, Container>::size_type
Stack<T, Container>::Size()
{
    return ob.size();
}


template <typename T, typename Container>
bool 
Stack<T, Container>::empty()
{
    return ob.empty();
}


//comparison operators
template <class T, class Container>
bool Stack<T, Container>::operator==(const Stack& other)
{
    return ob == other.ob;
}


template <class T, class Container>
bool Stack<T, Container>::operator!=(const Stack& other)
{
    return ob != other.ob;
}

template <class T, class Container>
bool Stack<T, Container>::operator>(const Stack& other)
{
    return ob > other.ob;
}

template <class T, class Container>
bool Stack<T, Container>::operator<(const Stack& other)
{
    return ob < other.ob;
}


template <class T, class Container>
bool Stack<T, Container>::operator<=(const Stack& other)
{
    return ob <= other.ob;
}


template <class T, class Container>
bool Stack<T, Container>::operator>=(const Stack& other)
{
    return ob >= other.ob;
}