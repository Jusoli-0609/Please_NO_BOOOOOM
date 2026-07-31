#include <iostream>
#include "Console_Manager.h"

using namespace std;

void Intro()
{
	Console_Manager Console(120, 40);

	Console.Slow_Print("당신은 8시 55분에 눈을 떴다!", 50);
	Console.Slow_Print("익숙한 ZEP이 보인다!", 50);
	//아스키아트
	Console.Slow_Print("일단 아바타를 생성하자!", 50);
}