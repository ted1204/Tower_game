#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "MetalBullet.hpp"
#include "Group.hpp"
#include "DoubleMachineGunTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "AmplifierTurret.hpp"

const int DoubleMachineGunTurret::Price = 100;
DoubleMachineGunTurret::DoubleMachineGunTurret(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/turret-2.png", x, y, 250, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
void DoubleMachineGunTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();

    Engine::Point leftvector = Engine::Point(-sin(Rotation - ALLEGRO_PI / 2), cos(Rotation - ALLEGRO_PI / 2));
    Engine::Point rightvector = Engine::Point(sin(Rotation - ALLEGRO_PI / 2), -cos(Rotation - ALLEGRO_PI / 2));

    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new MetalBullet(Position + normalized * 36 + leftvector * 8, diff, rotation, this));
    getPlayScene()->BulletGroup->AddNewObject(new MetalBullet(Position + normalized * 36 + rightvector * 8, diff, rotation, this));
    // TODO 4 (2/2): Add a ShootEffect here. Remember you need to include the class.
    AudioHelper::PlayAudio("gun.wav");
}

void DoubleMachineGunTurret::Update(float deltaTime)
{
    Turret::Update(deltaTime);
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
