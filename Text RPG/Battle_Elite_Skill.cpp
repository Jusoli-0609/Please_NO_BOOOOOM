#include "Battle_Elite_Skill.h"

#include "Console_Manager.h"
#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <string>

using namespace std;

namespace
{
    string Normalize_Answer(string answer)
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

    void Draw_Elite_Fixed_Frame(Player* player, Monster& monster, const std::string& title)
    {
        Console_Manager console;

        console.Clear();

        monster.Print_Ascii_Art();

        cout << "\n";
        cout << "╔════════════════════════════════════════════════════╗\n";
        cout << "  " << title << "\n";
        cout << "╠════════════════════════════════════════════════════╣\n";

        if (player != nullptr)
        {
            cout << "  PLAYER : " << player->Get_Name() << " / HP : " << player->Get_Hp() << "\n";
        }

        cout << "  ENEMY  : " << monster.getName() << " / HP : " << monster.getHP() << "\n";
        cout << "╚════════════════════════════════════════════════════╝\n";
        cout << "\n";
    }

    void Wait_Elite_Fixed_Screen()
    {
        Console_Manager console;

        console.Wait_For_Key("확인 완료. 아무 키나 누르세요...");
    }

    void Draw_Elite_Question_Frame(Player* player, Monster& monster, const std::string& title)
    {
        Console_Manager console;

        console.Clear();

        monster.Print_Ascii_Art();

        cout << "\n";
        cout << "╔════════════════════════════════════════════════════╗\n";
        cout << "  " << title << "\n";
        cout << "╠════════════════════════════════════════════════════╣\n";

        if (player != nullptr)
        {
            cout << "  PLAYER : " << player->Get_Name() << " / HP : " << player->Get_Hp() << "\n";
        }

        cout << "  ENEMY  : " << monster.getName() << " / HP : " << monster.getHP() << "\n";
        cout << "╚════════════════════════════════════════════════════╝\n";
        cout << "\n";
    }

    void Wait_Elite_Screen()
    {
        Console_Manager console;

        console.Wait_For_Key("확인 완료. 아무 키나 누르세요...");
    }
}
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
    Draw_Elite_Question_Frame(player, monster, "정예 몬스터 코드 스니펫 문제");

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
        cout << "║ 문제를 맞혔다!!!                                   ║\n";
        cout << "╚════════════════════════════════════════════════════╝\n";

        Wait_Elite_Screen();

        return true;
    }

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                     오 답 !                        ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "║ 공부 하세요!!!                                     ║\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    Wait_Elite_Screen();

    return false;
}

//======================================================
// 엘리트 몬스터용 랜덤 1문제 출제
//======================================================
bool Ask_Random_Elite_Question(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return false;
    }

    const vector<Quiz>* question_Bank = Get_Elite_Question_Bank(monster.getChapterType());

    if (question_Bank == nullptr ||
        question_Bank->empty())
    {
        cout << "문제가 다 떨어졌다.\n";
        return false;
    }

    static random_device random_Device;
    static mt19937 random_Engine(random_Device());

    uniform_int_distribution<size_t> distribution(0,question_Bank->size() - 1);
    size_t random_Index = distribution(random_Engine);

    return Ask_Quiz(player, monster,(*question_Bank)[random_Index]);
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
// 튜터 문제 출제
bool Ask_Tutor_Question(const Tutor_Question& question)
{
    cout << "\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << question.description << "\n";
    cout << "──────────────────────────────────────────────────────\n";
    cout << question.code << "\n";
    cout << "──────────────────────────────────────────────────────\n";

    string input_Answer;

    cout << "답 입력 : ";
    getline(cin >> ws, input_Answer);

    bool is_Correct = Normalize_Answer(input_Answer) == Normalize_Answer(question.correct_Answer);

    if (is_Correct)
    {
        cout << "정답.\n";
        return true;
    }

    cout << "오답. 정답: " << question.correct_Answer << "\n";

    return false;
}

//======================================================
// 튜터 보스용 시험 시스템 (3문제 중 2문제 이상 통과)
//======================================================
bool Tutor_Test(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return false;
    }

    const vector<Tutor_Question>* question_Bank = Get_Tutor_Question_Bank(monster.getChapterType());

    if (question_Bank == nullptr ||
        question_Bank->empty())
    {
        cout << "문제가 다 떨어졌다.\n";
        return false;
    }

    Console_Manager console;

    int question_Count = min(3, static_cast<int>(question_Bank->size()));

    int correct_Count = 0;

    Draw_Elite_Question_Frame(player, monster, "튜터님 코드 리뷰 시험");

    cout << "총 3문제 중 2문제 이상 정답 시 합격!\n";

    console.Wait_For_Key("시험을 시작하려면 아무 키나 누르세요...");

    for (int index = 0; index < question_Count; index++)
    {
        Draw_Elite_Question_Frame(player, monster,"튜터님 코드 리뷰 시험");

        cout << "\n";
        cout << "══════════════════════════════════════════════════════\n";
        cout << "[ 문제 " << index + 1 << " / " << question_Count << " ]\n";
        cout << "══════════════════════════════════════════════════════\n";

        if (Ask_Tutor_Question((*question_Bank)[index]))
        {
            correct_Count++;
        }

        console.Wait_For_Key("다음 문제로 넘어가려면 아무 키나 누르세요...");
    }

    Draw_Elite_Question_Frame(player, monster, "튜터님 코드 리뷰 시험 결과");

    cout << "\n";
    cout << "╔════════════════════════════════════════════════════╗\n";
    cout << "║                  시 험 결 과                       ║\n";
    cout << "╠════════════════════════════════════════════════════╣\n";
    cout << "  정답 : "  << correct_Count  << " / " << question_Count << "\n";

    if (correct_Count >= 2)
    {
        cout << "                ★ 시험 통과! ★\n";
        cout << "╚════════════════════════════════════════════════════╝\n";

        console.Wait_For_Key("시험 결과 확인 완료. 아무 키나 누르세요...");

        return true;
    }

    cout << "                시험 실패...\n";
    cout << "╚════════════════════════════════════════════════════╝\n";

    console.Wait_For_Key("시험 결과 확인 완료. 아무 키나 누르세요...");

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
            cout << endl << "튜터님에게 인정 받았다!!" << endl;
            monster.setHP(0);
        }
        else
        {
            cout << endl << "튜터이 잔소리를 하셨다..." << endl;
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