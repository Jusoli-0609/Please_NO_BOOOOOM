#include "Equipment.h"
#include "Level_5_Engine.h"

Level_5_Engine::Level_5_Engine()
	: Equipment
	(
		"최상급 언리얼 엔진",
		10,
		10,
		Equipment_Grade::Best,
		Equipment_Type::Engine,
		R"(+--------+
| UE 5.X |
| MASTER |
+--------+)",
        "렉이 뭐죠?",
        8,
        350
    )
{
}
