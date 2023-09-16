#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "MetalBullet.hpp"
#include "Group.hpp"
#include "MachineGunTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "AmplifierTurret.hpp"

const int MachineGunTurret::Price = 50;
MachineGunTurret::MachineGunTurret(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/turret-1.png", x, y, 250, Price, 1.5) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
void MachineGunTurret::CreateBullet() {
    Engine::Point diff = Engine::Point(cos(Rotation - ALLEGRO_PI / 2), sin(Rotation - ALLEGRO_PI / 2));
    float rotation = atan2(diff.y, diff.x);
    Engine::Point normalized = diff.Normalize();
    // Change bullet position to the front of the gun barrel.
    getPlayScene()->BulletGroup->AddNewObject(new MetalBullet(Position + normalized * 36, diff, rotation, this));
    // TODO 4 (2/2): Add a ShootEffect here. Remember you need to include the class.
    AudioHelper::PlayAudio("gun.wav");
}

void MachineGunTurret::Update(float deltaTime)
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
