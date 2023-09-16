#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Shovel.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"
#include "Collider.hpp"
#include "PlugGunTurret.hpp"
#include "MachineGunTurret.hpp"
#include "DoubleMachineGunTurret.hpp"
#include "MeteorHammerTurret.hpp"
#include "WoodBullet.hpp"
#include "MetalBullet.hpp"
#include "RotatedBullet.hpp"

const int Shovel::Price = 0;
Shovel::Shovel(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/empty.png", "play/shovel.png", x, y, 0, Price, 0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Shovel::CreateBullet() {}
void Shovel::RemoveTurret(int mx, int my) {
    PlayScene* scene = getPlayScene();
    auto turrets = scene->TowerGroup->GetObjects();
    auto bullets = scene->BulletGroup->GetObjects();
    Engine::Point mousePoint(mx, my);
    Engine::Point rectSize(scene->BlockSize, scene->BlockSize);
    Engine::Point diff = rectSize * 1 / 2;
    for (auto it : turrets) {
        if (Engine::Collider::IsPointInRect(mousePoint, it->Position - diff, rectSize)) {
            if (dynamic_cast<PlugGunTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<WoodBullet*>(it2) && dynamic_cast<WoodBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->EarnMoney(PlugGunTurret::Price / 2);
            }
            else if (dynamic_cast<MachineGunTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<MetalBullet*>(it2) && dynamic_cast<MetalBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->EarnMoney(MachineGunTurret::Price / 2);
            }
            else if (dynamic_cast<DoubleMachineGunTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<MetalBullet*>(it2) && dynamic_cast<MetalBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->EarnMoney(DoubleMachineGunTurret::Price / 2);
            }
            else if (dynamic_cast<MeteorHammerTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<RotatedBullet*>(it2) && dynamic_cast<RotatedBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->EarnMoney(MeteorHammerTurret::Price / 2);
            }
            scene->TowerGroup->RemoveObject(it->GetObjectIterator());
            break;
        }
    }
}
