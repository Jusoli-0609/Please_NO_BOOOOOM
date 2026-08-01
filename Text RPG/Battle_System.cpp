#include "Battle_System.h"
#include "Item.h"
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
        Use_Item(player, inventory);
        break;
    }



    default:
    {
        cout << "잘못된 입력입니다." << endl;
        break;
    }
    }
}

void Use_Item(Player* player, Inventory<Item>& inventory)
{
    // 인벤토리 아이템

    cout << "아이템 기능 준비 중입니다." << endl;
}

//======================================================
// 플레이어 공격
//======================================================

void Attack(Player* player, Monster& monster)
{
    int Before_Monster_HP = monster.getHP();

    int Damage = player->Calculate_Damage(
        1.0f, // ATK 계수
        0.0f, // DEF 계수
        0.0f, // HP 계수
        0.0f, // MP 계수
        0.0f, // SNE  이거 용도가????
        0.0f, // AGI 이건 또 뭐지????
        monster.getDefence()
    );


    monster.setHP(Before_Monster_HP - Damage);


    cout << endl;
    cout << "공격!" << endl;

    cout << monster.getName()
        << "에게 "
        << Damage
        << " 데미지!" << endl;


    cout << monster.getName()
        << " HP : "
        << Before_Monster_HP
        << " -> "
        << monster.getHP()
        << endl;
}

//======================================================
// 플레이어 스킬
//======================================================

void Skill(Player* player, Monster& monster)
{
    // 직업 스킬
}

//======================================================
// 몬스터 턴
//======================================================

void Monster_Turn(Player* player, Monster& monster, int turnCount)
{
    // 몬스터 차례

    cout << endl;
    cout << "------ 몬스터 턴 ------" << endl;

    if (Check_Monster_Skill(monster, turnCount))
    {
        Monster_Skill(player, monster);
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
    int Before_Player_HP = player->Get_Hp();

    int Damage = monster.getPower() - player->Get_DEF();

    if (Damage < 1)
    {
        Damage = 1;
    }

    player->Set_Hp(Before_Player_HP - Damage);

    cout << monster.getName()
        << "의 공격!" << endl;

    cout << "플레이어 HP : "
        << Before_Player_HP
        << " -> "
        << player->Get_Hp()
        << endl;
}


//======================================================
// 몬스터 스킬
//======================================================
void Code_Snippet_Question(Player* player, Monster& monster)
{
    cout << endl;
    cout << "=================================" << endl;
    cout << "코드 스니펫의 망령이 문제를 냅니다!" << endl;
    cout << "=================================" << endl;

    cout << "다음 코드의 출력 결과를 입력하세요." << endl;
    cout << endl;

    cout << "게임 개발 시나리오에서 Character -> Warrior, Mage, Archer 구조를 설계할 때," << endl;
    cout << "각 직업 클래스가Character로부터 공통 속성(HP,MP)과 이동 기능을 물려받아" << endl;
    cout << "각자의 고유 스킬만 추가하였습니다. 이 설계에서 가장 주도적으로 활용된 OOP특성은?" << endl;

    cout << "총 4종류가 있으니까 잘 보고 입력하라고!" << endl;
    cout << "-추상화, 다형성, 캡슐화, 상속-" << endl;

    string answer;

    cout << endl;
    cout << "정답 : ";
    cin >> answer;

    if (answer == "상속")
    {
        cout << "정답이다!!!" << endl;
        cout << "망령의 공격을 무효화했습니다." << endl;


    }
    else
    {
        cout << "틀렸어!!" << endl;
        cout << "망령이 분노합니다!" << endl;

        int damage = monster.getPower() * 2;

        player->Set_Hp(player->Get_Hp() - damage);

        cout << damage << " 피해를 받았습니다." << endl;
    }
}

void Monster_Skill(Player* player, Monster& monster)
{
    switch (monster.getMonsterType())
    {
    case Monster_Type::CODE_SNIPPET_WRAITH:
    {
        Code_Snippet_Question(player, monster);

        break;
    }

    default:
    {
        break;
    }
     
    }
}


//======================================================
// 전투 종료
//======================================================
bool Check_Monster_Skill(Monster& monster, int turnCount)
{
    if (monster.getMonsterGrade() != Monster_Grade::ELITE)
    {
        return false;
    }

    switch (monster.getMonsterType())
    {
    case Monster_Type::CODE_SNIPPET_WRAITH:
    {
        if (turnCount % 3 == 0)
        {
            return true;
        }

        break;
    }

    default:
        break;
    }

    return true;
}

bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (monster.getHP() <= 0)
    {
        cout << endl;
        cout << "전투 승리!" << endl;


        int exp = monster.getExpReward();

        player->Gain_Exp(exp);

        cout << exp
            << " 경험치를 획득했습니다."
            << endl;


        cout << monster.getDropItemName()
            << " 획득!" << endl;


        return true;
    }


    if (player->Get_Hp() <= 0)
    {
        cout << endl;
        cout << "전투 패배!" << endl;

        return true;
    }


    return false;
}

