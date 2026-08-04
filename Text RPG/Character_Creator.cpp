#include <iostream>
#include <string>

#include "Character_Creator.h"
#include "Job_Selection.h"
#include "JYJ.h"
#include "JSR.h"
#include "JWH.h"
#include "LYB.h"
#include "LMR.h"
#include "PSB.h"
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

	case 2:
		return new JSR(name);

	case 3:
		return new JWH(name);

	case 4:
		return new LYB(name);

	case 5:
		return new LMR(name);

	case 6:
		return new PSB(name);

    default:
        return nullptr;
    }
}