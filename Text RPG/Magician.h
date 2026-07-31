#pragma once
#include "Player.h"

class Magician : public Player
{
public:
    Magician(const std::string& name, const int stat[]);

    void attack(Monster* monster) override;
};