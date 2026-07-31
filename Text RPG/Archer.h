#pragma once
#include "Player.h"	

class Archer : public Player
{
public:
    Archer(std::string name, const int stat[]);

    void attack(Monster* monster) override;
};