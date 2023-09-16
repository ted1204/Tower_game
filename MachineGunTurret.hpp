#ifndef MACHINEGUNTURRET_HPP_INCLUDED
#define MACHINEGUNTURRET_HPP_INCLUDED
#include "Turret.hpp"

class MachineGunTurret : public Turret {
public:
    static const int Price;
    MachineGunTurret(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};


#endif // MACHINEGUNTURRET_HPP_INCLUDED
