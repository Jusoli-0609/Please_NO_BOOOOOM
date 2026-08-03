#include "Equipment.h"
#include "Level_1_Headset.h"

#include "Level_1_Headset.h"

Level_1_Headset::Level_1_Headset()
	: Equipment
	(
		"1헤드셋",
		0,
		2,
		Equipment_Grade::Worst,
		Equipment_Type::Headset,
		R"( /------\
|  L  R  |
|  MIC   |
 \_||||_/)",
		"설명",
		4
	)
{
}