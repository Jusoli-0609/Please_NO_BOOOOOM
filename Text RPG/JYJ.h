#pragma once

#include "Player.h"
#include "Monster.h"

class JYJ : public Player
{
public:

    JYJ(const std::string& name,
        const int stat[]);

    void attack(Monster* monster) override;
};