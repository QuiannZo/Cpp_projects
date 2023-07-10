#include<iostream>

#include "RBTree/RBTree.hxx"
#include <Controller.hpp>

int main(int argc, char* argv[]){
    /*
    ecci::RedBlackTree<std::string, int> tree;
    ecci::RedBlackTree<std::string, int> treeTwo;

    tree.insert("KartOne", 1);
    tree.insert("KartTwo", 2);
    tree.insert("KartThree", 3);
    tree.insert("KartFour", 4);
    tree.insert("KartFive", 5);
    tree.insert("KartSix", 6);

    tree.printInOrder();
    std::cout << std::endl;
    treeTwo = tree;
    std::cout << "Test: " << treeTwo["KartOne"] << std::endl;
    */

    controller controller;
    controller.readClassData();
    controller.runMenu();
    return 0;
}