#include "Equipment.h"
#include "Level_1_Glasses.h"

Level_1_Glasses::Level_1_Glasses()
	: Equipment
	(
		"1안경",
		0,
		2,
		Equipment_Grade::Worst,
		Equipment_Type::BlueLight_Glasses,
		R"( .--..--.
(  )(  )
 '--''--')",
        "설명",
		2,
		1
	)
{
}
