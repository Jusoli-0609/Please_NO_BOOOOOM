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
#include <random>

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

    inventory.Use_Item(*player, monster);
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
    cout << endl;
    cout << "--------------------------------------------------" << endl;

    cout << quiz.question << endl;

    cout << "--------------------------------------------------" << endl;


    for (size_t i = 0; i < quiz.choices.size(); i++)
    {
        cout << i + 1
            << ". "
            << quiz.choices[i]
            << endl;
    }


    cout << endl;

    cout << "선택 : ";


    int answer;
    cin >> answer;



    if (answer == quiz.answer)
    {
        cout << endl;
        cout << "정답입니다." << endl;

        return true;
    }


    cout << endl;
    cout << "오답입니다." << endl;


    return false;
}

void First_Impression_Quiz_Phase(
    Player* player,
    Monster& monster,
    vector<Quiz>& quizPool
)
{
    if (player == nullptr)
    {
        return;
    }


    if (quizPool.empty())
    {
        return;
    }



    cout << endl;
    cout << "==================================================" << endl;
    cout << "[ 최종 검증 시작 전 테스트 ]" << endl;
    cout << "==================================================" << endl;

    cout << monster.getName()
        << " : "
        << endl;

    cout << "\"먼저 당신의 기본적인 코드 이해도를 확인하겠습니다.\""
        << endl;


    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(
        0,
        static_cast<int>(quizPool.size()) - 1
    );


    int index = dist(gen);



    bool isCorrect = Ask_Single_Quiz(
        quizPool[index]
    );


    cout << endl;


    if (isCorrect)
    {
        cout << "==================================================" << endl;
        cout << "검증 통과." << endl;
        cout << "==================================================" << endl;

        return;
    }



    cout << "==================================================" << endl;
    cout << "검증 실패." << endl;
    cout << "최종 시험의 난이도가 상승합니다." << endl;
    cout << "==================================================" << endl;


    int penaltyDamage = 20;


    player->Set_Hp(
        player->Get_Hp() - penaltyDamage
    );


    if (player->Get_Hp() < 0)
    {
        player->Set_Hp(0);
    }


    cout << "추가 피해 : "
        << penaltyDamage
        << endl;

    cout << "현재 HP : "
        << player->Get_Hp()
        << endl;
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

bool Final_Boss_Duo_Battle(
    Player* player,
    Monster& kim,
    Monster& moon,
    Inventory<Item>& inventory
)
{
    if (player == nullptr)
    {
        return false;
    }


    //==================================================
    // 최종보스 시작 전 기선제압 테스트
    //==================================================

    vector<Quiz> firstQuizPool;


    if (kim.getMonsterType() == Monster_Type::KIM_DONG_HYUN_MANAGER)
    {
        firstQuizPool = KimDongHyunManagerQuiz;
    }


    if (!firstQuizPool.empty())
    {
        First_Impression_Quiz_Phase(
            player,
            kim,
            firstQuizPool
        );
    }


    if (player->Get_Hp() <= 0)
    {
        return false;
    }



    int turnCount = 1;


    while (
        player->Get_Hp() > 0 &&
        (kim.getHP() > 0 || moon.getHP() > 0)
        )
    {
        cout << endl;
        cout << "==================================================" << endl;
        cout << "FINAL DUO TURN : "
            << turnCount
            << endl;
        cout << "==================================================" << endl;



        cout << endl;
        cout << kim.getName()
            << " HP : "
            << kim.getHP()
            << endl;


        cout << moon.getName()
            << " HP : "
            << moon.getHP()
            << endl;



        //==================================================
        // 플레이어 턴
        //==================================================

        Duo_Player_Turn(
            player,
            kim,
            moon,
            inventory
        );



        // 둘 다 쓰러졌는지 확인
        if (
            kim.getHP() <= 0 &&
            moon.getHP() <= 0
            )
        {
            break;
        }



        //==================================================
        // 김동현 매니저 턴
        //==================================================

        if (kim.getHP() > 0)
        {
            Duo_Monster_Turn(
                player,
                kim
            );
        }



        if (player->Get_Hp() <= 0)
        {
            break;
        }



        //==================================================
        // 문승호 매니저 턴
        //==================================================

        if (moon.getHP() > 0)
        {
            Duo_Monster_Turn(
                player,
                moon
            );
        }



        //==================================================
        // 버프/디버프 턴 감소
        //==================================================

        player->Process_Stat_Modifier_Turn();



        turnCount++;
    }



    //==================================================
    // 전투 종료 처리
    //==================================================

    if (player->Get_Hp() <= 0)
    {
        player->Remove_Temporary_Modifiers();
        return false;
    }


    player->Remove_Temporary_Modifiers();


    return true;
}

void Duo_Player_Turn(
    Player* player,
    Monster& kim,
    Monster& moon,
    Inventory<Item>& inventory
)
{
    bool actionCompleted = false;

    while (!actionCompleted)
    {
        cout << endl;
        cout << "==================================================" << endl;
        cout << "[ 플레이어 턴 ]" << endl;
        cout << "==================================================" << endl;

        cout << "1. 김동현 매니저 공격" << endl;
        cout << "2. 문승호 매니저 공격" << endl;
        cout << "3. 스킬 사용" << endl;
        cout << "4. 아이템 사용" << endl;
        cout << "선택 : ";

        int menu;
        cin >> menu;


        switch (menu)
        {
        case 1:
        {
            if (kim.getHP() <= 0)
            {
                cout << "이미 검증을 완료한 대상입니다." << endl;
                break;
            }

            Attack(player, kim);
            actionCompleted = true;

            break;
        }


        case 2:
        {
            if (moon.getHP() <= 0)
            {
                cout << "이미 검증을 완료한 대상입니다." << endl;
                break;
            }

            Attack(player, moon);
            actionCompleted = true;

            break;
        }


        case 3:
        {
            cout << endl;
            cout << "[ 스킬 사용 ]" << endl;

            bool usedSkill = false;


            // 기존 Skill은 Monster 1개 기준이라
            // 대상 선택 후 실행
            cout << "스킬 대상을 선택하세요." << endl;

            cout << "1. "
                << kim.getName()
                << endl;

            cout << "2. "
                << moon.getName()
                << endl;

            cout << "선택 : ";


            int target;
            cin >> target;


            if (target == 1)
            {
                usedSkill = Skill_Menu_Process(player, kim);
            }
            else if (target == 2)
            {
                usedSkill = Skill_Menu_Process(player, moon);
            }
            else
            {
                cout << "잘못된 선택입니다." << endl;
            }


            if (usedSkill)
            {
                actionCompleted = true;
            }

            break;
        }


        case 4:
        {
            Use_Item(player, kim, inventory);

            actionCompleted = true;

            break;
        }


        default:
        {
            cout << "잘못된 선택입니다." << endl;
            break;
        }
        }
    }
}

void Duo_Monster_Turn(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return;
    }

    if (monster.getHP() <= 0)
    {
        return;
    }


    cout << endl;
    cout << "==================================================" << endl;
    cout << "[ " << monster.getName() << "의 턴 ]" << endl;
    cout << "==================================================" << endl;



    //==================================================
    // 최종보스 전용 스킬
    //==================================================

    if (monster.getMonsterType() == Monster_Type::KIM_DONG_HYUN_MANAGER)
    {
        int chance = rand() % 100;

        if (chance < 30)
        {
            Kim_Dong_Hyun_Manager_Skill(player, monster);
            return;
        }
    }


    if (monster.getMonsterType() == Monster_Type::MOON_SEUNG_HO_MANAGER)
    {
        int chance = rand() % 100;

        if (chance < 30)
        {
            Moon_Seung_Ho_Manager_Skill(player, monster);
            return;
        }
    }



    //==================================================
    // 최종보스 전용 공격 대사 출력
    //==================================================

    monster.Print_Attack_Message();



    //==================================================
    // 기존 최종보스 기믹 스킬 체크
    //==================================================

    static int finalBossTurnCount = 1;


    if (Check_Elite_Skill(monster, finalBossTurnCount))
    {
        cout << endl;
        cout << "[ 최종 검증 패턴 발동 ]" << endl;


        Execute_Elite_Skill(player, monster);


        finalBossTurnCount++;


        return;
    }



    //==================================================
    // 기본 공격
    //==================================================

    int damage = monster.getPower() - player->Get_DEF();


    if (damage <= 0)
    {
        damage = 1;
    }


    cout << endl;
    cout << monster.getName()
        << "의 코드 검증 공격!"
        << endl;


    cout << "받은 피해 : "
        << damage
        << endl;



    int currentHP = player->Get_Hp();


    player->Set_Hp(currentHP - damage);



    if (player->Get_Hp() < 0)
    {
        player->Set_Hp(0);
    }



    cout << "현재 HP : "
        << player->Get_Hp()
        << endl;

    finalBossTurnCount++;
}

bool Duo_Skill_Process(
    Player* player,
    Monster& kim,
    Monster& moon
)
{
    int target;


    cout << endl;
    cout << "==================================================" << endl;
    cout << "스킬 대상 선택" << endl;
    cout << "==================================================" << endl;



    if (kim.getHP() > 0)
    {
        cout << "1. "
            << kim.getName()
            << " HP : "
            << kim.getHP()
            << endl;
    }


    if (moon.getHP() > 0)
    {
        cout << "2. "
            << moon.getName()
            << " HP : "
            << moon.getHP()
            << endl;
    }



    cout << "선택 : ";
    cin >> target;



    if (target == 1 &&
        kim.getHP() > 0)
    {
        Skill(
            player,
            kim
        );

        return true;
    }



    if (target == 2 &&
        moon.getHP() > 0)
    {
        Skill(
            player,
            moon
        );

        return true;
    }



    cout << "사용할 수 없는 대상입니다." << endl;

    return false;
}

void Kim_Dong_Hyun_Manager_Skill(
    Player* player,
    Monster& monster
)
{
    cout << endl;
    cout << "==================================================" << endl;
    cout << monster.getName()
        << " : 코드 검증을 시작합니다."
        << endl;
    cout << "==================================================" << endl;



    if (KimDongHyunManagerQuiz.empty())
    {
        Monster_Attack(player, monster);
        return;
    }



    int index = rand() % KimDongHyunManagerQuiz.size();


    bool correct =
        Ask_Single_Quiz(
            KimDongHyunManagerQuiz[index]
        );



    if (correct)
    {
        cout << endl;
        cout << "코드 검증 성공!" << endl;
        cout << "공격을 막아냈습니다." << endl;
    }
    else
    {
        cout << endl;
        cout << "검증 실패!" << endl;
        cout << "추가 피해 발생!" << endl;


        int damage = 20;

        int currentHP = player->Get_Hp();

        int afterHP = currentHP - damage;


        if (afterHP < 0)
        {
            afterHP = 0;
        }


        player->Set_Hp(afterHP);


        cout << "받은 피해 : "
            << damage
            << endl;

        cout << "현재 HP : "
            << player->Get_Hp()
            << endl;
    }
}

void Moon_Seung_Ho_Manager_Skill(
    Player* player,
    Monster& monster
)
{
    cout << endl;
    cout << "==================================================" << endl;
    cout << monster.getName()
        << " : 메모리 구조 검증을 시작합니다."
        << endl;
    cout << "==================================================" << endl;



    if (MoonSeungHoManagerQuiz.empty())
    {
        Monster_Attack(player, monster);
        return;
    }



    int index =
        rand() % MoonSeungHoManagerQuiz.size();



    bool correct =
        Ask_Single_Quiz(
            MoonSeungHoManagerQuiz[index]
        );



    if (correct)
    {
        cout << "검증 성공!" << endl;
        cout << "피해를 회피했습니다." << endl;
    }
    else
    {
        cout << "검증 실패!" << endl;
        cout << "포인터 오류 공격!" << endl;


        int damage = 30;

        int currentHP = player->Get_Hp();

        int afterHP = currentHP - damage;


        if (afterHP < 0)
        {
            afterHP = 0;
        }


        player->Set_Hp(afterHP);


        cout << "받은 피해 : "
            << damage
            << endl;

        cout << "현재 HP : "
            << player->Get_Hp()
            << endl;
    }
}

void Print_Final_Boss_Duo_Introduction(Monster& kim, Monster& moon)
{
    cout << endl;
    cout << "==================================================" << endl;
    cout << "              FINAL CODE VERIFICATION              " << endl;
    cout << "==================================================" << endl;

    cout << endl;

    cout << kim.getName()
        << " : \"여기까지 온 것을 인정하지.\""
        << endl;

    cout << moon.getName()
        << " : \"하지만 마지막 검증은 쉽지 않을 것이다.\""
        << endl;

    cout << endl;

    cout << "두 명의 매니저가 동시에 코드를 분석하기 시작했다." << endl;
    cout << "플레이어는 두 명의 보스를 상대해야 한다." << endl;

    cout << "==================================================" << endl;
}