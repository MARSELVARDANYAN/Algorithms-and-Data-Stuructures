#ifndef __STACK__
#define __STACK__
#include "../../Vector/Headers/vector.h"
#include <vector>
#include <initializer_list>
#include <iostream>

template <typename T, typename Container = Vector<T>>
class Stack
{
    private:
        Container ob;

    public:
        using value_type = T;
        using Container_type = Container;
        using size_type = std::size_t;
        using referance = value_type&;
        using const_referance = const value_type&;
       

    public:
        Stack();
        Stack(const Stack & rhv);
        Stack(Stack&& rhv);
        Stack(std::initializer_list<value_type> init);
        template <typename InputIt>
        Stack(InputIt first, InputIt last);
        ~Stack();

        const Stack& operator=(const Stack& rhv);
        Stack& operator=(Stack&& rhv);
        
        
        referance top();
        const_referance top()const;

        size_type Size();
        bool empty();

        void push(const_referance elem);
        void pop();

    public:
        bool operator==(const Stack& other);
        bool operator!=(const Stack& other);
        bool operator<(const Stack& other);
        bool operator<=(const Stack& other);
        bool operator>(const Stack& other);
        bool operator>=(const Stack& other);
        
};


#include "../Header/stack.hpp"

#endif

