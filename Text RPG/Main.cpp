#include "Console_Manager.h"
#include "DungeonManager.h"
#include "Ascii_Art_Manager.h"
#include <iostream>
#include <string>


using namespace std;

void PrintLine()
{
    cout << string(50, '=') << endl;
}
void Intro();

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Console_Manager Console(120, 40);
    Ascii_Art_Manager Art_Manager;
    
    Console.Set_Console_Size();
    Console.Clear();
    Console.Set_Cursor_Position(15, 10);
    Art_Manager.Print("Title.txt");

    Intro();

    //직업 선택
 
    return 0;
}