#include "Equipment.h"
#include "Level_3_Keyboard.h"

Level_3_Keyboard::Level_3_Keyboard()
	: Equipment
	(
		"3키보드",
		7,
		0,
		Equipment_Grade::Middle,
		Equipment_Type::Keyboard,
		R"(+--------+
|MECH++++|
|[______]|
+--------+)",
        "설명",
        6,
        1
    )
{
}
