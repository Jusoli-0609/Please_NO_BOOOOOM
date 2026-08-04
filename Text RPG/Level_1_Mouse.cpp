#include "Equipment.h"
#include "Level_1_Mouse.h"

Level_1_Mouse::Level_1_Mouse()
	: Equipment
	(
		"최하급 마우스",
		2,
		0,
		Equipment_Grade::Worst,
		Equipment_Type::Mouse,
		R"(  .----.
 /  ||  \
|   ||   |
 \______/)",
        "생쥐가 더 일을 잘합니다.",
		5,
		1
	)
{
}