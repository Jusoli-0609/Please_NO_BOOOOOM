#include "DungeonManager.h"
#include "Battle.h"
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

namespace
{
	constexpr int BASE_TUTOR_REQUIRED_SCORE = 300;
	constexpr double CHAPTER_SCORE_MULTIPLIER = 1.3;
	constexpr int NORMAL_MONSTER_TYPE_COUNT = 3;
	constexpr int ELITE_APPEARANCE_RATE = 20;
}

Dungeon_Manager::Dungeon_Manager()
	: _current_Chapter(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_is_All_Chapter_Cleared(false),
	_current_Chapter_Score(0)
{
}

void Dungeon_Manager::Open_Dungeon(Player* player, Inventory& inventory)
{
	if (player == nullptr)
	{
		cout << "플레이어 정보가 없습니다." << endl;

		return;
	}

	if (_is_All_Chapter_Cleared)
	{
		cout << "모든 일반 챕터를 클리어했습니다." << endl;

		return;
	}

	Print_Current_Chapter();

	cout << "현재 챕터 점수: " << _current_Chapter_Score << endl;

	cout << "튜터 도전 요구 점수: " << Get_Required_Tutor_Score() << endl;

	if (Check_Tutor_Challenge_Available())
	{
		cout << "튜터에게 도전할 수 있습니다!" << endl;
	}
	else
	{
		cout << "튜터 도전까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았습니다." << endl;
	}

	int dungeon_Choice = -1;

	cout << endl;
	cout << "1. 현재 챕터 입장" << endl;
	cout << "0. 메인 메뉴로 돌아가기" << endl;
	cout << "선택: ";

	cin >> dungeon_Choice;

	switch (dungeon_Choice)
	{
	case 1:
	{
		Run_Current_Chapter(player, inventory);

		break;
	}

	case 0:
	{
		cout << "메인 메뉴로 돌아갑니다." << endl;

		break;
	}

	default:
	{
		cout << "잘못된 선택입니다." << endl;

		break;
	}
	}
}

bool Dungeon_Manager::Check_All_Chapter_Cleared() const
{
	return _is_All_Chapter_Cleared;
}

int Dungeon_Manager::Get_Current_Chapter_Score() const
{
	return _current_Chapter_Score;
}

void Dungeon_Manager::Add_Chapter_Score(int score_Reward)
{
	if (score_Reward <= 0)
	{
		return;
	}

	int max_Chapter_Score =
		Get_Required_Tutor_Score();

	if
		(_current_Chapter_Score >= max_Chapter_Score)
	{
		_current_Chapter_Score = max_Chapter_Score;
		cout << "현재 챕터 점수가 이미 최대입니다." << endl;

		return;
	}

	int previous_Score = _current_Chapter_Score;

	_current_Chapter_Score += score_Reward;

	if
		(_current_Chapter_Score > max_Chapter_Score)
	{
		_current_Chapter_Score = max_Chapter_Score;
	}

	int added_Score = _current_Chapter_Score - previous_Score;

	cout << "챕터 점수 +" << added_Score << endl;
	cout << "현재 챕터 점수: " << _current_Chapter_Score << " / " << max_Chapter_Score << endl;

	if
		(_current_Chapter_Score >= max_Chapter_Score)
	{
		cout << "튜터 도전 조건을 달성했습니다!" << endl;
	}
}

int Dungeon_Manager::Get_Required_Tutor_Score() const
{
	int chapter_Number = 1;

	switch (_current_Chapter)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		chapter_Number = 1;

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		chapter_Number = 2;

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		chapter_Number = 3;

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		chapter_Number = 4;

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		chapter_Number = 5;

		break;
	}

	default:
	{
		return 0;
	}
	}

	double required_Score = BASE_TUTOR_REQUIRED_SCORE;

	for
		(
			int chapter_Index = 1;
			chapter_Index < chapter_Number;
			chapter_Index++
			)
	{
		required_Score *= CHAPTER_SCORE_MULTIPLIER;
	}

	return static_cast<int>
		(required_Score + 0.5);
}

bool Dungeon_Manager::Check_Tutor_Challenge_Available() const
{
	return
		_current_Chapter_Score >= Get_Required_Tutor_Score();
}

void Dungeon_Manager::Print_Current_Chapter() const
{
	cout << endl;
	cout << "========================================" << endl;
	cout << "현재 입장 가능한 던전" << endl;
	cout << Get_Chapter_Name(_current_Chapter) << endl;
	cout << "========================================" << endl;
}

void Dungeon_Manager::Run_Current_Chapter(Player* player, Inventory& inventory)
{
	cout << endl;
    cout << Get_Chapter_Name(_current_Chapter) << "에 입장했습니다." << endl;

	bool is_Elite_Appeared = Check_Elite_Monster_Appearance();

	if (is_Elite_Appeared)
	{
		Monster elite_Monster;
		elite_Monster.Initialize_Elite_Monster(_current_Chapter);

		bool is_Correct = Run_Elite_Quiz(elite_Monster);

		if (is_Correct)
		{
			elite_Monster.Generate_Drop_Reward();

			cout << endl;
			cout << "========================================" << endl;
			cout << "[ 정예 몬스터 처치 보상 ]" << endl;
			cout << "========================================" << endl;
			cout << "획득 경험치: " << elite_Monster.getExpReward() << endl;
			cout << "획득 챕터 점수: " << elite_Monster.getScoreReward() << endl;
			cout << "획득 아이템: " << elite_Monster.getDropItemName() << " " << elite_Monster.getDropItemCount() << "개" << endl;
			cout << "획득 훈련장려금: " << elite_Monster.getGoldReward() << " 원" << endl;

			Add_Chapter_Score(elite_Monster.getScoreReward());
		}
		else
		{
			cout << endl;

			cout << "코드 스니펫의 망령이 도망갔습니다." << endl;

			cout << "이번 던전에서는 보상을 획득하지 못했습니다." << endl;
		}
		return;
	}

	Monster_Type random_Monster_Type = Get_Random_Normal_Monster();

	Monster monster(random_Monster_Type);

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 일반 몬스터 등장 ]" << endl;
	cout << monster.getName() << "이(가) 나타났습니다!" << endl;
	cout << "========================================" << endl;

	monster.Print_Monster_Info();

	Battle(player, monster, inventory);
	if (player->getHp() <= 0)
	{
		cout << endl;
		cout << "던전 공략에 실패했습니다." << endl;
		return;
	}

	if (monster.getHP() > 0)
	{
		cout << endl;
		cout << "몬스터를 처치하지 못했습니다." << endl;

		return;
	}

	cout << endl;

	cout << monster.getName() << " 처치 완료!" << endl;

	Add_Chapter_Score(monster.getScoreReward());

	cout << endl;
	cout << "========================================" << endl;

	cout << "현재 챕터 점수: " << _current_Chapter_Score << " / " << Get_Required_Tutor_Score() << endl;

	if (Check_Tutor_Challenge_Available())
	{
		cout << "튜터 도전 조건을 달성했습니다!" << endl;
	}
	else
	{
		cout << "튜터 도전까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았습니다." << endl;
	}

	cout << "========================================" << endl;
}


void Dungeon_Manager::Get_Current_Chapter_Monsters(Monster_Type monster_Types[]) const
{
	switch (_current_Chapter)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		monster_Types[0] = Monster_Type::INT_SLIME;
		monster_Types[1] = Monster_Type::BOOL_MUSHROOM;
		monster_Types[2] = Monster_Type::IF_GOBLIN;

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		monster_Types[0] = Monster_Type::ARRAY_JELLYFISH;
		monster_Types[1] = Monster_Type::FOR_SHARK;
		monster_Types[2] = Monster_Type::WHILE_WHALE;

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		monster_Types[0] = Monster_Type::PARAMETER_GIANT_FLY;
		monster_Types[1] = Monster_Type::RETURN_GARGOYLE;
		monster_Types[2] = Monster_Type::FUNCTION_MAGE;

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		monster_Types[0] = Monster_Type::POINTER_GHOST;
		monster_Types[1] = Monster_Type::NULL_BANSHEE;
		monster_Types[2] = Monster_Type::MEMORY_REAPER;

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		monster_Types[0] = Monster_Type::CLASS_MACHINE_DOLL;
		monster_Types[1] = Monster_Type::INHERITANCE_CHIMERA;
		monster_Types[2] = Monster_Type::VECTOR_DRONE;

		break;
	}

	default:
	{
		monster_Types[0] = Monster_Type::INT_SLIME;
		monster_Types[1] = Monster_Type::BOOL_MUSHROOM;
		monster_Types[2] = Monster_Type::IF_GOBLIN;

		break;
	}
	}
}

Monster_Type Dungeon_Manager::Get_Random_Normal_Monster() const
{
	Monster_Type monster_Types
		[NORMAL_MONSTER_TYPE_COUNT];

	Get_Current_Chapter_Monsters(monster_Types);

	int random_Index = rand() % NORMAL_MONSTER_TYPE_COUNT;

	return monster_Types[random_Index];
}

bool Dungeon_Manager::Check_Elite_Monster_Appearance() const
{
	int appearance_Roll = rand() % 100 + 1;

	return
		appearance_Roll <= ELITE_APPEARANCE_RATE;
}

Elite_Question Dungeon_Manager::Get_Elite_Question(Chapter_Type chapter_Type) const
{
	Elite_Question elite_Question;

	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		elite_Question.question = "정답은 2";
		elite_Question.choices[0] = "0";
		elite_Question.choices[1] = "2";
		elite_Question.choices[2] = "0";
		elite_Question.choices[3] = "0";
		elite_Question.correct_Answer = 2;
		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		elite_Question.question = "정답은 0";
		elite_Question.choices[0] = "0";
		elite_Question.choices[1] = "0";
		elite_Question.choices[2] = "0";
		elite_Question.choices[3] = "4";
		elite_Question.correct_Answer = 4;

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		elite_Question.question = "정답은 1";
		elite_Question.choices[0] = "1";
		elite_Question.choices[1] = "0";
		elite_Question.choices[2] = "0";
		elite_Question.choices[3] = "0";
		elite_Question.correct_Answer = 1;

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		elite_Question.question = "정답은 1";
		elite_Question.choices[0] ="1";
		elite_Question.choices[1] ="0";
		elite_Question.choices[2] ="0";
		elite_Question.choices[3] ="0";
		elite_Question.correct_Answer = 1;

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		elite_Question.question = "정답은 2";
		elite_Question.choices[0] = "0";
		elite_Question.choices[1] = "2";
		elite_Question.choices[2] = "0";
		elite_Question.choices[3] = "0";
		elite_Question.correct_Answer = 2;

		break;
	}

	default:
	{
		elite_Question.question = "정답은 1";
		elite_Question.choices[0] = "1";
		elite_Question.choices[1] = "0";
		elite_Question.choices[2] = "0";
		elite_Question.choices[3] = "0";
		elite_Question.correct_Answer = 1;

		break;
	}
	}

	return elite_Question;
}
bool Dungeon_Manager::Run_Elite_Quiz
(Monster& elite_Monster)
{
	Elite_Question elite_Question = Get_Elite_Question(elite_Monster.getChapterType());

	int player_Answer = 0;

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 정예 몬스터 등장 ]" << endl;
	cout << elite_Monster.getName() << "이(가) 나타났습니다!" << endl;
	cout << "\"코드 스니펫을 복사했습니다.\"" << endl;
	cout << "========================================" << endl;
	cout << endl;
	cout << elite_Question.question << endl;
	cout << endl;

	for
		(
			int choice_Index = 0;
			choice_Index < 4;
			choice_Index++
			)
	{
		cout << choice_Index + 1 << ". " << elite_Question.choices[choice_Index] << endl;
	}

	while (true)
	{
		cout << endl;
		cout << "정답 입력 (1~4): ";

		cin >> player_Answer;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "숫자를 입력해주세요." << endl;

			continue;
		}

		if
			(player_Answer >= 1 && player_Answer <= 4)
		{
			break;
		}

		cout << "1번부터 4번 사이의 번호를 입력해주세요." << endl;
	}

	if
		(player_Answer== elite_Question.correct_Answer)
	{
		cout << endl;
		cout << "정답입니다!" << endl;
		cout << "코드 스니펫의 망령을 처치했습니다." << endl;

		return true;
	}

	cout << endl;
	cout << "오답입니다!" << endl;
	cout << "코드 스니펫의 망령이 비웃으며 도망갔습니다.ㅋ" << endl;

	return false;
}

void Dungeon_Manager::Clear_Current_Chapter()
{
	cout << endl;

	cout << Get_Chapter_Name(_current_Chapter) << "을(를) 클리어했습니다!" << endl;

	Move_Next_Chapter();

	_current_Chapter_Score = 0;

	if (_is_All_Chapter_Cleared)
	{
		cout
			<< "모든 일반 챕터를 클리어했습니다!" << endl;

	}
	else
	{
		cout
			<< Get_Chapter_Name (_current_Chapter) << "이(가) 열렸습니다!" << endl;
	}
}

void Dungeon_Manager::Move_Next_Chapter()
{
	switch (_current_Chapter)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		_current_Chapter = Chapter_Type::ARRAY_LOOP_OCEAN;

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		_current_Chapter = Chapter_Type::FUNCTION_RUINS;

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		_current_Chapter = Chapter_Type::POINTER_MEMORY_GRAVEYARD;

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		_current_Chapter = Chapter_Type::OBJECT_STL_FACTORY;
		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		_current_Chapter = Chapter_Type::ALL_CHAPTER_CLEARED;

		_is_All_Chapter_Cleared = true;
		break;
	}

	default:
	{
		_is_All_Chapter_Cleared = true;
		break;
	}
	}
}
string Dungeon_Manager::Get_Chapter_Name
(
	Chapter_Type chapter_Type
) const
{
	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		return
			"챕터 1 - 변수·조건문 숲";
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		return
			"챕터 2 - 배열·반복문 바다";
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		return
			"챕터 3 - 함수 유적";
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		return
			"챕터 4 - 포인터·메모리 묘지";
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		return
			"챕터 5 - 객체지향·STL 공장";
	}

	default:
	{
		return
			"모든 일반 챕터 클리어";
	}
	}
}