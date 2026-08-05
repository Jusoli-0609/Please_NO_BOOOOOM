#include "Tutor_Glasses.h"

Tutor_Glasses::Tutor_Glasses()
	: Equipment
	(
		"김하늘 튜터님의 도수높은 안경",
		0,
		22,
		Equipment_Grade::Tutor,
		Equipment_Type::BlueLight_Glasses,
		R"( .@@..@@.
(@@)(@@)
 '@@''@@')",
		"오류를 포착했다.이 안경과 함께라면 두려운 것이 없습니다.",
		2,
		1
	)
{
}
