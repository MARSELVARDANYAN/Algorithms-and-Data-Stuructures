#include "../Headers/RBTree.h"

int main(){
    
    RBTree<int> ob;

    ob.insert(40);
    ob.insert(50);
    ob.insert(30);
    ob.insert(10);
    ob.insert(12);
    ob.insert(100);
    ob.insert(105);
    ob.insert(38);
    //ob.postOrder();
    ob.delete_node(40);
    //ob.inOrder();

}