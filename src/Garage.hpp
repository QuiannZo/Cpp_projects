#pragma once

#include  "RBTree/RBTree.hxx"

using ecci::RedBlackTree;

class Garage {
  public:
    RedBlackTree<int, std::string> kartsAceleration;
    RedBlackTree<double, std::string> kartsSpeed;
    RedBlackTree<int, std::string> bikes;
    RedBlackTree<int, std::string> atvs;
    RedBlackTree<int, std::string> tires;
    RedBlackTree<int, std::string> gliders;
  public:
    Garage();
};