#include <iostream>

#include "Battle_System.h"
#include "JYJ.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"

using namespace std;

int main()
{
    // ==========================
    // 테스트용 플레이어 생성
    // ==========================
    Player* player = new JYJ("테스터");

    // ==========================
    // 테스트용 몬스터 생성
    // ==========================
    Monster monster(Monster_Type::CODE_SNIPPET_WRAITH);

    // ==========================
    // 테스트용 인벤토리 생성
    // ==========================
    Inventory<Item> inventory(20, 100);

    cout << "==============================" << endl;
    cout << "      Battle Test Start" << endl;
    cout << "==============================" << endl;

    Battle(player, monster, inventory);

    delete player;

    return 0;
}