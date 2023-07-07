#pragma once

#include <vector>

#include  "RBTree/RBTree.hxx"
#include "Driver.hpp"

using ecci::RedBlackTree;

class Garage {
  public:
    // Parts by atributes.
    RedBlackTree<int, std::string> KartsAceleration;
    RedBlackTree<double, std::string> KartsSpeed;
    RedBlackTree<int, std::string> BikesAceleration;
    RedBlackTree<double, std::string> BikesSpeed;
    RedBlackTree<int, std::string> ATVsAceleration;
    RedBlackTree<double, std::string> ATVsSpeed;
    RedBlackTree<int, std::string> TiresTSpeed;
    RedBlackTree<int, std::string> TiresWSpeed;
    RedBlackTree<int, std::string> TiresASpeed;
    RedBlackTree<int, std::string> gliders;

    // Tracks by Terrain, water, and air meters.
    RedBlackTree<int, std::string> TrackT;
    RedBlackTree<int, std::string> TrackW;
    RedBlackTree<int, std::string> TrackA;

    // Players.
    // // When creating the driver sons to store here, the code must get the type of kart from the file input to create
    // // and store the object on the list.
    std::vector<Driver> DriverList;

  public:
    Garage();
};