#include "Equipment.h"
#include "Level_4_Keyboard.h"

Level_4_Keyboard::Level_4_Keyboard()
	: Equipment
	(
		"4키보드",
		11,
		0,
		Equipment_Grade::High,
		Equipment_Type::Keyboard,
		R"(+--------+
|CUSTOM<>|
|[______]|
+--------+)",
        "설명",
        6,
        1
    )
{
}