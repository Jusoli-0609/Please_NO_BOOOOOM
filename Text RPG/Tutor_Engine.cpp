#include "Tutor_Engine.h"

Tutor_Engine::Tutor_Engine()
	: Equipment
	(
		"문승현 튜터님의 최고버전 언리얼엔진",
		14,
		14,
		Equipment_Grade::Tutor,
		Equipment_Type::Engine,
		R"(+----------+
|  UE 5.X  |
| <TUTOR>  |
+----------+)",
        "설명",
        8,
        0
    )
{
}