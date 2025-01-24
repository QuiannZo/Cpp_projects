#pragma once

#include<string>

class Part{
  public:
    std::string name;
    double aceleration;
    int speed;
  public:
    Part();
    Part(std::string name, double aceleration, int speed);
};

class Kart : public Part{
  public:
    Kart(std::string name, double aceleration, int speed);
    double getAceleration();
    int getSpeed();
    void setAceleration(double aceleration);
    void setSpeed(int speed);
};

class Bike : public Part{
  public:
    Bike(std::string name, double aceleration, int speed);
    double getAceleration();
    int getSpeed();
    void setAceleration(double aceleration);
    void setSpeed(int speed);
};

class ATV : public Part{
  public:
    ATV(std::string name, double aceleration, int speed);
    double getAceleration();
    int getSpeed();
    void setAceleration(double aceleration);
    void setSpeed(int speed);
};

class Glider{
  public:
    std::string name;
    int delay; 
    int airSpeed;
  public:
    Glider();
    Glider(std::string name, int delay, int airSpeed);
    int getDelay();
    int getAirSpeed();
    void setDelay(int delay);
    void setAirSpeed(int airSpeed);
};

class Tire{
  public:
    std::string name;
    int terrainSpeed;
    int waterSpeed;
    int airSpeed;
  public:
    Tire();
    Tire(std::string name, int terrainSpeed, int waterSpeed, int airSpeed);
    int getTerrainSpeed();
    int getWaterSpeed();
    int getAirSpeed();
    void setTerrainSpeed(int terrainSpeed);
    void setWaterSpeed(int waterSpeed);
    void setAirSpeed(int airSpeed);
};

class Driver{
  public:
    Part kart;
    Tire tires;
    Glider glider;
  public:
    std::string gamerTag;
    std::string character;
  public:
    Driver();
    Driver(std::string gt, std::string ch, Part kart, Tire tires, Glider glider);
    virtual int calcSpeed(int terrain, int water, int air) = 0;
  public:
    virtual Part getVehicle() = 0;
    virtual Tire getTire() = 0;
    virtual Glider getGlider() = 0;
    virtual void setVehicle(Part vehicle) = 0;
    virtual void setTire(Tire tire) = 0;
    virtual void setGlider(Glider glider) = 0;
};

class KartDriver : public Driver {
  public:
    KartDriver();
    KartDriver(std::string gt, std::string ch, Part kart, Tire tires, Glider glider);
    int calcSpeed(int terrain, int water, int air);
  public:
    Part getVehicle() override;
    Tire getTire() override;
    Glider getGlider() override;
    void setVehicle(Part vehicle) override;
    void setTire(Tire tire) override;
    void setGlider(Glider glider) override;
};

class BikeDriver : public Driver {
  public:
    BikeDriver();
    BikeDriver(std::string gt, std::string ch, Part bike, Tire tires, Glider glider);
    int calcSpeed(int terrain, int water, int air) override;
  public:
    Part getVehicle() override;
    Tire getTire() override;
    Glider getGlider() override;
    void setVehicle(Part vehicle) override;
    void setTire(Tire tire) override;
    void setGlider(Glider glider) override;
};

class ATVDriver : public Driver {
  public:
    ATVDriver();
    ATVDriver(std::string gt, std::string ch, Part atv, Tire tires, Glider glider);
    int calcSpeed(int terrain, int water, int air) override;
  public:
    Part getVehicle() override;
    Tire getTire() override;
    Glider getGlider() override;
    void setVehicle(Part vehicle) override;
    void setTire(Tire tire) override;
    void setGlider(Glider glider) override;
};