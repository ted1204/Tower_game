#include <allegro5/base.h>
#include <cmath>
#include <string>

#include "AudioHelper.hpp"
#include "Group.hpp"
#include "Shifter.hpp"
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
#include "GameEngine.hpp"
#include "AmplifierTurret.hpp"
#include <iostream>

const int Shifter::Price = 0;
Shifter::Shifter(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/empty.png", "play/shifter.png", x, y, 0, Price, 0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
void Shifter::CreateBullet() {}
void Shifter::ShiftTurret(int x, int y) {
    PlayScene* scene = getPlayScene();
    auto turrets = scene->TowerGroup->GetObjects();
    auto bullets = scene->BulletGroup->GetObjects();
    int blockSize = scene->BlockSize;
    Turret* pre = scene->preview;
    for (auto it : turrets) {
    std::cout << "in\n";
        if (it->Position.x == x * blockSize + blockSize / 2 && it->Position.y == y * blockSize + blockSize / 2) {
            scene->shifting = true;
            if (dynamic_cast<PlugGunTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<WoodBullet*>(it2) && dynamic_cast<WoodBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->TowerGroup->RemoveObject(it->GetObjectIterator());
                scene->UIBtnClicked(0);
            }
            else if (dynamic_cast<MachineGunTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<MetalBullet*>(it2) && dynamic_cast<MetalBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->TowerGroup->RemoveObject(it->GetObjectIterator());
                scene->UIBtnClicked(1);

            }
            else if (dynamic_cast<DoubleMachineGunTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<MetalBullet*>(it2) && dynamic_cast<MetalBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->TowerGroup->RemoveObject(it->GetObjectIterator());
                scene->UIBtnClicked(-1);
            }
            else if (dynamic_cast<MeteorHammerTurret*>(it)) {
                for (auto it2 : bullets) {
                    if (dynamic_cast<RotatedBullet*>(it2) && dynamic_cast<RotatedBullet*>(it2)->parent == it) {
                        scene->BulletGroup->RemoveObject(it2->GetObjectIterator());
                    }
                }
                scene->TowerGroup->RemoveObject(it->GetObjectIterator());
                scene->UIBtnClicked(2);
            }
            else if (dynamic_cast<AmplifierTurret*>(it)) {
                scene->TowerGroup->RemoveObject(it->GetObjectIterator());
                scene->UIBtnClicked(5);
            }
            break;
        }
    }
}
