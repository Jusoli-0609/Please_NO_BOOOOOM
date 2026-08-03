#include "Equipment.h"
#include "Level_1_Keyboard.h"

#include "Level_1_Keyboard.h"

Level_1_Keyboard::Level_1_Keyboard()
	: Equipment
	(
		"1키보드",
		2,
		0,
		Equipment_Grade::Worst,
		Equipment_Type::Keyboard,
		R"(+--------+
|[][][][]|
|[______]|
+--------+)",
"설명",
6
)
{
}
