#include "Tutor_Mouse.h"

Tutor_Mouse::Tutor_Mouse()
	: Equipment
	(
		"손승현 튜터님의 로지텍 마우스",
		22,
		0,
		Equipment_Grade::Tutor,
		Equipment_Type::Mouse,
		R"(  .------.
 / [LOGI] \
|  TUTOR   |
 \________/)",
		"설명",
		5,
		1
	)
{
}