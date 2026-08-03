#include "Console_Manager.h"
#include "DungeonManager.h"
#include "Inventory.h"
#include "Item.h"
#include "Character_Creator.h"
#include "Player.h"

#include <iostream>
#include <ctime>

using namespace std;

void PrintLine()
{
    cout << string(50, '=') << endl;
}

void Intro();

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    Console_Manager console(120, 40);

    console.Set_Console_Size();
    console.Clear();
    console.Set_Cursor_Position(15, 10);

    PrintLine();
    Intro();

    // 플레이어 생성
    Player* player = Character_Creator();

    if (player == nullptr)
    {
        cout << "캐릭터 생성 실패!" << endl;
        return 0;
    }

    Inventory<Item> inventory(10, 9999);

    Dungeon_Manager dungeonManager;

    bool gameRunning = true;

    while (gameRunning)
    {
        int menu;

        cout << endl;
        cout << "==============================" << endl;
        cout << "         메인 메뉴" << endl;
        cout << "==============================" << endl;
        cout << "1. 던전" << endl;
        cout << "2. 인벤토리" << endl;
        cout << "3. 상태창" << endl;
        cout << "0. 종료" << endl;
        cout << "==============================" << endl;
        cout << "선택 : ";

        cin >> menu;

        switch (menu)
        {
        case 1:
        {
            dungeonManager.Open_Dungeon(player,inventory);

            if(dungeonManager.Check_Game_Cleared())
            {
                gameRunning =false;
            }

            break;
        }

        case 2:
            inventory.Print_Inventory();
            break;

        case 3:
            player->Print_Status();
            break;

        case 0:
            gameRunning = false;
            break;

        default:
            cout << "잘못된 입력입니다." << endl;
            break;
        }
    }

    delete player;
}
    