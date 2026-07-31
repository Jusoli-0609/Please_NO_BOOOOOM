#pragma once
#include "Player.h"

class Thief : public Player
{
public:
    Thief(const std::string& name, const int stat[]);

    void attack(Monster* monster) override;
};