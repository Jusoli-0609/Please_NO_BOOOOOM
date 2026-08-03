#include "Equipment.h"
#include "Level_1_Mouse.h"

Level_1_Mouse::Level_1_Mouse()
	: Equipment
	(
		"1마우스",
		2,
		0,
		Equipment_Grade::Worst,
		Equipment_Type::Mouse,
		R"(  .----.
 /  ||  \
|   ||   |
 \______/)",
		"설명",
		5
	)
{
}