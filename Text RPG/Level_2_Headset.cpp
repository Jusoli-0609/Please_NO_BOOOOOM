#include "Equipment.h"
#include "Level_2_Headset.h"

Level_2_Headset::Level_2_Headset()
	: Equipment
	(
		"2헤드셋",
		0,
		4,
		Equipment_Grade::Low,
		Equipment_Type::Headset,
		R"( /------\
| STUDY  |
|  MIC   |
 \_||||_/)",
        "설명",
		4,
		1
	)
{
}