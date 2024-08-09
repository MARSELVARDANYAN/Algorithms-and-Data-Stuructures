#include "../Headers/BS_Tree.h"


int main()
{
    BST<int> obj;

    std::cout << "is empty = " << obj.isEmpty() << std::endl;

    obj.setRootData(10);
    obj.add(7);
    obj.add(3);
    obj.add(5);
    obj.add(15);
    obj.add(13);
    obj.add(17);
    obj.add(8);

    obj.inorderTraverse();
    obj.preorderTraverse();
    obj.postOrderTraverse();
    obj.levelOrderTraverse();

    std::cout << "Contains function returned -> " << obj.contains(10) << std::endl;

    std::cout << "Entry == " << obj.getEntry(3) << std::endl;
    
    std::cout << "object is = " << obj.getRootData() << std::endl;

    std::cout << "size is = " << obj.getNumberOfNodes() << std::endl;

    obj.clear();

    std::cout << "size is = " << obj.getNumberOfNodes() << std::endl;


}
