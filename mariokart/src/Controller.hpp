#pragma once

#include <iostream>
#include <random>
#include <string>
#include <fstream>

#include<Garage.hpp>

using std::string;

class controller{
  public:
    Garage garageForController;
    controller();
    ~controller();
  public:
    void trim(string& str);
    void readClassData();
    void printParts(string piece);
    void bestCombinationForTrack(string track);
    // Sumo todas las distancias y aplico para el total.
    void bestCombinationForAllTracks();
    void avgFinishingPos(string playerName);
    void bestCombinationForTracks(string track1, string track2, string track3, string track4);
    void runMenu();
};