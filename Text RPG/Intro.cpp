#include "Intro.h"
#include "Console_Manager.h"
#include "Ascii_Art_Manager.h"

void Intro::Show(Console_Manager& console, Ascii_Art_Manager& art)
{
    art.Print("Title.txt");

    console.Slow_Print("당신은 8시 55분에 눈을 떴다!", 50);
    console.Slow_Print("익숙한 ZEP이 보인다!", 50);
    console.Slow_Print("일단 아바타를 생성하자!", 50);
}