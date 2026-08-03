#include "Console_Manager.h"
#include "DungeonManager.h"
#include "Inventory.h"
#include "Item.h"
#include "Character_Creator.h"
#include "Player.h"
#include "Equipment.h"
#include "Ascii_Art_Manager.h"


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
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    Ascii_Art_Manager Art_Manager;
    Inventory<Item> inventory(10,100);
    Currently_Equipped_Equipments currently_equipped_equipments;
    Console_Manager console(120, 40);

    console.Set_Console_Size();
    console.Clear();
    console.Set_Cursor_Position(15, 10);

    // 1. 강신호의 마우스 획득
    Equipment KangShinho_Mouse(
        "강신호의 마우스",
        50,                         // 공격력
        10,                         // 방어력

        Equipment_Grade::Best,
        Equipment_Type::Mouse,
        R"(
        ______________
       |   ����ȣ     |
       |    Mouse     |
       |______________|
        )",
        "강신호 형님이 선물하신 고급형 마우스",
        3
    );

    // 2. 장비 전용 인벤토리 생성
    Inventory_For_Equipments_Only Equipment_Inventory;


    // 플레이어 생성
    Player* player = Character_Creator();

    if (player == nullptr)
    {
        cout << "캐릭터 생성 실패!" << endl;
        return 0;
    }

    // 3. 마우스 획득

    Equipment_Inventory.Add_Equipment(KangShinho_Mouse);

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
            dungeonManager.Open_Dungeon(player, inventory);
            break;

        case 2:
            inventory.Print_Inventory_Menu(currently_equipped_equipments,Equipment_Inventory,player);
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
    return 0;
}

