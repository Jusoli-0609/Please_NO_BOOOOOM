#include "Archer.h"
#include <string>
#include <iostream>

Archer::Archer(std::string name, const int stat[])
    : Player(name, stat)
{
    job = "궁수";
    hp += 30;
}

void Archer::attack(Monster* monster)
{
    std::cout
        << name
        << "이 화살을 발사했다!"
        << std::endl;
}