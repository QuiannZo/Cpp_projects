#include<iostream>

#include "RBTree/RBTree.hxx"
#include <Controller.hpp>

int main(int argc, char* argv[]){
    controller controller;
    controller.readClassData();
    controller.runMenu();
    return 0;
}