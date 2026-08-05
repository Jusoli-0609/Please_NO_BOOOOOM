#include "Equipment.h"
#include "Level_2_Keyboard.h"

Level_2_Keyboard::Level_2_Keyboard()
	: Equipment
	(
		"하급 키보드",
		4,
		0,
		Equipment_Grade::Low,
		Equipment_Type::Keyboard,
		R"(+--------+
|MEMBRANE|
|[______]|
+--------+)",
        "드디어 키가 올라오긴 합니다.",
        6,
        100
    )
{
}