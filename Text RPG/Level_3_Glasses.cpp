#include "Equipment.h"
#include "Level_3_Glasses.h"

Level_3_Glasses::Level_3_Glasses()
	: Equipment
	(
		"3안경",
		0,
		7,
		Equipment_Grade::Middle,
		Equipment_Type::BlueLight_Glasses,
		R"( .##..##.
( @)(@ )
 '##''##')",
		"설명",
		2
	)
{
}
