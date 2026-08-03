#include "Equipment.h"
#include "Level_2_Glasses.h"

Level_2_Glasses::Level_2_Glasses()
	: Equipment
	(
		"2안경",
		0,
		4,
		Equipment_Grade::Low,
		Equipment_Type::BlueLight_Glasses,
		R"( .==..==.
(  )(  )
 '==''==')",
		"설명",
		2
	)
{
}
