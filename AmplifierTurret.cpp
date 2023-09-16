#include <allegro5/base.h>
#include <allegro5/color.h>
#include <allegro5/allegro_primitives.h>


#include <cmath>
#include <string>
#include <list>
#include "AudioHelper.hpp"
#include "Group.hpp"
#include "AmplifierTurret.hpp"
#include "PlayScene.hpp"
#include "Point.hpp"

const int AmplifierTurret::Price = 100;
AmplifierTurret::AmplifierTurret(float x, float y) :
    // TODO 3 (1/5): You can imitate the 2 files: 'PlugGunTurret.hpp', 'PlugGunTurret.cpp' to create a new turret.
    Turret("play/tower-base.png", "play/amplifier.png", x, y, 150, Price, 0) {
    // Move center downward, since we the turret head is slightly biased upward
    Anchor.y += 8.0f / GetBitmapHeight();
}
void AmplifierTurret::CreateBullet() {}

void AmplifierTurret::Update(float deltaTime)
{
	Sprite::Update(deltaTime);
	imgBase.Position = Position;
	imgBase.Tint = Tint;
	if (!Enabled)
		return;
}
void AmplifierTurret::Draw() const
{
    if (Preview) {
		al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(0, 255, 0, 50));
	}
	else {
        al_draw_filled_circle(Position.x, Position.y, CollisionRadius, al_map_rgba(255, 0, 255, 50));
	}
	imgBase.Draw();
	Sprite::Draw();
	if (PlayScene::DebugMode) {
		// Draw target radius.
		al_draw_circle(Position.x, Position.y, CollisionRadius, al_map_rgb(0, 0, 255), 2);
	}
}
