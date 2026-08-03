#include "Equipment.h"
#include "Level_5_Keyboard.h"

Level_5_Keyboard::Level_5_Keyboard()
	: Equipment
	(
		"5키보드",
		16,
		0,
		Equipment_Grade::Best,
		Equipment_Type::Keyboard,
		R"(+--------+
|MASTER{}|
|[______]|
+--------+)",
"설명",
6
)
{
}