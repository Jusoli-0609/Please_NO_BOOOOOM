#include "Battle_Elite_Skill.h"
#include <iostream>

using namespace std;

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

    case Monster_Type::CODE_SNIPPET_WRAITH: //코드스니펫의 망령
    {
        if (turnCount % 3 == 0)
        {
            return true;
        }

        break;
    }

    case Monster_Type::VARIABLE_CONDITION_TUTOR: //손승현 튜터님
    {
        if (turnCount % 3 == 0)
        {
            return true;
        }
        break;
    }

    case Monster_Type::ARRAY_LOOP_TUTOR: //박은일 튜터님
    {
        if (monster.getHP() <= 50)
        {
            return true;
        }
        break;
    }

    case Monster_Type::FUNCTION_TUTOR: //강신호 튜터님
    {
        if (monster.getHP() <= 50)
        {
            return true;
        }
        break;
    }

    case Monster_Type::POINTER_MEMORY_TUTOR: //문승현 튜터님
    {
        if (monster.getHP() <= 50)
        {
            return true;
        }
        break;
    }

    case Monster_Type::OBJECT_STL_TUTOR: //김하늘 튜터님
    {
        if (monster.getHP() <= 50)
        {
            return true;
        }
        break;
    }

    default:
        break;
    }
	return false;
}

void Execute_Elite_Skill(Player* player, Monster& monster)
{
    if (player == nullptr)
    {
        return;
    }

    switch (monster.getMonsterType())
    {
    case Monster_Type::CODE_SNIPPET_WRAITH:
    {
        Code_Snippet_Question(player, monster);
        break;
    }

    case Monster_Type::VARIABLE_CONDITION_TUTOR:
    {
        Variable_Condition_Question(player, monster);
        break;
    }

    case Monster_Type::ARRAY_LOOP_TUTOR:
    {
        Array_Loop_Question(player, monster);
        break;
    }

    case Monster_Type::FUNCTION_TUTOR:
    {
        Function_Question(player, monster);
        break;
    }

    case Monster_Type::POINTER_MEMORY_TUTOR:
    {
        Pointer_Memory_Question(player, monster);
        break;
    }

    case Monster_Type::OBJECT_STL_TUTOR:
    {
        Object_Stl_Question(player, monster);
        break;
    }

    default:
        break;
    }
}

void Code_Snippet_Question(Player* player, Monster& monster)
{
    cout << endl;
    cout << "=================================" << endl;
    cout << "코드 스니펫의 망령이 문제를 냈다!" << endl;
    cout << "=================================" << endl;

    cout << "객체지향 프로그래밍에서" << endl;
    cout << "부모 클래스의 기능을 물려받는 것을 무엇이라고 할까?" << endl;

    cout << "- 추상화, 다형성, 캡슐화, 상속 -" << endl;

    string answer;

    cout << endl;
    cout << "정답 : ";
    cin >> answer;


    if (answer == "상속")
    {
        cout << endl;
        cout << "정답을 맞혔다!" << endl;
        cout << "코드 스니펫의 망령 공격을 무효화했다!" << endl;
    }
    else
    {
        int damage = monster.getPower() * 2;

        player->Set_Hp(player->Get_Hp() - damage);

        cout << endl;
        cout << "정답을 틀렸다!" << endl;
        cout << "코드 스니펫의 망령이 분노했다!" << endl;
        cout << damage << " 피해를 받았다!" << endl;
        cout << "(남은 체력 : " << player->Get_Hp() << ")" << endl;
    }
}

void Variable_Condition_Question(Player* player, Monster& monster)
{
    cout << endl;
    cout << "손승현 튜터님이 변수와 조건문 문제를 냈다!" << endl;

    string answer;

    cout << "정답 : ";
    cin >> answer;


    if (answer == "if")
    {
        cout << "정답을 맞혔다!" << endl;
        cout << "손승현 튜터님의 공격을 막았다!" << endl;
    }
    else
    {
        int damage = monster.getPower();

        player->Set_Hp(player->Get_Hp() - damage);

        cout << "정답을 틀렸다!" << endl;
        cout << "손승현 튜터님에게 " << damage << " 피해를 받았다!" << endl;
        cout << "(남은 체력 : " << player->Get_Hp() << ")" << endl;
    }
}

void Array_Loop_Question(Player* player, Monster& monster)
{
    cout << player->Get_Name() << "은(는) 배열과 반복문 코드를 분석하기 시작했다!" << endl;

    string answer;

    cout << "코드 문제의 정답 : ";
    cin >> answer;


    if (answer == "if")
    {
        cout << player->Get_Name() << "은(는) 정답을 입력했다!" << endl;
        cout << "코드 분석 성공!" << endl;
    }
    else
    {
        int damage = monster.getPower();

        cout << player->Get_Name() << "은(는) 오답을 입력했다!" << endl;
        cout << monster.getName() << "이(가) " << damage << "의 피해를 입혔다!" << endl;

        player->Set_Hp(player->Get_Hp() - damage);

        cout << "(남은 체력 : "
            << player->Get_Hp()
            << ")" << endl;
    }
}

void Function_Question(Player* player, Monster& monster)
{
    cout << player->Get_Name() << "은(는) 함수 코드를 분석하기 시작했다!" << endl;

    string answer;

    cout << "코드 문제의 정답 : ";
    cin >> answer;


    if (answer == "if")
    {
        cout << player->Get_Name() << "은(는) 함수 분석에 성공했다!" << endl;
    }
    else
    {
        int damage = monster.getPower();

        cout << player->Get_Name() << "은(는) 함수 분석에 실패했다!" << endl;
        cout << monster.getName() << "이(가) "
            << damage << "의 피해를 입혔다!" << endl;

        player->Set_Hp(player->Get_Hp() - damage);

        cout << "(남은 체력 : "
            << player->Get_Hp()
            << ")" << endl;
    }
}


void Pointer_Memory_Question(Player* player, Monster& monster)
{
    cout << player->Get_Name() << "은(는) 포인터와 메모리 문제를 확인했다!" << endl;

    string answer;

    cout << "코드 문제의 정답 : ";
    cin >> answer;


    if (answer == "if")
    {
        cout << player->Get_Name() << "은(는) 메모리 구조를 이해했다!" << endl;
    }
    else
    {
        int damage = monster.getPower();

        cout << player->Get_Name() << "은(는) 메모리 문제를 해결하지 못했다!" << endl;
        cout << monster.getName() << "이(가) "
            << damage << "의 피해를 입혔다!" << endl;

        player->Set_Hp(player->Get_Hp() - damage);

        cout << "(남은 체력 : "
            << player->Get_Hp()
            << ")" << endl;
    }
}


void Object_Stl_Question(Player* player, Monster& monster)
{
    cout << player->Get_Name() << "은(는) 객체지향과 STL 문제를 분석했다!" << endl;

    string answer;

    cout << "코드 문제의 정답 : ";
    cin >> answer;


    if (answer == "if")
    {
        cout << player->Get_Name() << "은(는) 객체지향 개념을 이해했다!" << endl;
    }
    else
    {
        int damage = monster.getPower();

        cout << player->Get_Name() << "은(는) STL 활용에 실패했다!" << endl;
        cout << monster.getName() << "이(가) "
            << damage << "의 피해를 입혔다!" << endl;

        player->Set_Hp(player->Get_Hp() - damage);

        cout << "(남은 체력 : "
            << player->Get_Hp()
            << ")" << endl;
    }
}
