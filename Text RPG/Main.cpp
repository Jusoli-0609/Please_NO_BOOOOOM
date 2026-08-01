#include <iostream>
#include <limits>

#include "Battle_System.h"
#include "JYJ.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"

using namespace std;

int main()
{
    Player* player = new JYJ("테스터");
    Inventory<Item> inventory(20, 100);

    int menu;

    while (true)
    {
        cout << "\n==================================" << endl;
        cout << "        Battle Test Menu" << endl;
        cout << "==================================" << endl;
        cout << "1. 슬라임과 전투" << endl;
        cout << "2. 인벤토리 확인" << endl;
        cout << "3. 이름으로 아이템 사용" << endl;
        cout << "4. 전투 아이템 사용 테스트" << endl;
        cout << "5. 플레이어 상태 확인" << endl;
        cout << "0. 종료" << endl;
        cout << "==================================" << endl;
        cout << "선택 : ";

        cin >> menu;

        switch (menu)
        {
        case 1:
        {
            Monster monster(Monster_Type::INT_SLIME);
            Battle(player, monster, inventory);
            break;
        }

        case 2:
        {
            inventory.Print_Inventory();
            break;
        }

        case 3:
        {
            string itemName;

            inventory.Print_Inventory();

            cout << "\n사용할 아이템 이름 : ";

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, itemName);

            if (inventory.Use_Item_By_Name(itemName))
            {
                cout << itemName << " 사용 완료!" << endl;
            }
            else
            {
                cout << "아이템 사용 실패!" << endl;
            }

            break;
        }

        case 4:
        {
            Monster monster(Monster_Type::INT_SLIME);

            inventory.Use_Item_In_Battle(*player, monster);

            break;
        }

        case 5:
        {
            player->Print_Status();
            break;
        }

        case 0:
        {
            delete player;
            return 0;
        }

        default:
        {
            cout << "잘못된 입력입니다." << endl;
            break;
        }
        }
    }

    delete player;
    return 0;
}