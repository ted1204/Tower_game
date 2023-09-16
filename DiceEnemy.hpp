#ifndef DICEENEMY_HPP_INCLUDED
#define DICEENEMY_HPP_INCLUDED
#include "Enemy.hpp"
class DiceEnemy : public Enemy {
public:
    DiceEnemy(int x, int y);
    void OnExplode() override;
};

#endif // DICEENEMY_HPP_INCLUDED
