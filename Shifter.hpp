#ifndef SHIFTER_HPP_INCLUDED
#define SHIFTER_HPP_INCLUDED

#include "Turret.hpp"
class Shifter : public Turret {
public:
    static const int Price;
    Shifter(float x, float y);
    void CreateBullet() override;
    void ShiftTurret(int mx, int my);
};


#endif // SHIFTER_HPP_INCLUDED
