#include "Equipment.h"
#include "Level_1_Glasses.h"

Level_1_Glasses::Level_1_Glasses()
	: Equipment
	(
		"최하급 안경",
		0,
		2,
		Equipment_Grade::Worst,
		Equipment_Type::BlueLight_Glasses,
		R"( .--..--.
(  )(  )
 '--''--')",
        "기스가 하도 나 앞이 보이지 않는 안경",
		2,
		1
	)
{
}
