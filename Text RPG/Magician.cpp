#include "Magician.h"
#include "Monster.h"
#include <iostream>

Magician::Magician(const std::string& name, const int stat[])
    : Player(name, stat)
{
    job = "마법사";
    mp += 30;
}

void Magician::attack(Monster* monster)
{
    (void)monster;

    std::cout << name << "이(가) 파이어볼을 발사한다!" << std::endl;
}