#include "Equipment.h"
#include "Level_2_Mouse.h"

Level_2_Mouse::Level_2_Mouse()
	: Equipment
	(
		"2마우스",
		4,
		0,
		Equipment_Grade::Low,
		Equipment_Type::Mouse,
		R"(  .----.
 / [DPI]\
|   ||   |
 \______/)",
		"설명",
		5
	)
{
}
