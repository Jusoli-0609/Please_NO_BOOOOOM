#include "Equipment.h"
#include "Level_4_Headset.h"

Level_4_Headset::Level_4_Headset()
	: Equipment
	(
		"상급 헤드셋",
		0,
		11,
		Equipment_Grade::High,
		Equipment_Type::Headset,
		R"( /------\
|  ANC   |
| <MUTE> |
 \_||||_/)",
		"오 이것이 사플이라는 것이군요",
		4,
		1
	)
{
}