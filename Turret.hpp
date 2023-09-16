#ifndef TURRET_HPP
#define TURRET_HPP
#include <allegro5/base.h>
#include <list>
#include <string>

#include "Sprite.hpp"

class Enemy;
class PlayScene;

class Turret: public Engine::Sprite {
protected:
    bool enhanced;
    int price;
    float coolDown;
    float reload = 0;
    float rotateRadian = 2 * ALLEGRO_PI;
    Sprite imgBase;
    std::list<Turret*>::iterator lockedTurretIterator;
    PlayScene* getPlayScene();
    // Reference: Design Patterns - Factory Method.
    virtual void CreateBullet() = 0;

public:
    bool Enabled = true;
    bool Preview = false;
    Enemy* Target = nullptr;
    Turret(std::string imgBase, std::string imgTurret, float x, float y, float radius, int price, float coolDown);
    void Update(float deltaTime) override;
    virtual void Draw() const override;
	int GetPrice() const;
	void setCoolDown(float cooldown);
	float getCoolDown();
	void setEnhanced(bool enhancing);
	bool getEnhanced();
};
#endif // TURRET_HPP
