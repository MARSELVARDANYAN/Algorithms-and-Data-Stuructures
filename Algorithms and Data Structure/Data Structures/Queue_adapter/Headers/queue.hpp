
#include "../Headers/queue.h"

template <typename T, typename Container>
Queue<T, Container>::Queue()
    : ob()
{}

template <typename T, typename Container>
Queue<T, Container>::Queue(const Queue& rhv) 
    : ob(rhv.ob)
{}

template <typename T, typename Container>
Queue<T, Container>::Queue(Queue && other)
    : ob(std::move(other.ob))
{}

template <typename T, typename Container>
Queue<T, Container>::Queue(std::initializer_list<value_type> init)
    : ob()
{
    for (auto &i : init) {
        ob.push_back(i);
    }
    
}

template <typename T, typename Container>
template <typename InputIt>
Queue<T, Container>::Queue(InputIt first, InputIt last)
    : ob(first, last)
{}

template <typename T, typename Container>
Queue<T, Container>::~Queue()
{}


template <typename T, typename Container>
const Queue<T, Container>& 
Queue<T, Container>::operator=(const Queue& rhv)
{   
    if (this != &rhv) {
        ob = rhv.ob;
    }
    return *this;
    
}


template<typename T , typename Container>
const Queue<T, Container>& 
Queue<T,Container>::operator=(Queue&& other)
{
    if (this != &other) {        
        ob = std::move(other.ob);
    }

    return *this; 
}

template <typename T, typename Container>
typename Queue<T, Container>::referance
Queue<T, Container>::front()
{
    return ob.front();
}

template <typename T, typename Container>
typename Queue<T, Container>::const_referance
Queue<T, Container>::front() const
{
    return ob.front();
}

template <typename T, typename Container>
typename Queue<T, Container>::referance
Queue<T, Container>::back()
{
    return ob.back();
}

template <typename T, typename Container>
typename Queue<T, Container>::const_referance
Queue<T, Container>::back() const
{
    return ob.back();
}

template <typename T, typename Container>
bool 
Queue<T, Container>::empty() const
{
    return ob.empty();
}

template <typename T, typename Container>
typename Queue<T, Container>::size_type
Queue<T, Container>::size() const
{
    return ob.size();
}

template <typename T, typename Container>
void 
Queue<T, Container>::push(const_referance val)
{
    ob.push_back(val);
}

template <typename T, typename Container>
void 
Queue<T, Container>::pop()
{
    if (ob.empty()) {
        throw 1;
    }
    
    ob.pop_front();
}

template <class T, class Container>
bool Queue<T, Container>::operator==(const Queue& rhv)
{
    return ob == rhv.ob;
}

//Operator !=
template <class T, class Container>
bool Queue<T, Container>::operator!=(const Queue& rhv)
{
    return ob != rhv.ob;
}

//Operator >
template <class T, class Container>
bool Queue<T, Container>::operator>(const Queue& rhv)
{
    return ob > rhv.ob;
}

//Operator <
template <class T, class Container>
bool Queue<T, Container>::operator<(const Queue& rhv)
{
    return ob < rhv.ob;
}

//Operator <=
template <class T, class Container>
bool Queue<T, Container>::operator<=(const Queue& rhv)
{
    return ob <= rhv.ob;
}

//Operator >=
template <class T, class Container>
bool Queue<T, Container>::operator>=(const Queue& rhv)
{
    return ob >= rhv.ob;
}
