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

	case Monster_Type::CODE_SNIPPET_WRAITH:
	{
		if (turnCount % 3 == 0)
		{
			return true;
		}

		break;
	}

    case Monster_Type::VARIABLE_CONDITION_TUTOR:
    {
        if (turnCount % 3 == 0)
        {
            return true;
        }
        break;
    }

    case Monster_Type::ARRAY_LOOP_TUTOR:
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

    default:
        break;
    }
}

void Code_Snippet_Question(Player* player, Monster& monster)
{
    cout << endl;
    cout << "=================================" << endl;
    cout << "코드 스니펫의 망령이 문제를 냅니다!" << endl;
    cout << "=================================" << endl;

    cout << "객체지향 프로그래밍에서" << endl;
    cout << "부모 클래스의 기능을 물려받는 것을 무엇이라고 할까요?" << endl;

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

void Variable_Condition_Question(Player* player, Monster& monster)
{
    cout << "변수와 조건문 문제입니다." << endl;

    string answer;

    cout << "정답 : ";
    cin >> answer;


    if (answer == "if")
    {
        cout << "정답!" << endl;
    }
    else
    {
        cout << "오답!" << endl;

        int damage = monster.getPower();

        player->Set_Hp(player->Get_Hp() - damage);
    }
}
