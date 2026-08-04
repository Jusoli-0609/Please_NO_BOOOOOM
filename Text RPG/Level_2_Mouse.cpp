#include "Equipment.h"
#include "Level_2_Mouse.h"

Level_2_Mouse::Level_2_Mouse()
	: Equipment
	(
		"하급 마우스",
		4,
		0,
		Equipment_Grade::Low,
		Equipment_Type::Mouse,
		R"(  .----.
 / [DPI]\
|   ||   |
 \______/)",
        "클릭이 드디어 되기 시작합니다.",
		5,
		1
	)
{
}
