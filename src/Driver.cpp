#include<string>

#include "Driver.hpp"

Part::Part() : name{""} {}

Part::Part(std::string name) : name{name} {}

Kart::Kart(std::string name, double aceleration, int speed)
: Part(name), aceleration{aceleration}, speed{speed}
{}

Bike::Bike(std::string name, double aceleration, int speed)
: Part(name), aceleration{aceleration}, speed{speed}
{}

ATV::ATV(std::string name, double aceleration, int speed)
: Part(name), aceleration{aceleration}, speed{speed}
{}

Glider::Glider(std::string name, int aceleration, int speed)
: Part(name), delay{delay}, airSpeed{airSpeed}
{}

Tire::Tire(std::string name, int terrainSpeed, int waterSpeed, int airSpeed)
: Part(name), terrainSpeed{terrainSpeed}, waterSpeed{waterSpeed}, airSpeed{airSpeed}
{}

Driver::Driver() : gamerTag{}, character{} {}

Driver::Driver(std::string gt, std::string ch) 
: gamerTag{gt}, character{ch}
{}

// Karts
KartDriver::KartDriver()
: Driver(), kart{}, tires{}, glider{}
{}

KartDriver::KartDriver(std::string gt, std::string ch, Part kart, Part tires, Part glider)
: Driver(gt, ch), kart{kart}, tires{tires}, glider{glider}
{}

int KartDriver::calcSpeed(int terrain, int water, int air) {
    return 0;
}

Part KartDriver::getVehicle() {
    return kart;
}
Part KartDriver::getTire() {
    return tires;
}
Part KartDriver::getGlider() {
    return glider;
}

void KartDriver::setVehicle(Part vehicle){
    kart = vehicle;
}

void KartDriver::setTire(Part tire){
    tires = tire;
}

void KartDriver::setVehicle(Part glider){
    glider = glider;
}

// Bikes
BikeDriver::BikeDriver()
: Driver(), bike{}, tires{}, glider{}
{}

BikeDriver::BikeDriver(std::string gt, std::string ch, Part bike, Part tires, Part glider)
: Driver(gt, ch), bike{bike}, tires{tires}, glider{glider}
{}

int BikeDriver::calcSpeed(int terrain, int water, int air) {
    return 0;
}

Part BikeDriver::getVehicle() {
    return bike;
}
Part BikeDriver::getTire() {
    return tires;
}
Part BikeDriver::getGlider() {
    return glider;
}

void BikeDriver::setVehicle(Part vehicle){
    bike = vehicle;
}

void BikeDriver::setTire(Part tire){
    tires = tire;
}

void BikeDriver::setVehicle(Part glider){
    glider = glider;
}

// ATVS
ATVDriver::ATVDriver()
: Driver(), atv{}, tires{}, glider{}
{}

ATVDriver::ATVDriver(std::string gt, std::string ch, Part atv, Part tires, Part glider)
: Driver(gt, ch), atv{atv}, tires{tires}, glider{glider}
{}

int ATVDriver::calcSpeed(int terrain, int water, int air) {
    return 0;
}

Part ATVDriver::getVehicle() {
    return atv;
}
Part ATVDriver::getTire() {
    return tires;
}
Part ATVDriver::getGlider() {
    return glider;
}

void ATVDriver::setVehicle(Part vehicle){
    atv = vehicle;
}

void ATVDriver::setTire(Part tire){
    tires = tire;
}

void ATVDriver::setVehicle(Part glider){
    glider = glider;
}