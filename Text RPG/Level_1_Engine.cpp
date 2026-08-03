#include "Equipment.h"
#include "Level_1_Engine.h"

Level_1_Engine::Level_1_Engine()
	: Equipment
	(
		"1언리얼 엔진",
		1,
		1,
		Equipment_Grade::Worst,
		Equipment_Type::Engine,
		R"(+--------+
| UE 4.0 |
| [OLD]  |
+--------+)",
"설명",
5
)
{
}
