#ifndef ROTATEDBULLET_HPP_INCLUDED
#define ROTATEDBULLET_HPP_INCLUDED
#include "Bullet.hpp"

class Enemy;
class Turret;

namespace Engine {
    struct Point;
}  // namespace Engine


class RotatedBullet : public Bullet {
public:
    explicit RotatedBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent);
    void OnExplode(Enemy* enemy) override;
    void Update(float deltaTime) override;
};


#endif // ROTATEDBULLET_HPP_INCLUDED
