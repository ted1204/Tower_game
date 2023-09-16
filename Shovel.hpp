#ifndef SHOVEL_HPP_INCLUDED
#define SHOVEL_HPP_INCLUDED
#include "Turret.hpp"
class Shovel : public Turret {
public:
    static const int Price;
    Shovel(float x, float y);
    void CreateBullet() override;
    void RemoveTurret(int mx, int my);
};

#endif // SHOVEL_HPP_INCLUDED
