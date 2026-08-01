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

    // ===========================
    // 테스트용 인벤토리 생성
    // ===========================

    Inventory<Item> inventory(10, 9999);

    // 슬롯 10칸 채우기
    for (int i = 0; i < 10; i++)
    {
        Item item;
        item._Item_Name = "쓰레기" + to_string(i + 1);
        item._Item_Count = 20;
        item._Item_Weight = 1;
        item._Item_Price = 1;
        item._Item_Type_Usable = false;
        item._Item_Description = "쓰레기다!";
        item._Item_Ascii_Art = R"(

        .-""""-.
      .'  ____  '.
     /   / __ \   \
    |   | (__) |   |
    |   |      |   |
    |   |______|   |
     \    ____    /
      '._/____\_.'
         /||||\
        /_||||_\

)";

        inventory.Add_Or_Increase_Item(item);
    }

    cout << "\n===== 현재 인벤토리 =====\n";
    inventory.Print_Inventory();

    // 새 아이템 획득

    Item newItem;
    newItem._Item_Name = "전설의 검";
    newItem._Item_Count = 1;
    newItem._Item_Weight = 1;
    newItem._Item_Price = 9999;
    newItem._Item_Type_Usable = false;
    newItem._Item_Description = "전설의 검이다!";
    newItem._Item_Ascii_Art = 
    R"(

       /\
      /  \
     /====\
    /======\
       ||
       ||
       ||
       ||
       ||
=================
   \\______//
      ||||
      ||||
     /____\

)";

    cout << "\n새 아이템을 획득합니다.\n";
    inventory.Add_Or_Increase_Item(newItem);

    cout << "\n===== 결과 =====\n";
    inventory.Print_Inventory();

    return 0;
}