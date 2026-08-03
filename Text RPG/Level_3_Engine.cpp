#include "Equipment.h"
#include "Level_3_Engine.h"

Level_3_Engine::Level_3_Engine()
	: Equipment
	(
		"3언리얼 엔진",
		4,
		4,
		Equipment_Grade::Middle,
		Equipment_Type::Engine,
		R"(+--------+
| UE 5.0 |
| [FAST] |
+--------+)",
"설명",
8
)
{
}
