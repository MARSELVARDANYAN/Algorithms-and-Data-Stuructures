#include <iostream>
#include "../Headers/List.h"
#include <list>

int main()
{
     List<int> ob{88, 33, 55, 33, 22, 33, 77};

    ob.push_back(9);
    ob.print_list();

    std::cout << ob.front() << std::endl;
    std::cout << ob.back() << std::endl;

    //ob.push_front(477);
    //ob.print_list();

    ob.pop_front();
    // ob.print_list();

    // //std::cout << ob.head == ob.tail << std::endl;
    ob.pop_back();
    // ob.print_list();
    
    // List<int>::iterator it = ob.end();
    // ob.insert_after(it, 5555);
    ob.print_list();
    ob.unique();
    ob.print_list();
    ob.clear();
    ob.push_back(7);
    ob.print_list();
    // //List<int>::iterator it = ob.begin();
    //  ob.insert_after(ob.begin()++, 6);
    
    // List<int>::iterator t = ob.end()--;
    // std::cout << *t;
}
