#include "Equipment.h"
#include "Level_5_Glasses.h"

Level_5_Glasses::Level_5_Glasses()
	: Equipment
	(
		"5안경",
		0,
		16,
		Equipment_Grade::Best,
		Equipment_Type::BlueLight_Glasses,
		R"( .@@..@@.
(@@)(@@)
 '@@''@@')",
		"설명",
		2,
		1
	)
{
}
