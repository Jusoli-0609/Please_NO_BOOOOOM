#include "JYJ.h"
#include "Monster.h"

#include <iostream>

using namespace std;

JYJ::JYJ
(
    const std::string& name,
    const int stat[]
)
    : Player(name, stat)
{
    job = "JYJ";
}

void JYJ::attack(Monster* monster)
{
    (void)monster;

    cout << name
        << "이 공격했다!"
        << endl;
}