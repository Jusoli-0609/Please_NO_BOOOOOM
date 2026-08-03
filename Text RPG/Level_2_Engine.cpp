#include "Equipment.h"
#include "Level_2_Engine.h"

Level_2_Engine::Level_2_Engine()
	: Equipment
	(
		"2언리얼 엔진",
		2,
		2,
		Equipment_Grade::Low,
		Equipment_Type::Engine,
		R"(+--------+
| UE 4.5 |
| [STBL] |
+--------+)",
        "설명",
        8,
        1
    )
{
}
