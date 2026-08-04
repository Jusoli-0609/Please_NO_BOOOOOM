#include "Equipment.h"
#include "Level_2_Headset.h"

Level_2_Headset::Level_2_Headset()
	: Equipment
	(
		"하급 헤드셋",
		0,
		4,
		Equipment_Grade::Low,
		Equipment_Type::Headset,
		R"( /------\
| STUDY  |
|  MIC   |
 \_||||_/)",
        "주변 소음이라는 것이 무엇인지 깨닫게 됩니다.",
		4,
		1
	)
{
}