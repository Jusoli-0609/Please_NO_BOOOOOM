#include "Battle_Elite_Skill.h"

#include <iostream>
#include <algorithm>
#include <random>
#include <ctime>

using namespace std;

//======================================================
// 엘리트 / 튜터 스킬 발동 조건 체크
//======================================================
bool Check_Elite_Skill(Monster& monster, int turnCount)
{
    if (monster.getMonsterGrade() != Monster_Grade::ELITE &&
        monster.getMonsterGrade() != Monster_Grade::TUTOR &&
        monster.getMonsterGrade() != Monster_Grade::FINAL_BOSS)
    {
        return false;
    }

    switch (monster.getMonsterType())
    {
    case Monster_Type::CODE_SNIPPET_WRAITH:
    case Monster_Type::VARIABLE_CONDITION_TUTOR:
    {
        if (turnCount % 3 == 0) return true;
        break;
    }

    case Monster_Type::ARRAY_LOOP_TUTOR:
    case Monster_Type::FUNCTION_TUTOR:
    case Monster_Type::POINTER_MEMORY_TUTOR:
    case Monster_Type::OBJECT_STL_TUTOR:
    {
        if (monster.getHP() <= 50) return true;
        break;
    }

    default:
        break;
    }
    return false;
}

//======================================================
// 단일 퀴즈 출제 함수 (4지선다)
//======================================================
// Battle_Elite_Skill.cpp

bool Ask_Quiz(Player* player, Monster& monster, const Quiz& quiz)
{
    cout << "\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << quiz.question << "\n";
    cout << "──────────────────────────────────────────────────────\n\n";

    for (size_t i = 0; i < quiz.choices.size(); i++)
    {
        cout << " [" << i + 1 << "] " << quiz.choices[i] << '\n';
    }

    cout << "\n";
    cout << "══════════════════════════════════════════════════════\n";

    int answer;
    cout << "선택 : ";
    cin >> answer;

    if (answer == quiz.answer)
    {
        cout << "\n";
        cout << "╔════════════════════════════════════════════════════╗\n";
        cout << "║                     정 답 !                        ║\n";
        cout << "╠════════════════════════════════════════════════════╣\n";
        cout << "║ 문제를 정확히 맞혔습니다!                          ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n";

        return true;
    }

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                     오 답 !                        ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║ 아쉽습니다. 다음 기회에 다시 도전하세요.           ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    return false;
}

//======================================================
// 엘리트 몬스터용 랜덤 1문제 출제
//======================================================
bool Ask_Random_Elite_Question(Player* player, Monster& monster)
{
    if (EliteQuiz.empty()) return false;

    srand((unsigned int)time(nullptr));
    int index = rand() % EliteQuiz.size();

    return Ask_Quiz(player, monster, EliteQuiz[index]);
}

//======================================================
// 튜터 타입별 문제 은행 포인터 반환
//======================================================
vector<Quiz>* Get_Tutor_Quiz(Monster_Type type)
{
    switch (type)
    {
    case Monster_Type::VARIABLE_CONDITION_TUTOR: return &VariableTutorQuiz;
    case Monster_Type::ARRAY_LOOP_TUTOR:         return &ArrayTutorQuiz;
    case Monster_Type::FUNCTION_TUTOR:           return &FunctionTutorQuiz;
    case Monster_Type::POINTER_MEMORY_TUTOR:     return &PointerTutorQuiz;
    case Monster_Type::OBJECT_STL_TUTOR:         return &ObjectTutorQuiz;
    default:                                     return nullptr;
    }
}

//======================================================
// 튜터 보스용 시험 시스템 (3문제 중 2문제 이상 통과)
//======================================================
bool Tutor_Test(Player* player, Monster& monster)
{
    vector<Quiz>* quizList = Get_Tutor_Quiz(monster.getMonsterType());
    if (quizList == nullptr || quizList->empty())
        return false;

    vector<int> order;
    for (size_t i = 0; i < quizList->size(); i++)
    {
        order.push_back((int)i);
    }

    random_device rd;
    mt19937 g(rd());
    shuffle(order.begin(), order.end(), g);

    int score = 0;

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                  튜 터 시 험                       ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << "  시험관 : " << monster.getName() << "\n";
    cout << "║                                                    ║\n";
    cout << "║ 총 3문제 중 2문제 이상 정답 시 합격!               ║\n";
    cout << "║                                                    ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    int questionCount = min(3, (int)quizList->size());

    for (int i = 0; i < questionCount; i++)
    {
        cout << "\n";
        cout << "══════════════════════════════════════════════════════\n";
        cout << "                 [ 문제 " << i + 1 << " / " << questionCount << " ]\n";
        cout << "══════════════════════════════════════════════════════\n";

        if (Ask_Quiz(player, monster, (*quizList)[order[i]]))
        {
            score++;
        }
    }

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                  시 험 결 과                       ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║                                                    ║\n";
    cout << "  정답 : " << score << " / " << questionCount << "\n";
    cout << "║                                                    ║\n";

    if (score >= 2)
    {
        cout << "                ★ 시험 통과! ★\n";
        cout << "║                                                    ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n";
        return true;
    }

    cout << "                시험 실패...\n";
    cout << "║                                                    ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    return false;
}
//======================================================
// 스킬 실행 분기
//======================================================
void Execute_Elite_Skill(Player* player, Monster& monster)
{
    if (player == nullptr) return;

    switch (monster.getMonsterType())
    {
    case Monster_Type::CODE_SNIPPET_WRAITH:
    {
        Ask_Random_Elite_Question(player, monster);
        break;
    }

    case Monster_Type::VARIABLE_CONDITION_TUTOR:
    case Monster_Type::ARRAY_LOOP_TUTOR:
    case Monster_Type::FUNCTION_TUTOR:
    case Monster_Type::POINTER_MEMORY_TUTOR:
    case Monster_Type::OBJECT_STL_TUTOR:
    {
        if (Tutor_Test(player, monster))
        {
            cout << endl << "튜터 시험을 통과했습니다!" << endl;
            monster.setHP(0);
        }
        else
        {
            cout << endl << "튜터 시험에 실패했습니다..." << endl;
            player->Set_Hp(0);
        }
        break;
    }

    default:
        break;
    }
}

//======================================================
// 레거시 래퍼 함수들
//======================================================
void Code_Snippet_Question(Player* player, Monster& monster) { Ask_Random_Elite_Question(player, monster); }
void Variable_Condition_Question(Player* player, Monster& monster) { Tutor_Test(player, monster); }
void Array_Loop_Question(Player* player, Monster& monster) { Tutor_Test(player, monster); }
void Function_Question(Player* player, Monster& monster) { Tutor_Test(player, monster); }
void Pointer_Memory_Question(Player* player, Monster& monster) { Tutor_Test(player, monster); }
void Object_Stl_Question(Player* player, Monster& monster) { Tutor_Test(player, monster); }

//======================================================
// 튜터 판별 함수
//======================================================
bool Is_Tutor(Monster& monster)
{
    switch (monster.getMonsterType())
    {
    case Monster_Type::VARIABLE_CONDITION_TUTOR:
    case Monster_Type::ARRAY_LOOP_TUTOR:
    case Monster_Type::FUNCTION_TUTOR:
    case Monster_Type::POINTER_MEMORY_TUTOR:
    case Monster_Type::OBJECT_STL_TUTOR:
        return true;

    default:
        return false;
    }
}