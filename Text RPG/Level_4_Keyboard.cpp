#include "Equipment.h"
#include "Level_4_Keyboard.h"

Level_4_Keyboard::Level_4_Keyboard()
	: Equipment
	(
		"상급 키보드",
		11,
		0,
		Equipment_Grade::High,
		Equipment_Type::Keyboard,
		R"(+--------+
|CUSTOM<>|
|[______]|
+--------+)",
        "300타 그 이상이 가능해집니다.",
        6,
        1
    )
{
}