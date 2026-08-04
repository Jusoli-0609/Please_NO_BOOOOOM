#define NOMINMAX
#include <Windows.h>
#include "Intro.h"
#include "Console_Manager.h"
#include "Ascii_Art_Manager.h"
#include <iostream>
#include <limits>

void Intro::Show(Console_Manager& console, Ascii_Art_Manager& art)
{
    art.Print("Title.txt");
    console.Print_At(0, 45, "아무 키나 누르면 계속됩니다...");

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get(); //대기
}