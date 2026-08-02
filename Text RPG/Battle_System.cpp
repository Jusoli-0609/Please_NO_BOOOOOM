#include "Battle_System.h"
#include "Battle_Elite_Skill.h"
#include "Stat_Modifier.h"

#include "Level_Up.h"
#include "Item.h"
#include "Inventory.h"

#include "Monster.h"
#include "Player.h"

#include <iostream>
#include <string>

using namespace std;

//======================================================
// 전투 시작
//======================================================

void Battle(Player* player, Monster& monster, Inventory<Item>& inventory)
{

    if (player == nullptr)
    {
        return;
    }

    int turnCount = 1;

    Show_Battle_Start(player, monster);

    while (true)
    {
        Show_Battle_Status(player, monster, turnCount);

        Player_Turn(player, monster, inventory);

        if (Check_Battle_End(player, monster, inventory))
        {
            break;
        }

        Monster_Turn(player, monster, turnCount);

        if (Check_Battle_End(player, monster, inventory))
        {
            break;
        }

        player->Process_Stat_Modifier_Turn();

        turnCount++;
    }

    Show_Battle_End(player, monster);
}

//======================================================
// UI (UI 담당)
//======================================================

void Show_Battle_Start(Player* player, Monster& monster)
{
    cout << endl;
    cout << "==================================" << endl;
    cout << "          전투 시작!" << endl;
    cout << "==================================" << endl;

    cout << player->Get_Name()
        << " VS "
        << monster.getName()
        << endl;

    cout << "==================================" << endl;
}

void Show_Battle_Status(Player* player, Monster& monster, int turnCount)
{
    cout << endl;
    cout << "==================================" << endl;
    cout << "             "
        << turnCount
        << " TURN"
        << endl;
    cout << "==================================" << endl;


    cout << player->Get_Name()
        << " HP : "
        << player->Get_Hp()
        << endl;


    cout << monster.getName()
        << " HP : "
        << monster.getHP()
        << endl;


    cout << "==================================" << endl;
}

void Show_Battle_Menu()
{
    // UI 선택지

    cout << endl;
    cout << "==============================" << endl;
    cout << "        플레이어 턴" << endl;
    cout << "==============================" << endl;
    cout << "1. 공격" << endl;
    cout << "2. 스킬" << endl;
    cout << "3. 아이템" << endl;
    cout << "==============================" << endl;
    cout << "선택 : ";
}

void Show_Battle_End(Player* player, Monster& monster)
{
    // UI 전투 종료
}

//======================================================
// 플레이어 턴
//======================================================

void Player_Turn(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    //플레이어 차례 (JRPG 턴 개념)

    int menu;

    Show_Battle_Menu();

    cin >> menu;

    switch (menu)
    {
    case ATTACK:
    {
        Attack(player, monster);
        break;
    }

    case SKILL:
    {
        Skill(player, monster);
        break;
    }

    case ITEM:
    {
        Use_Item(player, monster, inventory);
        break;
    }




    default:
    {
        cout << "잘못된 입력입니다." << endl;
        break;
    }
    }
}

void Use_Item(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (player == nullptr)
    {
        return;
    }

    inventory.Use_Item_In_Battle(*player, monster);
}

//======================================================
// 플레이어 공격
//======================================================

void Attack(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return;
    }

    player->Attack(&monster);
}

//======================================================
// 플레이어 스킬
//======================================================

void Skill(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return;
    }

    int menu;

    cout << endl;
    cout << "------ 스킬 ------" << endl;
    cout << "1. 스킬 1" << endl;
    cout << "2. 스킬 2" << endl;
    cout << "3. 스킬 3" << endl;
    cout << "0. 뒤로가기" << endl;
    cout << "선택 : ";

    cin >> menu;

    switch (menu)
    {
    case 1:
        player->Skill1(&monster);
        break;

    case 2:
        player->Skill2(&monster);
        break;

    case 3:
        player->Skill3(&monster);
        break;

    case 0:
        return;

    default:
        cout << "잘못된 입력입니다." << endl;
        break;
    }
}

//======================================================
// 몬스터 턴
//======================================================

void Monster_Turn(Player* player, Monster& monster, int turnCount)
{
    if (player == nullptr)
    {
        return;
    }

    cout << endl;
    cout << "------ 몬스터 턴 ------" << endl;

    if (Check_Elite_Skill(monster, turnCount))
    {
        Execute_Elite_Skill(player, monster);
    }
    else
    {
        Monster_Attack(player, monster);
    }
}

//======================================================
// 몬스터 공격
//======================================================

void Monster_Attack(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return;
    }

    int Before_Player_HP = player->Get_Hp();

    int Damage = monster.getPower() - player->Get_DEF();

    if (Damage < 1)
    {
        Damage = 1;
    }

    int After_HP = Before_Player_HP - Damage;

    if (After_HP < 0)
    {
        After_HP = 0;
    }

    player->Set_Hp(Before_Player_HP - Damage);

    cout << endl;
    cout << "[전투 로그]" << endl;

    cout << monster.getName()
        << "이(가) 공격했습니다!"
        << endl;

    cout << "HP : "
        << Before_Player_HP
        << " → "
        << player->Get_Hp()
        << endl;
}

//======================================================
// 전투 종료
//======================================================

bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (monster.getHP() <= 0)
    {
        cout << endl;
        cout << "==================================" << endl;
        cout << "          전투 승리!" << endl;
        cout << "==================================" << endl;


        player->Remove_Temporary_Modifiers();


        int exp = monster.getExpReward();


        cout << "[보상 획득]" << endl;

        cout << exp
            << " 경험치를 획득했습니다."
            << endl;


        Give_Battle_Item_Reward(player, monster, inventory);


        return true;
    }


    if (player->Get_Hp() <= 0)
    {
        cout << endl;
        cout << "==================================" << endl;
        cout << "          전투 패배!" << endl;
        cout << "==================================" << endl;

        cout << "플레이어가 쓰러졌습니다."
            << endl;


        player->Remove_Temporary_Modifiers();


        return true;
    }


    return false;
}


void Give_Battle_Item_Reward(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (player == nullptr)
    {
        return;
    }


    monster.Generate_Drop_Reward();


    const vector<Item>& dropItems = monster.getDropItems();


    cout << endl;
    cout << "[아이템 획득]" << endl;


    for (const Item& dropItem : dropItems)
    {
        inventory.Add_Or_Increase_Item(dropItem);


        cout << "- "
            << dropItem._Item_Name
            << endl;
    }


    int goldReward = monster.getGoldReward();

    int currentMoney = inventory.Get_Money();


    inventory.Set_Money(
        currentMoney + goldReward
    );


    cout << endl;

    cout << "[재화 획득]" << endl;

    cout << "훈련장려금 "
        << goldReward
        << " 획득!"
        << endl;
}