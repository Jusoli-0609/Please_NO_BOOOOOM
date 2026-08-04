#include "Tutor_Keyboard.h"

Tutor_Keyboard::Tutor_Keyboard()
	: Equipment
	(
		"박은일 튜터님의 갈축 키보드",
		22,
		0,
		Equipment_Grade::Tutor,
		Equipment_Type::Keyboard,
		R"(+----------+
| [BROWN]  |
| <TUTOR>  |
+----------+)",
        "키보드가 저절로 코드를 알잘딱하게 써줍니다.",
        6,
        1
    )
{
}
