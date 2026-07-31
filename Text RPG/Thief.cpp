#include "Thief.h"
#include "Monster.h"
#include <iostream>

Thief::Thief(const std::string& name, const int stat[])
    : Player(name, stat)
{
    job = "도적";
    atk += 30;
}

void Thief::attack(Monster* monster)
{
    (void)monster;

    std::cout << name << "이(가) 표창을 던진다!" << std::endl;
}