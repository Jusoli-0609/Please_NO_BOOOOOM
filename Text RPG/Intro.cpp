#include "Intro.h"
#include "Console_Manager.h"
#include "Ascii_Art_Manager.h"

void Intro::Show(Console_Manager& console, Ascii_Art_Manager& art)   // Intro:: 를 붙임
{
    console.Clear();
    console.Set_Cursor_Position(0, 0);
    art.Print("Title.txt");

    console.Set_Cursor_Position(10, 32);
    console.Slow_Print("당신은 눈을 떴다...", 50);
    console.Slow_Print("여기는 어디지?", 50);

    system("pause");
    console.Clear();
}