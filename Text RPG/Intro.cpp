#include "Intro.h"
#include "Console_Manager.h"
#include "Ascii_Art_Manager.h"

void Intro::Show(
    Console_Manager& console,
    Ascii_Art_Manager& art
)
{
    console.Clear();
    art.Print("Title.txt");
    console.Print_At(40,console.Get_Height() - 3,"Press Any Key To Start...");

    console.Wait_For_Key("");
}