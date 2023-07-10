#pragma once

#include <iostream>
#include <random>
#include <string>
#include <fstream>

#include<Garage.hpp>

class controller{
  public:
    Garage garageForController;
    controller();
  public:
    void trim(std::string& str);
    void readClassData(int argc, char* argv[]);
    void printParts(std::string piece);
    void bestCombinationForTrack(std::string track);
    void runMenu();
};