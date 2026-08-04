#include "Tutor_Headset.h"

Tutor_Headset::Tutor_Headset()
	: Equipment
	(
		"강신호 튜터님의 게이밍 헤드셋",
		0,
		22,
		Equipment_Grade::Tutor,
		Equipment_Type::Headset,
		R"( /--------\
| <TUTOR> |
|  [7.1]  |
 \__||||__/)",
		"설명",
		4,
		0
	)
{
}
