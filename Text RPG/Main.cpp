#include "Console_Manager.h"
#include "DungeonManager.h"
#include "Inventory.h"
#include "Item.h"

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
    Console_Manager Console(120, 40);

    Console.Set_Console_Size();
    Console.Clear();
    Console.Set_Cursor_Position(15, 10);
    Console.Slow_Print("눈 떠보니 코드 마스터", 50);

    PrintLine();
    Intro();

    return 0;
}