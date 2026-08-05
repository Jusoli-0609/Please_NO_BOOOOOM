#include "Equipment.h"
#include "Level_1_Keyboard.h"

#include "Level_1_Keyboard.h"

Level_1_Keyboard::Level_1_Keyboard()
	: Equipment
	(
		"최하급 키보드",
		2,
		0,
		Equipment_Grade::Worst,
		Equipment_Type::Keyboard,
		R"(+--------+
|[][][][]|
|[______]|
+--------+)",
       "키가 누른 뒤로 안 올라옵니다.",
        6,
        55
    )
{
}
