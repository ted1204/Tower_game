#ifndef SHOOTEFFET_HPP_INCLUDED
#define SHOOTEFFET_HPP_INCLUDED
#include <allegro5/bitmap.h>
#include <memory>
#include <vector>

#include "Sprite.hpp"

class PlayScene;

class ShootEffect : public Engine::Sprite {
protected:
	PlayScene* getPlayScene();
	float timeTicks;
	std::vector<std::shared_ptr<ALLEGRO_BITMAP>> bmps;
	float timeSpan = 0.5;
public:
	ShootEffect(float x, float y);
	void Update(float deltaTime) override;
};


#endif // SHOOTEFFET_HPP_INCLUDED
