#include "Equipment.h"
#include "Level_5_Mouse.h"

Level_5_Mouse::Level_5_Mouse()
	: Equipment
	(
		"5마우스",
		16,
		0,
		Equipment_Grade::Best,
		Equipment_Type::Mouse,
		R"(  .------.
 /[MASTER]\
| <CODE> |
 \______/)",
		"설명",
		5
	)
{
}
