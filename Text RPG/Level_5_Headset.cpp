#include "Equipment.h"
#include "Level_5_Headset.h"

Level_5_Headset::Level_5_Headset()
	: Equipment
	(
		"5헤드셋",
		0,
		16,
		Equipment_Grade::Best,
		Equipment_Type::Headset,
		R"( /------\
| MASTER |
| <7.1>  |
 \_||||_/)",
		"설명",
		4,
		1
	)
{
}