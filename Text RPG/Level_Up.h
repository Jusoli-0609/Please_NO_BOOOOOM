#pragma once
#include "Player.h"

// Monster 클래스가 존재한다는 것을 미리 알려줌 (전방 선언)
class Monster;

class Level_Up
{
private:
    int _current_level;
    int _current_exp;
    int _max_exp;
    int _stat_points;

public:
    Level_Up();
    ~Level_Up();

    // Monster 참조(&) 전달
    void GainExp(Player* player, const Monster& monster);
    void ProcessLevelUp(Player* player);
};