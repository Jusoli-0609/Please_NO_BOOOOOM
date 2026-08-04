#include "Equipment.h"
#include "Level_1_Headset.h"

#include "Level_1_Headset.h"

Level_1_Headset::Level_1_Headset()
	: Equipment
	(
		"최하급 헤드셋",
		0,
		2,
		Equipment_Grade::Worst,
		Equipment_Type::Headset,
		R"( /------\
|  L  R  |
|  MIC   |
 \_||||_/)",
        "사플이 뭔가요?",
		4,
		1
	)
{
}