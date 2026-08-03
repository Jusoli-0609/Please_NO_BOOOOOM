#include "Equipment.h"
#include "Level_3_Mouse.h"

Level_3_Mouse::Level_3_Mouse()
	: Equipment
	(
		"3마우스",
		7,
		0,
		Equipment_Grade::Middle,
		Equipment_Type::Mouse,
		R"(  .----.
 / [RGB]\
|  DPI+ |
 \______/)",
"설명",
		5,
		1
	)
{
}
