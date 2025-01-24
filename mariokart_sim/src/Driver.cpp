#include<string>

#include "Driver.hpp"

Part::Part() : name{""} {}

Part::Part(std::string name, double aceleration, int speed) 
: name{name}, aceleration{aceleration}, speed{speed} {}

// Part kart.
Kart::Kart(std::string name, double aceleration, int speed)
: Part(name, aceleration, speed)
{}

double Kart::getAceleration() {
    return aceleration;
}

int Kart::getSpeed(){
    return speed;
}

// Part bike.
Bike::Bike(std::string name, double aceleration, int speed)
: Part(name, aceleration, speed)
{}

double Bike::getAceleration() {
    return aceleration;
}

int Bike::getSpeed(){
    return speed;
}

// Part ATV.
ATV::ATV(std::string name, double aceleration, int speed)
: Part(name, aceleration, speed)
{}

double ATV::getAceleration() {
    return aceleration;
}

int ATV::getSpeed(){
    return speed;
}

// Part glider.
Glider::Glider() : name{}, delay{}, airSpeed{}
{}

Glider::Glider(std::string name, int delay, int airSpeed)
: name{name}, delay{delay}, airSpeed{airSpeed}
{}

int Glider::getDelay(){
    return delay;
}

int Glider::getAirSpeed(){
    return airSpeed;
}

// Part tire.
Tire::Tire() : name{}, terrainSpeed{}, waterSpeed{}, airSpeed{}
{}

Tire::Tire(std::string name, int terrainSpeed, int waterSpeed, int airSpeed)
: name{name}, terrainSpeed{terrainSpeed}, waterSpeed{waterSpeed}, airSpeed{airSpeed}
{}

int Tire::getTerrainSpeed(){
    return terrainSpeed;
}

int Tire::getWaterSpeed(){
    return waterSpeed;
}

int Tire::getAirSpeed(){
    return airSpeed;
}

// Base class driver.
Driver::Driver() : gamerTag{}, character{}, kart{}, tires{}, glider{}{}

Driver::Driver(std::string gt, std::string ch, Part kart, Tire tires, Glider glider) 
: gamerTag{gt}, character{ch}, kart{kart}, tires{tires}, glider{glider}
{}

// Karts
KartDriver::KartDriver()
: Driver()
{}

KartDriver::KartDriver(std::string gt, std::string ch, Part kart, Tire tires, Glider glider)
: Driver(gt, ch, kart, tires, glider)
{}

int KartDriver::calcSpeed(int terrain, int water, int air) {
    //terrain.
    double terrainSpeed = ((0.5*terrain) * kart.aceleration) + kart.speed + (1.1 * tires.terrainSpeed) - (0.5 * glider.delay);
    //water.
    double waterSpeed = ((0.7*water) * kart.aceleration) + kart.speed + (1.2*tires.waterSpeed) - (0.7*glider.delay);
    //air.
    double airSpeed = ((0.5*air) * kart.aceleration) + kart.speed - (0.9*tires.airSpeed) + (0.7*glider.airSpeed);
    //return sum.
    return (terrainSpeed + waterSpeed + airSpeed); 
}

Part KartDriver::getVehicle() {
    return kart;
}
Tire KartDriver::getTire() {
    return tires;
}
Glider KartDriver::getGlider() {
    return glider;
}

void KartDriver::setVehicle(Part vehicle){
    kart = vehicle;
}

void KartDriver::setTire(Tire tire){
    tires = tire;
}

void KartDriver::setGlider(Glider glider){
    glider = glider;
}

// Bikes
BikeDriver::BikeDriver()
: Driver()
{}

BikeDriver::BikeDriver(std::string gt, std::string ch, Part bike, Tire tires, Glider glider)
: Driver(gt, ch, kart, tires, glider)
{}

int BikeDriver::calcSpeed(int terrain, int water, int air) {
    //terrain.
    double terrainSpeed = ((0.4*terrain) * kart.aceleration) + kart.speed + (1.2 * tires.terrainSpeed) - (0.4 * glider.delay);
    //water.
    double waterSpeed = ((0.7*water) * kart.aceleration) + kart.speed + (1.2*tires.waterSpeed) - (0.7*glider.delay);
    //air.
    double airSpeed = ((0.5*air) * kart.aceleration) + kart.speed - (0.7*tires.airSpeed) + (0.9*glider.airSpeed);
    //return sum.
    return (terrainSpeed + waterSpeed + airSpeed); 
}

Part BikeDriver::getVehicle() {
    return kart;
}
Tire BikeDriver::getTire() {
    return tires;
}
Glider BikeDriver::getGlider() {
    return glider;
}

void BikeDriver::setVehicle(Part vehicle){
    kart = vehicle;
}

void BikeDriver::setTire(Tire tire){
    tires = tire;
}

void BikeDriver::setGlider(Glider glider){
    glider = glider;
}

// ATVS
ATVDriver::ATVDriver()
: Driver()
{}

ATVDriver::ATVDriver(std::string gt, std::string ch, Part atv, Tire tires, Glider glider)
: Driver(gt, ch, kart, tires, glider)
{}

int ATVDriver::calcSpeed(int terrain, int water, int air) {
    //terrain.
    double terrainSpeed = ((0.6*terrain) * kart.aceleration) + kart.speed + (1.0 * tires.terrainSpeed) - (0.6 * glider.delay);
    //water.
    double waterSpeed = ((0.7*water) * kart.aceleration) + kart.speed + (1.2*tires.waterSpeed) - (0.7*glider.delay);
    //air.
    double airSpeed = ((0.4*air) * kart.aceleration) + kart.speed - (0.68*tires.airSpeed) - (0.8*glider.airSpeed);
    //return sum.
    return (terrainSpeed + waterSpeed + airSpeed); 
}

Part ATVDriver::getVehicle() {
    return kart;
}
Tire ATVDriver::getTire() {
    return tires;
}
Glider ATVDriver::getGlider() {
    return glider;
}

void ATVDriver::setVehicle(Part vehicle){
    kart = vehicle;
}

void ATVDriver::setTire(Tire tire){
    tires = tire;
}

void ATVDriver::setGlider(Glider glider){
    glider = glider;
}