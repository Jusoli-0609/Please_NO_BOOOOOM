#include "Basic_Mouse.h"
#include "Equipment.h"


Basic_Mouse::Basic_Mouse()
    : Equipment(
        "기본 마우스",
        10,
        0,
        Equipment_Grade::Low,
        Equipment_Type::Mouse,
        "...",
        "...",
        5
    )
{
}