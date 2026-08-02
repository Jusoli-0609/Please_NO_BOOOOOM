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
// 전투 시작 Main Loop
//======================================================
void Battle(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (player == nullptr) return;

    int turnCount = 1;
    Show_Battle_Start(player, monster);

    while (true)
    {
        Show_Battle_Status(player, monster, turnCount);

        // 1. 플레이어 턴 (유효한 행동을 할 때까지 진행)
        Player_Turn(player, monster, inventory);
        if (Check_Battle_End(player, monster, inventory)) break;

        // 2. 몬스터 턴
        Monster_Turn(player, monster, turnCount);
        if (Check_Battle_End(player, monster, inventory)) break;

        // 3. 턴 종료 시 지속 버프/디버프 처리
        player->Process_Stat_Modifier_Turn();

        turnCount++;
    }

    Show_Battle_End(player, monster);
}

//======================================================
// UI 함수
//======================================================
void Show_Battle_Start(Player* player, Monster& monster)
{
    cout << endl;
    cout << "==================================" << endl;
    cout << "          전투 시작!" << endl;
    cout << "==================================" << endl;
    cout << player->Get_Name() << " VS " << monster.getName() << endl;
    cout << "==================================" << endl;
}

void Show_Battle_Status(Player* player, Monster& monster, int turnCount)
{
    cout << endl;
    cout << "==================================" << endl;
    cout << "              " << turnCount << " TURN" << endl;
    cout << "==================================" << endl;
    cout << player->Get_Name() << " HP : " << player->Get_Hp() << endl;
    cout << monster.getName() << " HP : " << monster.getHP() << endl;
    cout << "==================================" << endl;
}

void Show_Battle_Menu()
{
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
    // 전투 종료 후 필요한 출력 처리
}

//======================================================
// 플레이어 턴 (행동 성공 시에만 턴 종료)
//======================================================
void Player_Turn(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    bool actionCompleted = false;

    while (!actionCompleted)
    {
        int menu;
        Show_Battle_Menu();
        cin >> menu;

        switch (menu)
        {
        case ATTACK:
            Attack(player, monster);
            actionCompleted = true;
            break;

        case SKILL:
            // 스킬 사용 선택 후 뒤로가기(0)를 한 경우 false 반환
            actionCompleted = Skill_Menu_Process(player, monster);
            break;

        case ITEM:
            Use_Item(player, monster, inventory);
            actionCompleted = true;
            break;

        default:
            cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
            break;
        }
    }
}

void Use_Item(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (player == nullptr) return;
    inventory.Use_Item_In_Battle(*player, monster);
}

void Attack(Player* player, Monster& monster)
{
    if (player == nullptr) return;
    player->Attack(&monster);
}

// 스킬 메뉴 처리 (행동 성공 여부를 bool로 반환하도록 내부 함수 구성)
bool Skill_Menu_Process(Player* player, Monster& monster)
{
    if (player == nullptr) return false;

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
        return true;
    case 2:
        player->Skill2(&monster);
        return true;
    case 3:
        player->Skill3(&monster);
        return true;
    case 0:
        return false; // 뒤로가기 선택 시 플레이어 행동 취소
    default:
        cout << "잘못된 입력입니다." << endl;
        return false;
    }
}

void Skill(Player* player, Monster& monster)
{
    Skill_Menu_Process(player, monster);
}

//======================================================
// 몬스터 턴
//======================================================
void Monster_Turn(Player* player, Monster& monster, int turnCount)
{
    if (player == nullptr) return;

    cout << endl;
    cout << "------ 몬스터 턴 ------" << endl;

    // 튜터는 일반 공격 없이 시험 스킬만 진행
    if (Is_Tutor(monster))
    {
        Execute_Elite_Skill(player, monster);
        return;
    }

    // 엘리트 몬스터 스킬 조건 체크
    if (Check_Elite_Skill(monster, turnCount))
    {
        Execute_Elite_Skill(player, monster);
    }
    else
    {
        Monster_Attack(player, monster);
    }
}

void Monster_Attack(Player* player, Monster& monster)
{
    if (player == nullptr) return;

    int Before_Player_HP = player->Get_Hp();
    int Damage = monster.getPower() - player->Get_DEF();

    if (Damage < 1) Damage = 1;

    int After_HP = Before_Player_HP - Damage;
    if (After_HP < 0) After_HP = 0;

    // 보정된 After_HP를 적용해 체력이 음수가 되는 것 방지
    player->Set_Hp(After_HP);

    cout << endl;
    cout << "[전투 로그]" << endl;
    cout << monster.getName() << "이(가) 공격했습니다!" << endl;
    cout << "HP : " << Before_Player_HP << " → " << player->Get_Hp() << endl;
}

//======================================================
// 전투 종료 및 승리 보상 처리
//======================================================
bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    // 1. 몬스터 처치 (승리)
    if (monster.getHP() <= 0)
    {
        if (Is_Tutor(monster))
        {
            cout << endl;
            cout << "==================================" << endl;
            cout << "        튜터 시험 통과!" << endl;
            cout << "    다음 챕터로 이동합니다." << endl;
            cout << "==================================" << endl;

            player->Remove_Temporary_Modifiers();
            return true;
        }

        cout << endl;
        cout << "==================================" << endl;
        cout << "          전투 승리!" << endl;
        cout << "==================================" << endl;

        player->Remove_Temporary_Modifiers();

        // 경험치 획득
        int exp = monster.getExpReward();
        player->Gain_Exp(exp);

        // 전투 아이템 및 골드 보상 지급
        Give_Battle_Item_Reward(player, monster, inventory);

        return true;
    }

    // 2. 플레이어 사망 (패배)
    if (player->Get_Hp() <= 0)
    {
        cout << endl;
        cout << "==================================" << endl;
        cout << "          전투 패배!" << endl;
        cout << "==================================" << endl;
        cout << "플레이어가 쓰러졌습니다." << endl;

        player->Remove_Temporary_Modifiers();
        return true;
    }

    return false;
}

void Give_Battle_Item_Reward(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (player == nullptr) return;

    monster.Generate_Drop_Reward();
    const vector<Item>& dropItems = monster.getDropItems();

    if (!dropItems.empty())
    {
        cout << endl << "[아이템 획득]" << endl;
        for (const Item& dropItem : dropItems)
        {
            inventory.Add_Or_Increase_Item(dropItem);
            cout << "- " << dropItem._Item_Name << endl;
        }
    }

    int goldReward = monster.getGoldReward();
    if (goldReward > 0)
    {
        int currentMoney = inventory.Get_Money();
        inventory.Set_Money(currentMoney + goldReward);

        cout << endl << "[재화 획득]" << endl;
        cout << "훈련장려금 " << goldReward << " 획득!" << endl;
    }
}