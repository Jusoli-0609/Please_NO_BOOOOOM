#include "Equipment.h"
#include "Level_5_Mouse.h"

Level_5_Mouse::Level_5_Mouse()
	: Equipment
	(
		"최상급 마우스",
		16,
		0,
		Equipment_Grade::Best,
		Equipment_Type::Mouse,
		R"(  .------.
 /[MASTER]\
| <CODE> |
 \______/)",
        "살아 숨쉬는 마우스 그 자체입니다",
		5,
		1
	)
{
}
