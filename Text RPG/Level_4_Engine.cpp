#include "Equipment.h"
#include "Level_4_Engine.h"

Level_4_Engine::Level_4_Engine()
	: Equipment
	(
		"4언리얼 엔진",
		7,
		7,
		Equipment_Grade::High,
		Equipment_Type::Engine,
		R"(+--------+
| UE 5.4 |
| [HIGH] |
+--------+)",
"설명",
8
)
{
}
