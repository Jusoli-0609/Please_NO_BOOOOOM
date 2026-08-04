#include "Equipment.h"
#include "Level_1_Engine.h"

Level_1_Engine::Level_1_Engine()
	: Equipment
	(
		"최하급 언리얼 엔진",
		1,
		1,
		Equipment_Grade::Worst,
		Equipment_Type::Engine,
		R"(+--------+
| UE 4.0 |
| [OLD]  |
+--------+)",
        "맨날 렉 걸리는 희대의 엔진",
        5,
        1
    )
{
}
