#include<iostream>

#include "RBTree/RBTree.hxx"

int main(){
    ecci::RedBlackTree<std::string, int> tree;

    tree.insert("KartOne", 1);
    tree.insert("KartTwo", 2);
    tree.insert("KartThree", 3);

    tree.printInOrder();
    std::cout << std::endl;
    std::cout << "Test: " << tree["KartOne"] << std::endl;
    return 0;
}