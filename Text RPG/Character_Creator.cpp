#include <iostream>
#include <string>

#include "Character_Creator.h"
#include "Job_Selection.h"
#include "JYJ.h"

Player* Character_Creator()
{
    std::string name;

    std::cout << "캐릭터의 이름을 정해주세요: ";
    std::cin >> name;

    int jobChoice = Job_Selection();

    switch (jobChoice)
    {
    case 1:
        return new JYJ(name);

    default:
        return nullptr;
    }
}