#include "Battle_System.h"
#include "Battle_Elite_Skill.h"
#include "Quiz_Bank.h"
#include "Stat_Modifier.h"
#include "Ascii_Art_Manager.h"

#include "Level_Up.h"
#include "Item.h"
#include "Inventory.h"

#include "Monster.h"
#include "Player.h"

#include "Sound_Manager.h"

#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <random>
#include <vector>

using namespace std;

namespace
{
    std::string Pad_Right(const std::string& text, size_t width)
    {
        if (text.size() >= width)
        {
            return text;
        }

        return text + std::string(width - text.size(), ' ');
    }

    std::vector<std::string> Make_Final_Boss_Status_Block(const Monster& boss,const std::string& manager_Code)
    {
        const size_t box_Width = 42;

        std::string hp_Line =
            std::string("HP : ") +
            std::to_string(
                boss.getHP()
            );

        std::string name_Line =
            std::string("NAME : ") +
            boss.getName();

        std::vector<std::string> block;

        block.push_back(".--------------------------------------------.");
        block.push_back(std::string("| ") +Pad_Right(manager_Code,box_Width) +std::string(" |"));
        block.push_back(std::string("| ") +Pad_Right(name_Line,box_Width) +std::string(" |"));
        block.push_back(std::string("| ") +Pad_Right(hp_Line,box_Width) +std::string(" |"));
        block.push_back(std::string("| ") +Pad_Right("STATUS : ONLINE", box_Width) +std::string(" |"));
        block.push_back("'--------------------------------------------'");

        return block;
    }

    void Print_Side_By_Side_Battle_Blocks(const std::vector<std::string>& left_Block, const std::vector<std::string>& right_Block, int gap = 8)
    {
        size_t left_Width = 0;

        for (const std::string& line : left_Block)
        {
            if (line.size() > left_Width)
            {
                left_Width = line.size();
            }
        }

        size_t max_Lines = std::max(left_Block.size(), right_Block.size());

        for (size_t index = 0;
            index < max_Lines;
            index++)
        {
            std::string left_Line = index < left_Block.size() ? left_Block[index] : "";
            std::string right_Line = index < right_Block.size() ? right_Block[index] : "";

            cout << left_Line;

            size_t padding = left_Width - left_Line.size();

            for (size_t i = 0;
                i < padding + gap;
                i++)
            {
                cout << ' ';
            }

            cout << right_Line << "\n";
        }
    }

    void Print_Final_Boss_Duo_Status(Player* player, Monster& first_Boss, Monster& second_Boss, int turnCount)
    {
        cout << "\n";
        cout << "==================================================" << "\n";
        cout << "[ FINAL TURN " << turnCount << " ]" << "\n";
        cout << "==================================================" << "\n";

        if (player != nullptr)
        {
            cout << "PLAYER : " << player->Get_Name() << " / HP : " << player->Get_Hp() << "\n";
        }

        cout << "--------------------------------------------------" << "\n";

        Print_Side_By_Side_Battle_Blocks(Make_Final_Boss_Status_Block(first_Boss, "FINAL_MANAGER_01 :: CODE REVIEW"), Make_Final_Boss_Status_Block(second_Boss, "FINAL_MANAGER_02 :: VALIDATION"), 8);

        cout << "==================================================" << "\n";
    }

    void Print_Final_Boss_Duo_Status_For_Question(Player* player, Monster& first_Boss, Monster& second_Boss)
    {
        cout << "\n";
        cout << "==================================================" << "\n";
        cout << "[ BOSS STATUS - CODE VALIDATION ACTIVE ]" << "\n";
        cout << "==================================================" << "\n";

        if (player != nullptr)
        {
            cout << "PLAYER : " << player->Get_Name() << " / HP : " << player->Get_Hp() << "\n";
        }

        cout << "--------------------------------------------------" << "\n";

        Print_Side_By_Side_Battle_Blocks(Make_Final_Boss_Status_Block(first_Boss, "FINAL_MANAGER_01 :: CODE REVIEW"), Make_Final_Boss_Status_Block(second_Boss, "FINAL_MANAGER_02 :: VALIDATION"), 8);

        cout << "==================================================" << "\n";
    }
}

//======================================================
// 전투 시작 Main Loop
//======================================================
void Battle(Player* player, Monster& monster, Inventory<Item>& inventory, Console_Manager& console)
{
    if (player == nullptr) return;

	Sound_Manager::Get_Instance().Play_BGM(BGM_Type::Battle);

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

    Show_Battle_End(player, monster, console);   // console 전달
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

void Show_Battle_End(Player* player, Monster& monster, Console_Manager& console)
{
    console.Wait_For_Key("계속하려면 아무 키나 누르세요...");
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
            actionCompleted = Use_Item(player, monster, inventory);
            break;

        default:
            cout << "잘못된 입력입니다. 다시 선택해주세요." << endl;
            break;
        }
    }
}

bool Use_Item(Player* player, Monster& monster, Inventory<Item>& inventory)
{
    if (player == nullptr)
    {
        return false;
    }

   return inventory.Use_Item(*player);
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
            cout << "║   축하합니다.                                      ║\n";
            cout << "║   다음 챕터로 이동해주세요.                        ║\n";
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
        cout << "    " << monster.getName() << " 오류 해결!!\n";
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
        cout << endl << "[보상 획득]" << endl;
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
    cout << "\n답을 입력하라. (1~4): ";

    int inputAnswer = 0;
    cin >> inputAnswer;

    if (inputAnswer == quiz.answer)
    {
        cout << ">> 정답!\n";
        return true;
    }
    else
    {
        cout << ">> 오답! (정답: " << quiz.answer << "번)\n";
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
            cout << "║ 기습 공격을 허용!                                  ║\n";
            cout << "║ 받은 피해 : " << bossDamage << "\n";
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
        cout << "║ 질문에 알맞게 대답하면 카운터 공격!                ║\n";
        cout << "║ 틀리면 강력한 특수 공격을 받는다!                  ║\n";
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
            cout << "║ 특수 공격을 허용!                                  ║\n";
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

void Boss_Battle(Player* player, Monster& monster, Inventory<Item>& inventory, Console_Manager& console)
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

    Show_Battle_End(player, monster, console);   // console 전달
}

namespace
{
    string Normalize_Final_Boss_Answer(string answer)
    {
        string normalized;

        for (char character : answer)
        {
            unsigned char converted = static_cast<unsigned char>(character);

            if (isspace(converted))
            {
                continue;
            }

            normalized += static_cast<char>(tolower(converted));
        }

        return normalized;
    }

    bool Ask_Final_Boss_Question(Player* player, Monster& first_Boss,  Monster& second_Boss, const Final_Boss_Question& question)
    {
        Print_Final_Boss_Duo_Status_For_Question(player, first_Boss, second_Boss);

        cout << "\n";
        cout << "==================================================" << "\n";
        cout << "[ 최종 코드 검증 문제 ]" << "\n";
        cout << "==================================================" << "\n";
        cout << question.description << "\n";

        if (!question.code.empty())
        {
            cout << "--------------------------------------------------" << "\n";
            cout << question.code << "\n";
        }

        cout << "==================================================" << "\n";

        if (question.type == Final_Boss_Question_Type::MULTIPLE_CHOICE)
        {
            for (int index = 0;
                index < 4;
                index++)
            {
                cout << index + 1 << ". " << question.choices[index] << "\n";
            }

            int input_Choice = 0;

            cout << "선택 : ";
            cin >> input_Choice;

            if (input_Choice == question.correct_Choice)
            {
                cout << "정답입니다. 객관식 보상으로 광역 피해가 발생합니다." << "\n";
                return true;
            }

            cout << "오답입니다. 정답: "  << question.correct_Choice << "번" << "\n";

            return false;
        }

        string input_Answer;

        cout << "답 입력 : ";
        getline(cin >> ws, input_Answer);

        bool is_Correct =   Normalize_Final_Boss_Answer(input_Answer) == Normalize_Final_Boss_Answer(question.correct_Answer);

        if (is_Correct)
        {
            cout << "정답입니다. 주관식 보상으로 그로기 공격이 발동합니다." << "\n";
            return true;
        }

        cout << "오답입니다. 정답: " << question.correct_Answer << "\n";

        return false;
    }

    bool Check_Final_Boss_Gimmick_Trigger()
    {
        static random_device random_Device;
        static mt19937 random_Engine(random_Device());

        uniform_int_distribution<int> distribution(1, 100);

        int random_Value = distribution(random_Engine);
        const int GIMMICK_CHANCE = 35;

        return random_Value <= GIMMICK_CHANCE;
    }

    void Print_Final_Boss_Gimmick_Start_Message()
    {
        cout << "\n";
        cout << "==================================================\n";
        cout << "[ 매니저님들이 문제를 냈다. ]\n";
        cout << "==================================================\n";
        cout << "매니저님이 시험을 어렵게 낸다...\n";
        cout << "문제를 해결하면 매니저님들을 놀라게 할 수도?\n";
        cout << "==================================================\n";
    }


    Monster* Select_Final_Boss_Target(Monster& first_Boss, Monster& second_Boss)
    {
        if (first_Boss.getHP() <= 0)
        {
            return &second_Boss;
        }

        if (second_Boss.getHP() <= 0)
        {
            return &first_Boss;
        }

        while (true)
        {
            int target_Choice = 0;

            cout << "\n[ 공격 대상 선택 ]\n";
            cout << "1. " << first_Boss.getName() << " / HP: " << first_Boss.getHP() << "\n";
            cout << "2. " << second_Boss.getName() << " / HP: " << second_Boss.getHP() << "\n";
            cout << "선택 : ";

            cin >> target_Choice;

            if (target_Choice == 1)
            {
                return &first_Boss;
            }

            if (target_Choice == 2)
            {
                return &second_Boss;
            }

            cout << "1번 또는 2번을 입력하세요.\n";
        }
    }

    void Apply_Final_Boss_Objective_Area_Damage(Player* player, Monster& first_Boss, Monster& second_Boss
    )
    {
        if (player == nullptr)
        {
            return;
        }

        cout << "\n";
        cout << "==================================================\n";
        cout << "[ 매니저님들이 당황하셨다.]\n";
        cout << "==================================================\n";

        Monster* bosses[2] =
        {
            &first_Boss, &second_Boss
        };

        for (Monster* boss : bosses)
        {
            if (boss->getHP() <= 0)
            {
                continue;
            }

            int damage = player->Get_ATK() * 2 - boss->getDefence();

            if (damage < 1)
            {
                damage = 1;
            }

            int changed_HP =
                boss->getHP() - damage;

            if (changed_HP < 0)
            {
                changed_HP = 0;
            }

            boss->setHP(changed_HP);

            cout << boss->getName() << "에게 " << damage << " 광역 피해!\n";
        }
    }

    void Apply_Final_Boss_Subjective_Groggy_Attack(Player* player, Monster& first_Boss,Monster& second_Boss)
    {
        if (player == nullptr)
        {
            return;
        }

        cout << "\n";
        cout << "==================================================\n";
        cout << "[ 매니저님들이 놀라셨다. ]\n";
        cout << "사용 기술: " << player->Get_Groggy_Attack_Name() << "\n";
        cout << "매니저님 한분을 지목하세요.\n";
        cout << "==================================================\n";

        Monster* selected_Target = Select_Final_Boss_Target(first_Boss, second_Boss);

        player->Groggy_Attack(selected_Target);
    }

    void Apply_Final_Boss_Question_Reward(Player* player, Monster& first_Boss, Monster& second_Boss, const Final_Boss_Question& question)
    {
        if (question.type == Final_Boss_Question_Type::MULTIPLE_CHOICE)
        {
            Apply_Final_Boss_Objective_Area_Damage(player, first_Boss, second_Boss);

            return;
        }

        Apply_Final_Boss_Subjective_Groggy_Attack(player, first_Boss, second_Boss);
    }

    void Final_Boss_Duo_Attack(Player* player, Monster& first_Boss, Monster& second_Boss)
    {
        cout << "\n";
        cout << "==================================================\n";
        cout << "[ 매니저님들이 잔소리를 하였습니다 ]\n";
        cout << "==================================================\n";

        if (first_Boss.getHP() > 0)
        {
            Monster_Attack(player, first_Boss);
        }

        if (player->Get_Hp() > 0 &&
            second_Boss.getHP() > 0)
        {
            Monster_Attack(player, second_Boss);
        }
    }

    void Final_Boss_Duo_Double_Damage_Attack(Player* player, Monster& first_Boss, Monster& second_Boss)
    {
        if (player == nullptr)
        {
            return;
        }

        cout << "\n";
        cout << "==================================================\n";
        cout << "[ 매니저님에게 GPT 사용을 걸렸다. ]\n";
        cout << "==================================================\n";
        cout << "매니저님들이 실망했다.\n";
        cout << "매니저님들의 잔소리.\n";
        cout << "==================================================\n";

        if (first_Boss.getHP() > 0)
        {
            Monster_Attack(player, first_Boss);

            if (player->Get_Hp() > 0)
            {
                Monster_Attack(player, first_Boss);
            }
        }

        if (player->Get_Hp() > 0 &&
            second_Boss.getHP() > 0)
        {
            Monster_Attack(player,second_Boss);

            if (player->Get_Hp() > 0)
            {
                Monster_Attack(player, second_Boss);
            }
        }
    }
}

bool Final_Boss_Duo_Battle(Player* player, Monster& first_Boss, Monster& second_Boss, Inventory<Item>& inventory)
{
    if (player == nullptr)
    {
        return false;
    }

    vector<Final_Boss_Question> question_Pool = Create_Final_Boss_Question_Pool();

    if (question_Pool.empty())
    {
        cout << "문제가 다 떨어졌다.\n";
        return false;
    }

    static random_device random_Device;
    static mt19937 random_Engine(random_Device());

    shuffle(question_Pool.begin(), question_Pool.end(), random_Engine);

    size_t question_Index = 0;
    int turnCount = 1;

    cout << "\n";
    cout << "==================================================\n";
    cout << "[ 최종 보스 2인 동시 전투 ]\n";
    cout << "==================================================\n";
    cout << "최종보스 기본 패턴: 일반 공격!" << endl;
	cout << "랜덤 코드 검증 기믹 발동!" << endl;
	cout << "객관식 정답: 전체 광역 피해!" << endl;
	cout << "주관식 정답: 대상 선택 후 그로기 공격!" << endl;
	cout << "오답: 보스 공격 2배 강화!" << endl;
    cout << "==================================================\n";

    while (player->Get_Hp() > 0 && (first_Boss.getHP() > 0 || second_Boss.getHP() > 0))
    {
        Print_Final_Boss_Duo_Status(player, first_Boss, second_Boss, turnCount);

        Monster* selected_Target =Select_Final_Boss_Target(first_Boss,second_Boss);

        Player_Turn(player, *selected_Target, inventory);

        if (first_Boss.getHP() <= 0 && second_Boss.getHP() <= 0)
        {
            break;
        }

        bool is_Gimmick_Triggered = Check_Final_Boss_Gimmick_Trigger();

        if (!is_Gimmick_Triggered)
        {
            cout << "\n";
            cout << "==================================================\n";
            cout << "[ 매니저님의 기습 세션 ]\n";
            cout << "==================================================\n";

            Final_Boss_Duo_Attack(player, first_Boss, second_Boss);
        }
        else
        {
            Print_Final_Boss_Gimmick_Start_Message();

            if (question_Index >= question_Pool.size())
            {
                shuffle(question_Pool.begin(), question_Pool.end(), random_Engine);

                question_Index = 0;
            }

            const Final_Boss_Question& current_Question = question_Pool[question_Index];

            bool is_Correct = Ask_Final_Boss_Question(player, first_Boss, second_Boss, current_Question);

            question_Index++;

            if (is_Correct)
            {
                Apply_Final_Boss_Question_Reward(player, first_Boss, second_Boss, current_Question);
            }
            else
            {
                Final_Boss_Duo_Double_Damage_Attack(player, first_Boss, second_Boss);
            }
        }

        player->Process_Stat_Modifier_Turn();
        turnCount++;
        player->Process_Stat_Modifier_Turn();
        turnCount++;
    }

    player->Remove_Temporary_Modifiers();

    return player->Get_Hp() > 0 &&
        first_Boss.getHP() <= 0 &&
        second_Boss.getHP() <= 0;
}