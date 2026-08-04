#include "Equipment.h"
#include "Level_4_Engine.h"

Level_4_Engine::Level_4_Engine()
	: Equipment
	(
		"상급 언리얼 엔진",
		7,
		7,
		Equipment_Grade::High,
		Equipment_Type::Engine,
		R"(+--------+
| UE 5.4 |
| [HIGH] |
+--------+)",
        "렉 없이 돌아가기 시작합니다.",
        8,
        1
    )
{
}
