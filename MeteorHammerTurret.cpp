#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "RotatedBullet.hpp"
#include "Group.hpp"
#include "MeteorHammerTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "ShootEffect.hpp"
#include "RotatedBullet.hpp"
#include "Enemy.hpp"
#include "AmplifierTurret.hpp"

const int MeteorHammerTurret::Price = 20;
MeteorHammerTurret::MeteorHammerTurret(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/turret-8.png", x, y, 200, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
    RemainBullets = 0;
}
void MeteorHammerTurret::CreateBullet() {
/*
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
*/

    Engine::Point down(0, 1);
    Engine::Point up(0, -1);
    Engine::Point right(1, 0);
    Engine::Point left(-1, 0);
    getPlayScene()->BulletGroup->AddNewObject(new RotatedBullet(Position + up * CollisionRadius, right, - ALLEGRO_PI / 4, this));
    getPlayScene()->BulletGroup->AddNewObject(new RotatedBullet(Position + down * CollisionRadius, left, ALLEGRO_PI * 3 / 4, this));
    getPlayScene()->BulletGroup->AddNewObject(new RotatedBullet(Position + left * CollisionRadius, up, ALLEGRO_PI * 5 / 4, this));
    getPlayScene()->BulletGroup->AddNewObject(new RotatedBullet(Position + right * CollisionRadius, down, ALLEGRO_PI / 4, this));
    RemainBullets = 4;
    // Change bullet position to the front of the gun barrel.

    // TODO 4 (2/2): Add a ShootEffect here. Remember you need to include the class.
	//getPlayScene()->EffectGroup->AddNewObject(new ShootEffect(Position.x, Position.y));
    AudioHelper::PlayAudio("gun.wav");
}

void MeteorHammerTurret::Update(float deltaTime)
{
	Sprite::Update(deltaTime);
	imgBase.Position = Position;
	imgBase.Tint = Tint;
    // shoot.
    if (RemainBullets <= 0 && Enabled) {
        CreateBullet();
    }
    PlayScene* scene = getPlayScene();
    auto turrets = scene->TowerGroup->GetObjects();
    for (auto it : turrets) {
        if (dynamic_cast<AmplifierTurret*> (it)) {
            Engine::Point dis = it->Position - Position;
            float distance = dis.Magnitude();
            if (distance <= dynamic_cast<AmplifierTurret*> (it)->CollisionRadius + scene->BlockSize / 2) {
                enhanced = true;
                return;
            }
        }
    }
    enhanced = false;
}
