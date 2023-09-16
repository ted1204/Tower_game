#ifndef AMPLIFIERTURRET_HPP_INCLUDED
#define AMPLIFIERTURRET_HPP_INCLUDED

#include "Turret.hpp"

class AmplifierTurret : public Turret {
public:
    static const int Price;
    AmplifierTurret(float x, float y);
    void CreateBullet() override;
    void Update(float delTatime) override;
    void Draw() const override;
};


#endif // AMPLIFIERTURRET_HPP_INCLUDED
