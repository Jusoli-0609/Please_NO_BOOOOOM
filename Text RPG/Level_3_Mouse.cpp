#include "Equipment.h"
#include "Level_3_Mouse.h"

Level_3_Mouse::Level_3_Mouse()
	: Equipment
	(
		"중급 마우스",
		7,
		0,
		Equipment_Grade::Middle,
		Equipment_Type::Mouse,
		R"(  .----.
 / [RGB]\
|  DPI+ |
 \______/)",
"여러번 눌러도 씹히지 않기 시작합니다",
		5,
		170
	)
{
}
