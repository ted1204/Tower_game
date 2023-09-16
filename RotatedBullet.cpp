#include <allegro5/base.h>
#include <random>
#include <string>
#include <iostream>
#include "DirtyEffect.hpp"
#include "Enemy.hpp"
#include "RotatedBullet.hpp"
#include "Group.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Turret.hpp"
#include "Collider.hpp"
#include "MeteorHammerTurret.hpp"

class Turret;

RotatedBullet::RotatedBullet(Engine::Point position, Engine::Point forwardDirection, float rotation, Turret* parent) :
    Bullet("play/bullet-11.png", 250, 2, position, forwardDirection, rotation - ALLEGRO_PI / 2, parent) {
    if (parent->getEnhanced()) Velocity = Velocity * 2;
    // TODO 3 (2/5): You can imitate the 2 files: 'WoodBullet.hpp', 'WoodBullet.cpp' to create a new bullet.
}
void RotatedBullet::OnExplode(Enemy* enemy)
{
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(2, 5);
    getPlayScene()->GroundEffectGroup->AddNewObject(new DirtyEffect("play/dirty-1.png", dist(rng), enemy->Position.x, enemy->Position.y));
}

void RotatedBullet::Update(float deltaTime) {

    Engine::Point a = (parent->Position - Position);
    Engine::Point ac = a.Normalize() * (Velocity.MagnitudeSquared() / parent->CollisionRadius);
    Velocity = Velocity + ac * deltaTime;
    Rotation = atan2(a.y, a.x) + ALLEGRO_PI * 3/ 4;

	Sprite::Update(deltaTime);
	PlayScene* scene = getPlayScene();
	// Can be improved by Spatial Hash, Quad Tree, ...
	// However simply loop through all enemies is enough for this program.
    auto p = dynamic_cast<MeteorHammerTurret*>(parent);

	for (auto& it : scene->EnemyGroup->GetObjects()) {
		Enemy* enemy = dynamic_cast<Enemy*>(it);
		if (!enemy->Visible)
			continue;
		if (Engine::Collider::IsCircleOverlap(Position, CollisionRadius, enemy->Position, enemy->CollisionRadius)) {
            p->RemainBullets--;
			OnExplode(enemy);
			enemy->Hit(damage);
			getPlayScene()->BulletGroup->RemoveObject(objectIterator);
			return;
		}
	}
	// Check if out of boundary.
	if (!Engine::Collider::IsRectOverlap(Position - Size / 2, Position + Size / 2, Engine::Point(0, 0), PlayScene::GetClientSize())) {
        p->RemainBullets--;
		getPlayScene()->BulletGroup->RemoveObject(objectIterator);
	}

}
