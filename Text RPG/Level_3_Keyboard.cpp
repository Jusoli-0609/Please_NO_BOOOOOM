#include "Equipment.h"
#include "Level_3_Keyboard.h"

Level_3_Keyboard::Level_3_Keyboard()
	: Equipment
	(
		"중급 키보드",
		7,
		0,
		Equipment_Grade::Middle,
		Equipment_Type::Keyboard,
		R"(+--------+
|MECH++++|
|[______]|
+--------+)",
        "타자 200까지는 가능해집니다.",
        6,
        1
    )
{
}
