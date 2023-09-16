#ifndef METEORHAMMERTURRET_HPP_INCLUDED
#define METEORHAMMERTURRET_HPP_INCLUDED
#include "Turret.hpp"
#include "RotatedBullet.hpp"

class RotatedBullet;

class MeteorHammerTurret : public Turret {
public:
    int RemainBullets;
    static const int Price;
    MeteorHammerTurret(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};


#endif // METEORHAMMERTURRET_HPP_INCLUDED
