#include "Warrior.h"
#include "Monster.h"
#include <iostream>

Warrior::Warrior(const std::string& name, const int stat[])
    : Player(name, stat)
{
    job = "전사";
    def += 30;
}

void Warrior::attack(Monster* monster)
{
    (void)monster;

    std::cout << name << "이(가) 검을 휘두른다!" << std::endl;
}