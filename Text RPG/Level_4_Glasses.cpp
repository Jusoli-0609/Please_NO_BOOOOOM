#include "Equipment.h"
#include "Level_4_Glasses.h"

Level_4_Glasses::Level_4_Glasses()
	: Equipment
	(
		"상급 안경",
		0,
		11,
		Equipment_Grade::High,
		Equipment_Type::BlueLight_Glasses,
		R"( .<>..<>.
(  )(  )
 '<>''<>')",
        "드디어 1.0의 시력을 갖추게 됩니다.",
		2,
		1
	)
{
}
