#include "Equipment.h"
#include "Level_3_Headset.h"

Level_3_Headset::Level_3_Headset()
	: Equipment
	(
		"중급 헤드셋",
		0,
		7,
		Equipment_Grade::Middle,
		Equipment_Type::Headset,
		R"( /------\
|  7.1   |
| <MIC>  |
 \_||||_/)",
        "오 이게 소리란 것이군요",
		4,
		160
	)
{
}