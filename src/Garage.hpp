#pragma once

#include <vector>

#include  "RBTree/RBTree.hxx"
#include "Driver.hpp"

using ecci::RedBlackTree;

class Garage {
  public:
    // Parts by atributes.
    RedBlackTree<int, std::vector<std::string>> KartsAceleration;
    RedBlackTree<double, std::vector<std::string>> KartsSpeed;
    RedBlackTree<int, std::vector<std::string>> BikesAceleration;
    RedBlackTree<double, std::vector<std::string>> BikesSpeed;
    RedBlackTree<int, std::vector<std::string>> ATVsAceleration;
    RedBlackTree<double, std::vector<std::string>> ATVsSpeed;
    RedBlackTree<int, std::vector<std::string>> TiresTSpeed;
    RedBlackTree<int, std::vector<std::string>> TiresWSpeed;
    RedBlackTree<int, std::vector<std::string>> TiresASpeed;
    RedBlackTree<int, std::vector<std::string>> gliders;

    // Tracks by Terrain, water, and air meters.
    RedBlackTree<int, std::vector<std::string>> TrackT;
    RedBlackTree<int, std::vector<std::string>> TrackW;
    RedBlackTree<int, std::vector<std::string>> TrackA;

    // Players.
    // // When creating the driver sons to store here, the code must get the type of kart from the file input to create
    // // and store the object on the list.
    std::vector<Driver> DriverList;

  public:
    Garage();
};