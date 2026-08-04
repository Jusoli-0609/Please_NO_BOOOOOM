#include "Equipment.h"
#include "Level_4_Headset.h"

Level_4_Headset::Level_4_Headset()
	: Equipment
	(
		"4헤드셋",
		0,
		11,
		Equipment_Grade::High,
		Equipment_Type::Headset,
		R"( /------\
|  ANC   |
| <MUTE> |
 \_||||_/)",
		"설명",
		4,
		1
	)
{
}