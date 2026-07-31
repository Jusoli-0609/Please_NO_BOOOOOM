#pragma once
#include <iostream>

class Player; // 전방 선언

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

    int GetCurrentLevel() const { return _current_level; }
    int GetCurrentExp() const { return _current_exp; }
    int GetMaxExp() const { return _max_exp; }
    int GetStatPoints() const { return _stat_points; }

    void GainExp(Player* player, int amount);
    void ProcessLevelUp(Player* player);
};