#include <iostream>
#include "../Headers/Forward_list.h"

int main()
{
    LinkedList<int> li;

    li.push_front(7);
    li.push_front(8);

    li.print_list();
    li.pop_front();

    li.push_front(5);
    li.push_front(22);
    li.push_front(22);
    li.push_front(22);
    li.push_front(22);
    li.push_front(22);
    li.push_front(22);
    li.push_front(5);

    li.unique();
    li.print_list();

    li.print_list();
    
    std::cout << li[1] << std::endl;

    std::cout << "size == " << li.Get_size();
    li.clear();

}