#include "Equipment.h"
#include "Level_4_Mouse.h"

Level_4_Mouse::Level_4_Mouse()
	: Equipment
	(
		"4마우스",
		11,
		0,
		Equipment_Grade::High,
		Equipment_Type::Mouse,
		R"(  .------.
 /[MACRO]\
| <CODE> |
 \______/)",
        "설명",
		5,
		1
	)
{
}