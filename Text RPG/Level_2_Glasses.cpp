#include "Equipment.h"
#include "Level_2_Glasses.h"

Level_2_Glasses::Level_2_Glasses()
	: Equipment
	(
		"하급 안경",
		0,
		4,
		Equipment_Grade::Low,
		Equipment_Type::BlueLight_Glasses,
		R"( .==..==.
(  )(  )
 '==''==')",
        "이제 앞이 뿌옇게 보이지는 않습니다.",
		2,
		1
	)
{
}
