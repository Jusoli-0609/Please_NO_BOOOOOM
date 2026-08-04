#include "Battle_System.h"
#include "Battle_Elite_Skill.h"
#include "Stat_Modifier.h"
#include "Ascii_Art_Manager.h"

#include "Level_Up.h"
#include "Item.h"
#include "Inventory.h"

#include "Monster.h"
#include "Player.h"

#include <iostream>
#include <string>
#include <iomanip>

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
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                   전 투 시 작                      ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "  PLAYER : " << player->Get_Name() << "\n";
    cout << "║                                                    ║\n";
    cout << "║                      V S                           ║\n";
    cout << "║                                                    ║\n";
    cout << "  ENEMY  : " << monster.getName() << "\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
}

void Show_Battle_Status(Player* player, Monster& monster, int turnCount)
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "                     TURN " << turnCount << " \n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "  PLAYER : " << player->Get_Name() << " \n";
    cout << "║ HP     : " << player->Get_Hp() << "\n";
    cout << "║                                                    ║\n";
    cout << "  ENEMY  : " << monster.getName() << " \n";
    cout << "  HP     : " << monster.getHP() << "\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
}

void Show_Battle_Menu()
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                  플레이어 턴                       ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << "║   [1] 공격                                         ║\n";
    cout << "║   [2] 스킬                                         ║\n";
    cout << "║   [3] 아이템                                       ║\n";
    cout << "║                                                    ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║ 행동을 선택하세요.                                 ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";
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
    if (player == nullptr)
    {
        return;
    }

    inventory.Use_Item(*player);
}

void Attack(Player* player, Monster& monster)
{
    if (player == nullptr) return;
    player->Attack(&monster);
}

bool Skill_Menu_Process(Player* player, Monster& monster)
{
    if (player == nullptr) return false;

    int menu;
    cout << endl;
    cout << "------ 스킬 ------" << endl;
    cout << "1. " << player->Get_Skill1_Name() << endl;
    cout << "2. " << player->Get_Skill2_Name() << endl;
    cout << "3. " << player->Get_Skill3_Name() << endl;
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
        return false;
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

    if (Is_Tutor(monster))
    {
        Execute_Elite_Skill(player, monster);
        return;
    }

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

    player->Set_Hp(After_HP);

    cout << endl;
    cout << "[전투 로그]" << endl;
    monster.Print_Attack_Message();
    cout << "HP : " << Before_Player_HP << " → " << player->Get_Hp() << endl;
}

//======================================================
// 전투 종료 및 승리 보상 처리
//======================================================
bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (monster.getHP() <= 0)
    {
        if (Is_Tutor(monster))
        {
            cout << "\n";
            cout << "╔════════════════════════════════════════════════════╗\n";
            cout << "║                 튜터 시험 통과!                    ║\n";
            cout << "╠════════════════════════════════════════════════════╣\n";
            cout << "║                                                    ║\n";
            cout << "║   축하합니다!                                      ║\n";
            cout << "║   다음 챕터가 해금되었습니다.                      ║\n";
            cout << "║                                                    ║\n";
            cout << "╚════════════════════════════════════════════════════╝\n";

            player->Remove_Temporary_Modifiers();
            return true;
        }

        cout << "\n";
        cout << "╔════════════════════════════════════════════════════╗\n";
        cout << "║                    전 투 승 리                     ║\n";
        cout << "╠════════════════════════════════════════════════════╣\n";
        cout << "║                                                    ║\n";
        cout << "    " << monster.getName() << " 처치 완료!\n";
        cout << "║                                                    ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n";

        player->Remove_Temporary_Modifiers();

        int exp = monster.getExpReward();
        player->Gain_Exp(exp);

        Give_Battle_Item_Reward(player, monster, inventory);

        return true;
    }

    if (player->Get_Hp() <= 0)
    {
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

//======================================================
// 최종 보스전 전용 퀴즈 시스템
//======================================================
bool Ask_Single_Quiz(const Quiz& quiz)
{
    cout << "\n[Q] " << quiz.question << "\n";
    for (size_t j = 0; j < quiz.choices.size(); ++j)
    {
        cout << (j + 1) << ") " << quiz.choices[j] << "  ";
    }
    cout << "\n답을 입력하세요 (1~4): ";

    int inputAnswer = 0;
    cin >> inputAnswer;

    if (inputAnswer == quiz.answer)
    {
        cout << ">> 정답입니다!\n";
        return true;
    }
    else
    {
        cout << ">> 오답입니다! (정답: " << quiz.answer << "번)\n";
        return false;
    }
}

void First_Impression_Quiz_Phase(Player* player, Monster& monster, vector<Quiz>& quizPool)
{
    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                  기 선 제 압                       ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << " " << monster.getName() << "의 기습 심사가 시작됩니다!\n";
    cout << "║                                                    ║\n";
    cout << "║ 전투 시작 전 2개의 질문이 출제됩니다.              ║\n";
    cout << "║ 정답을 맞히면 선제공격!                            ║\n";
    cout << "║ 틀리면 기습 공격을 받습니다!                       ║\n";
    cout << "║                                                    ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    for (int i = 0; i < 2 && !quizPool.empty(); ++i)
    {
        cout << "\n";
        cout << "══════════════════════════════════════════════════════\n";
        cout << "                [ 기습 문제 " << i + 1 << " / 2 ]\n";
        cout << "══════════════════════════════════════════════════════\n";

        Quiz q = quizPool.back();
        quizPool.pop_back();

        bool isCorrect = Ask_Single_Quiz(q);

        cout << "\n";

        if (isCorrect)
        {
            int counterDamage = player->Get_ATK();
            monster.setHP(monster.getHP() - counterDamage);

            cout << "╔════════════════════════════════════════════════════╗\n";
            cout << "║               기 선 제 압 성 공!                   ║\n";
            cout << "╠════════════════════════════════════════════════════╣\n";
            cout << "║ 선제공격 성공!                                     ║\n";
            cout << "  데미지 : " << counterDamage << "\n";
            cout << "╚════════════════════════════════════════════════════╝\n";
        }
        else
        {
            int bossDamage = static_cast<int>(monster.getPower() * 0.8);
            player->Set_Hp(player->Get_Hp() - bossDamage);

            cout << "╔════════════════════════════════════════════════════╗\n";
            cout << "║               기 선 제 압 실 패                    ║\n";
            cout << "╠════════════════════════════════════════════════════╣\n";
            cout << "║ 기습 공격을 허용했습니다!                          ║\n";
            cout << "  받은 피해 : " << bossDamage <<"\n";
            cout << "╚════════════════════════════════════════════════════╝\n";
        }

        if (player->Get_Hp() <= 0 || monster.getHP() <= 0)
            break;
    }
}

void Final_Boss_Monster_Turn(Player* player, Monster& monster, int turnCount, vector<Quiz>& quizPool)
{
    // 매 보스 턴마다 퀴즈 문제 출제
    if (!quizPool.empty())
    {
        cout << "\n";
        cout << "╔════════════════════════════════════════════════════╗\n";
        cout << "║               실 무 심 사 패 턴                    ║\n";
        cout << "╠════════════════════════════════════════════════════╣\n";
        cout << "║                                                    ║\n";
        cout << " " << monster.getName() << "의 특수 패턴이 발동!\n";
        cout << "║                                                    ║\n";
        cout << "║ 질문에 정답하면 카운터 공격!                       ║\n";
        cout << "║ 틀리면 강력한 특수 공격을 받습니다!                ║\n";
        cout << "║                                                    ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n";

        Quiz q = quizPool.back();
        quizPool.pop_back();

        cout << "\n";
        cout << "══════════════════════════════════════════════════════\n";
        cout << "                 [ 실무 심사 문제 ]\n";
        cout << "══════════════════════════════════════════════════════\n";

        monster.Print_Attack_Message();

        bool isCorrect = Ask_Single_Quiz(q);

        cout << "\n";

        if (isCorrect)
        {
            int counterDamage = player->Get_ATK() * 2;
            monster.setHP(monster.getHP() - counterDamage);

            cout << "╔════════════════════════════════════════════════════╗\n";
            cout << "║                 패 턴 파 훼 !                      ║\n";
            cout << "╠════════════════════════════════════════════════════╣\n";
            cout << "║                                                    ║\n";
            cout << "║ 카운터 공격 성공!                                  ║\n";
            cout << "  입힌 피해 : " << counterDamage << "\n";
            cout << "║                                                    ║\n";
            cout << "╚════════════════════════════════════════════════════╝\n";
        }
        else
        {
            int bossDamage = static_cast<int>(monster.getPower() * 1.5);
            player->Set_Hp(player->Get_Hp() - bossDamage);

            cout << "╔════════════════════════════════════════════════════╗\n";
            cout << "║                패 턴 실 패...                      ║\n";
            cout << "╠════════════════════════════════════════════════════╣\n";
            cout << "║                                                    ║\n";
            cout << "║ 특수 공격을 허용했습니다!                          ║\n";
            cout << "  받은 피해 : " << bossDamage << "\n";
            cout << "║                                                    ║\n";
            cout << "╚════════════════════════════════════════════════════╝\n";
        }
    }
    else
    {
        Monster_Attack(player, monster);
    }
}

void Boss_Battle(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    Show_Battle_Start(player, monster);

    vector<Quiz> quizPool;
    if (monster.getMonsterType() == Monster_Type::KIM_DONG_HYUN_MANAGER)
    {
        quizPool = KimDongHyunManagerQuiz;
    }
    else if (monster.getMonsterType() == Monster_Type::MOON_SEUNG_HO_MANAGER)
    {
        quizPool = MoonSeungHoManagerQuiz;
    }

    for (size_t i = 0; i < quizPool.size(); ++i)
    {
        int randIdx = rand() % quizPool.size();
        swap(quizPool[i], quizPool[randIdx]);
    }

    // 전투 시작 직후 기선제압 2문제 실행
    if (monster.getMonsterGrade() == Monster_Grade::FINAL_BOSS)
    {
        First_Impression_Quiz_Phase(player, monster, quizPool);
        if (Check_Battle_End(player, monster, inventory)) return;
    }

    int turnCount = 1;

    while (player->Get_Hp() > 0 && monster.getHP() > 0)
    {
        Show_Battle_Status(player, monster, turnCount);

        // 1. 플레이어 턴
        Player_Turn(player, monster, inventory);
        if (Check_Battle_End(player, monster, inventory)) break;

        // 2. 보스 턴 (매 보스 턴마다 퀴즈 패턴 적용)
        if (monster.getMonsterGrade() == Monster_Grade::FINAL_BOSS)
        {
            Final_Boss_Monster_Turn(player, monster, turnCount, quizPool);
        }
        else
        {
            Monster_Turn(player, monster, turnCount);
        }

        if (Check_Battle_End(player, monster, inventory)) break;

        turnCount++;
    }

    Show_Battle_End(player, monster);
}