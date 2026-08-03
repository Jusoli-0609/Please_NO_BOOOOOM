#include "Basic_Sword.h"
#include "Equipment.h"
#include <string>

using namespace std;

Basic_Sword::Basic_Sword()
{Equipment KangShinho_Mouse(
    "강신호의 마우스",
    50,
    10,
    Equipment_Grade::Best,
    Equipment_Type::Mouse,
    R"(
        ______________
       |   강신호     |
       |    Mouse     |
       |______________|
        )",
    "강신호 튜터가 사용하던 마우스",
    3
);
}