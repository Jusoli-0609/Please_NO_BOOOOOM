#pragma once
#include "Player.h"

class Warrior : public Player
{
public:
    Warrior(const std::string& name, const int stat[]);

    void attack(Monster* monster) override;
};