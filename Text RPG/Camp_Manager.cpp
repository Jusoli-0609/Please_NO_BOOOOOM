#include "Camp_Manager.h"
#include <iostream>
#include"Items_Equipments_Repository.h"

using namespace std;

Camp_Manager::Camp_Manager
(
    Player& player,
    Inventory<Item>& inventory,
    Inventory_For_Equipments_Only&
    inventory_for_equipments,
    Currently_Equipped_Equipments&
    currently_equipped_equipments
)
    : player(player),
    inventory(inventory), 
    inventory_for_equipments(inventory_for_equipments), 
    currently_equipped_equipments(currently_equipped_equipments)
{
}

void Camp_Manager::Open_Camp_Menu()
{
    while (true)
    {
        cout << "\n===== 내일배움캠프 재정비소 =====\n";
        cout << "1. 내배캠 119 기본 보급 받기\n";
        cout << "2. 펩 스토어\n";
        cout << "3. 문승호 매니저님의 만물 잡화점\n";
        cout << "4. 김동현 매니저님의 전리품 매입소\n";
        cout << "5. 쿠키의 대장간\n";
        cout << "0. 나가기\n";
        cout << "선택: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (Received_Basic_Items == true)
            {
                cout << "이미 보급을 받았다! 쿠키가 화내며 할퀸다!\n";
                player.SetHP(player.GetHP() - 1);
                break;
            }
            Give_Basic_Training_Item();
            Received_Basic_Items = true;
            break;
        }

        case 2:
        {
            Open_Pep_Store_Menu();
            break;
        }

        case 3:
        {
            Open_General_Store_Menu();
            break;
        }

        case 4:
        {
            Open_Loot_Shop_Menu();
            break;
        }

        case 5:
        {
            Open_Cookie_Blacksmith_Menu();
            break;
        }

        case 0:
        {
            cout << "재정비소에서 나갑니다."  << endl;
            return;
        }

        default:
        {
            cout << "잘못된 선택입니다." << endl;
            break;
        }
        }
    }
}




void Camp_Manager::Give_Basic_Training_Item()
{
    cout << "\n===== 내배캠 119 =====\n";
    cout << "기본 보급품을 지급받았습니다!\n";
}

void Camp_Manager::Open_Pep_Store_Menu()
{
    while (true)
    {
        cout << "\n===== 펩 스토어 =====\n";
        cout << "1. 장비 구매\n";
        cout << "2. 장비 판매\n";
        cout << "0. 뒤로가기\n";
        cout << "선택 : ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (inventory.Get_Money() <= 0)
            {
                cout << "골드가 없다!\n";
                break;
            }
            cout << "기본 CPU를 구매했습니다.\n";
            break;
        }

        case 2:
        {
            // TODO : 판매
            break;
        }

        case 0:
        {
            return;
        }

        default:
        {
            cout << "잘못된 입력입니다.\n";
            break;
        }
        }
    }
}

void Camp_Manager::Open_General_Store_Menu()
{
    cout << "\n===== 문승호 매니저님의 만물 잡화점 =====\n";

    // TODO: 소비 아이템 출력
    // TODO: 구매 처리
}

void Camp_Manager::Open_Loot_Shop_Menu()
{
    cout << "\n===== 김동현 매니저님의 전리품 매입소 =====\n";

    // TODO: 전리품 판매
}

void Camp_Manager::Open_Cookie_Blacksmith_Menu()
{
    while (true)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "[ 쿠키의 코드 대장간 ]" << endl;
        cout << "========================================" << endl;
        cout << "1. 장비 강화" << endl;
        cout << "2. 코드 조각으로 장비 제작" << endl;
        cout << "3. 장비 분해" << endl;
        cout << "0. 뒤로가기" << endl;
        cout << "선택: ";

        int choice = -1;

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "윤재님 얼른 장비강화기능 만들어 주세요" << endl;
            break;
        }

        case 2:
        {
            craft_work_shop.Craft_Item(inventory, inventory_for_equipments);
            break;
        }

        case 3:
        {
            craft_work_shop.Decomposition_Item(inventory_for_equipments, inventory);
            break;
        }

        case 0:
        {
            return;
        }

        default:
        {
            cout << "잘못된 입력이다." << endl;
            break;
        }
        }
    }
}