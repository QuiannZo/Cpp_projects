#pragma once

#include<string>

class Part{
  public:
    std::string name;
  public:
    Part();
    Part(std::string name);
};

class Kart : public Part{
  public:
    double aceleration;
    int speed;
  public:
    Kart(std::string name, double aceleration, int speed);
};

class Bike : public Part{
  public:
    double aceleration;
    int speed;
  public:
    Bike(std::string name, double aceleration, int speed);
};

class ATV : public Part{
  public:
    double aceleration;
    int speed;
  public:
    ATV(std::string name, double aceleration, int speed);
};

class Glider : public Part{
  public:
    int delay;
    int airSpeed;
  public:
    Glider(std::string name, int aceleration, int speed);
};

class Tire : public Part{
  public:
    int terrainSpeed;
    int waterSpeed;
    int airSpeed;
  public:
    Tire(std::string name, int terrainSpeed, int waterSpeed, int airSpeed);
};

class Driver{
  public:
    std::string gamerTag;
    std::string character;
  public:
    Driver();
    Driver(std::string gt, std::string ch);
    virtual int calcSpeed(int terrain, int water, int air) = 0;
  public:
    virtual Part getVehicle() = 0;
    virtual Part getTire() = 0;
    virtual Part getGlider() = 0;
    virtual void setVehicle(Part vehicle) = 0;
    virtual void setTire(Part tire) = 0;
    virtual void setGlider(Part glider) = 0;
};

class KartDriver : public Driver {
  public:
    Part kart;
    Part tires;
    Part glider;
  public:
    KartDriver();
    KartDriver(std::string gt, std::string ch, Part kart, Part tires, Part glider);
    int calcSpeed(int terrain, int water, int air) override;
  public:
    Part getVehicle() override;
    Part getTire() override;
    Part getGlider() override;
    void setVehicle(Part vehicle) override;
    void setTire(Part tire) override;
    void setGlider(Part glider) override;
};

class BikeDriver : public Driver {
  public:
    Part bike;
    Part tires;
    Part glider;
  public:
    BikeDriver();
    BikeDriver(std::string gt, std::string ch, Part bike, Part tires, Part glider);
    int calcSpeed(int terrain, int water, int air) override;
  public:
    Part getVehicle() override;
    Part getTire() override;
    Part getGlider() override;
    void setVehicle(Part vehicle) override;
    void setTire(Part tire) override;
    void setGlider(Part glider) override;
};

class ATVDriver : public Driver {
  public:
    Part atv;
    Part tires;
    Part glider;
  public:
    ATVDriver();
    ATVDriver(std::string gt, std::string ch, Part atv, Part tires, Part glider);
    int calcSpeed(int terrain, int water, int air) override;
  public:
    Part getVehicle() override;
    Part getTire() override;
    Part getGlider() override;
    void setVehicle(Part vehicle) override;
    void setTire(Part tire) override;
    void setGlider(Part glider) override;
};