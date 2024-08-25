#include "../Headers/AVL.h"


int main()
{
    AVL<int> ob;

    ob.insert(10);
    ob.insert(7);
    ob.insert(3);
    ob.insert(5);
    
    ob.inOrderTraverse();
    ob.levelOrderTraverse();
    ob.postOrderTraverse();   
    ob.preOrderTraverse();

    std::cout << ob.empty();


    return 0;
}
