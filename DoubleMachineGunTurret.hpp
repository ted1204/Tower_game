#ifndef DOUBLEMACHINEGUNTURRET_HPP_INCLUDED
#define DOUBLEMACHINEGUNTURRET_HPP_INCLUDED
#include "Turret.hpp"

class DoubleMachineGunTurret : public Turret {
public:
    static const int Price;
    DoubleMachineGunTurret(float x, float y);
    void CreateBullet() override;
    void Update(float deltaTime) override;
};


#endif // DOUBLEMACHINEGUNTURRET_HPP_INCLUDED
