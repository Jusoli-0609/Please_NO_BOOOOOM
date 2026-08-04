#include "Equipment.h"
#include "Level_5_Headset.h"

Level_5_Headset::Level_5_Headset()
	: Equipment
	(
		"최상급 헤드셋",
		0,
		16,
		Equipment_Grade::Best,
		Equipment_Type::Headset,
		R"( /------\
| MASTER |
| <7.1>  |
 \_||||_/)",
		"평소에 듣지 못하는 소리도 듣게 됩니다.",
		4,
		1
	)
{
}