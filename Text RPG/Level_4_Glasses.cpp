#include "Equipment.h"
#include "Level_4_Glasses.h"

Level_4_Glasses::Level_4_Glasses()
	: Equipment
	(
		"4안경",
		0,
		11,
		Equipment_Grade::High,
		Equipment_Type::BlueLight_Glasses,
		R"( .<>..<>.
(  )(  )
 '<>''<>')",
		"설명",
		2
	)
{
}
