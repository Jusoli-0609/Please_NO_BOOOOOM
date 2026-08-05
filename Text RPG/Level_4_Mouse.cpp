#include "Equipment.h"
#include "Level_4_Mouse.h"

Level_4_Mouse::Level_4_Mouse()
	: Equipment
	(
		"상급 마우스",
		11,
		0,
		Equipment_Grade::High,
		Equipment_Type::Mouse,
		R"(  .------.
 /[MACRO]\
| <CODE> |
 \______/)",
        "아무리 많이 클릭해도 고장이 나지 않습니다.",
		5,
		280
	)
{
}