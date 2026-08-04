#include "Equipment.h"
#include "Level_5_Keyboard.h"

Level_5_Keyboard::Level_5_Keyboard()
	: Equipment
	(
		"최상급 키보드",
		16,
		0,
		Equipment_Grade::Best,
		Equipment_Type::Keyboard,
		R"(+--------+
|MASTER{}|
|[______]|
+--------+)",
        "아무리 샷건을 내려쳐도 부서지지 않습니다.",
        6,
        1
    )
{
}