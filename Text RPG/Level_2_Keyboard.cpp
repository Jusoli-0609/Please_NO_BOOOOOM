#include "Equipment.h"
#include "Level_2_Keyboard.h"

Level_2_Keyboard::Level_2_Keyboard()
	: Equipment
	(
		"2키보드",
		4,
		0,
		Equipment_Grade::Low,
		Equipment_Type::Keyboard,
		R"(+--------+
|MEMBRANE|
|[______]|
+--------+)",
        "설명",
        6,
        1
    )
{
}