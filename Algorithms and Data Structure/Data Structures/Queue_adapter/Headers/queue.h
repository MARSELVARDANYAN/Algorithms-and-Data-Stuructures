#ifndef __QUEUE__
#define __QUEUE__
#include <deque>
#include <initializer_list>
#include <iostream>


template <typename T, typename Container = std::deque<T>>
class Queue
{
    public:
        //Member types
        using value_type = T;
        using size_type = std::size_t;
        using referance = value_type&;
        using const_referance = const value_type&;
        using continer_type = Container;

    public:
        Queue();
        Queue(const Queue& rhv);
        Queue(Queue&& other);
        Queue(std::initializer_list<value_type> init);
        template <typename InputIt>
        Queue(InputIt first, InputIt last);
        ~Queue();

        const Queue& operator=(const Queue& rhv);
        const Queue& operator=(Queue&& rhv);

    public:
        //Element access
        referance front();
        const_referance front() const;

        referance back();
        const_referance back() const;

    public:
        //Capasity
        bool empty() const;
        size_type size() const;

    public:
        //Modifiers
        void push(const_referance val);
        void pop();

    public:
        bool operator==(const Queue& other);
        bool operator!=(const Queue& other);
        bool operator<(const Queue& other);
        bool operator<=(const Queue& other);
        bool operator>(const Queue& other);
        bool operator>=(const Queue& other);

    private:
        continer_type ob;
};

  

#include "../Headers/queue.hpp"

#endif

    
