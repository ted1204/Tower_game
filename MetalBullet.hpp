#ifndef METALBULLET_HPP_INCLUDED
#define METALBULLET_HPP_INCLUDED
#include "Bullet.hpp"

class Enemy;
class Turret;
namespace Engine {
    struct Point;
}  // namespace Engine

class MetalBullet : public Bullet {
public:
    explicit MetalBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
};


#endif // METALBULLET_HPP_INCLUDED
