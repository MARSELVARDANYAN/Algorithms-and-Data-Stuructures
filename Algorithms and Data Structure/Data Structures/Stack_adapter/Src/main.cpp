#include "../Header/stack.h"
#include <iostream>

int main() 
{
    Stack<int> ob{1, 2, 3};

    Stack<int> ob1(ob);

    Stack<int> ob2 = {1, 2, 1, 8};

    Stack<int> ob4{9, 7, 8, 9};

    bool i = (ob1 == ob2);

    std::cout << ob.empty() << std::endl;

    ob.push(4);
    ob.pop();
    ob1.top();
    

    std::cout << i << std::endl;

}