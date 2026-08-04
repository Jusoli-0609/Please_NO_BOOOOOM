#include "Equipment.h"
#include "Level_3_Glasses.h"

Level_3_Glasses::Level_3_Glasses()
	: Equipment
	(
		"중급 안경",
		0,
		7,
		Equipment_Grade::Middle,
		Equipment_Type::BlueLight_Glasses,
		R"( .##..##.
( @)(@ )
 '##''##')",
        "드디어 눈에 뭔가 보이기 시작합니다.",
		2,
		1
	)
{
}
