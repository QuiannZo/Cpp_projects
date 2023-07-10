#include "Garage.hpp"

Garage::Garage(){
    
}

Garage::~Garage(){
    for (Driver* driver : DriverList) {
        delete driver;
    }
}