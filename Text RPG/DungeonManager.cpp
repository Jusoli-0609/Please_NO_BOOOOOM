#include "DungeonManager.h"
#include "Battle_System.h"
#include <cstdlib>
#include <iostream>
#include <limits>

using namespace std;

namespace
{
	constexpr int BASE_TUTOR_REQUIRED_SCORE = 500; // 챕터 1 튜터 도전에 필요한 기본 점수
	constexpr double CHAPTER_SCORE_MULTIPLIER = 1.3; // 다음 챕터 요구 점수 증가 배율
	constexpr int NORMAL_MONSTER_TYPE_COUNT = 3; // 챕터별 일반 몬스터 종류 수
	constexpr int ELITE_APPEARANCE_RATE = 20; // 정예 몬스터 등장 확률

	constexpr int ELITE_GIMMICK_HP_PENALTY = 20; // 정예 몬스터 문제 실패 시 HP 감소량
	constexpr int TUTOR_GIMMICK_SCORE_PENALTY = 100; // 튜터 문제 실패 시 점수 감소량

	constexpr int MINIMUM_BATTLE_HP = 1; // 패널티를 받고 전투 중 최소 HP 제한
}

//=============================================================================
// 1. 던전 생성 및 메뉴 실행 파트
//=============================================================================

// 1-1. 던전 매니저 생성자
Dungeon_Manager::Dungeon_Manager()
	: _current_Chapter(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_is_All_Chapter_Cleared(false),
	_current_Chapter_Score(0)
{
}
// 1-2. 던전 메뉴 열기
void Dungeon_Manager::Open_Dungeon(Player* player, Inventory<Item>& inventory)
{
	if (player == nullptr)
	{
		cout << "플레이어 정보가 없습니다." << endl;

		return;
	}

	if (_is_All_Chapter_Cleared)
	{
		cout << "튜터님 5명의 시험을 모두 통과했습니다." << endl;

		Print_Tutor_Item_Status(inventory);

		if(Check_Final_Boss_Room_Available(inventory)== false)
		{
			return;
		}

		cout << endl;
		cout << "1. 최종보스방 입장" << endl;
		cout << "0. 돌아가기" << endl;
		cout << "선택: ";

		int final_Boss_Choice = 0;

		cin >> final_Boss_Choice;

		switch (final_Boss_Choice)
		{
		case 1:
		{
			Run_Final_Boss_Room(player, inventory);

			break;
		}

		case 0:
		{
			cout << "최종보스방 입장을 취소했습니다." << endl;

			break;
		}

		default:
		{
			cout << "잘못된 선택입니다." << endl;

			break;
		}
		}

		return;
	}

	Print_Current_Chapter();

	cout << "튜터님 시험까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았습니다." << endl;
	cout << "튜터님 시험까지 점수 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "이(가) 남았습니다." << endl;

	if (Check_Tutor_Challenge_Available())
	{
		cout << "튜터님의 시험을 칠 수 있습니다.!" << endl;
	}
	else
	{
		cout << "튜터님 시험까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았습니다." << endl;
	}

	int dungeon_Choice = -1;

	cout << endl;
	cout << "1. 현재 챕터 입장" << endl;
	cout << "2. 몬스터 처치 기록 확인" << endl;
	cout << "3. 튜터님 시험보기" << endl;
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

	case 2:
	{
		Print_Current_Chapter_Kill_Log();

		break;
	}

	case 3:
	{
		Run_Tutor_Challenge(player, inventory);

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

//=============================================================================
// 2. 챕터 상태 조회 및 출력 파트
//=============================================================================

// 2-1. 전체 챕터 클리어 여부 조회
bool Dungeon_Manager::Check_All_Chapter_Cleared() const
{
	return _is_All_Chapter_Cleared;
}
// 2-2. 현재 챕터 점수 조회
int Dungeon_Manager::Get_Current_Chapter_Score() const
{
	return _current_Chapter_Score;
}
// 2-3. 현재 입장 가능한 챕터 출력
void Dungeon_Manager::Print_Current_Chapter() const
{
	cout << endl;
	cout << "========================================" << endl;
	cout << "현재 입장 가능한 던전" << endl;
	cout << Get_Chapter_Name(_current_Chapter) << endl;
	cout << "========================================" << endl;
}
// 2-4. 챕터 이름 변환
string Dungeon_Manager::Get_Chapter_Name(Chapter_Type chapter_Type) const

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

//=============================================================================
// 3. 현재 챕터 진행 파트
//=============================================================================

// 3-1. 현재 챕터 몬스터 및 정예 몬스터 이벤트 진행
void Dungeon_Manager::Run_Current_Chapter(Player* player, Inventory<Item>& inventory)
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

			if (player != nullptr)
			{
				player->Gain_Exp(elite_Monster.getExpReward());
			}

			cout << endl;
			cout << "========================================" << endl;
			cout << "[ 정예 몬스터 처치 보상 ]" << endl;
			cout << "========================================" << endl;
			cout << "획득 경험치: " << elite_Monster.getExpReward() << endl;
			cout << "획득 점수: " << elite_Monster.getScoreReward() << endl;

			elite_Monster.Print_Drop_Reward();

			Give_Drop_Items_To_Inventory(elite_Monster, inventory);

			cout << "획득 훈련장려금: " << elite_Monster.getGoldReward() << "원" << endl;
			cout << "========================================" << endl;

			Record_Monster_Kill
			(elite_Monster);
		}
		else
		{
			Apply_Elite_Gimmick_Failure_Penalty(player);

			cout << endl;
			cout << "코드스니펫의 망령이 도망갔습니다." << endl;
			cout << "보상을 획득하지 못했습니다." << endl;
		}
	}

	Monster_Type random_Monster_Type = Get_Random_Normal_Monster();
	Monster monster(random_Monster_Type);

	if (player != nullptr)
	{
		monster.Apply_Player_Level_Scaling(player->getLevel());
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 일반 몬스터 등장 ]" << endl;
	cout << monster.getName() << "이(가) 나타났습니다!" << endl;
	cout << "========================================" << endl;

	monster.Print_Monster_Info();
	monster.Generate_Drop_Reward();

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
	cout << "========================================" << endl;
	cout << "[ 일반 몬스터 처치 보상 ]" << endl;
	cout << "========================================" << endl;

	monster.Print_Drop_Reward();

	Give_Drop_Items_To_Inventory(monster, inventory);

	cout << "획득 훈련장려금: " << monster.getGoldReward() << "원" << endl;
	cout << "========================================" << endl;
	cout << endl;
	cout << monster.getName() << " 처치 완료!" << endl;

	Record_Monster_Kill(monster);

	if (Check_Tutor_Challenge_Available())
	{
		cout << "튜터님 시험 조건을 달성했습니다!" << endl;
	}
	else
	{
		cout << "튜터님 시험까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았습니다." << endl;
	}

	cout << "========================================" << endl;
}

//=============================================================================
// 4. 일반 몬스터 선택 파트
//=============================================================================

// 4-1. 현재 챕터 일반 몬스터 목록 구성
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
// 4-2. 현재 챕터 일반 몬스터 랜덤 선택
Monster_Type Dungeon_Manager::Get_Random_Normal_Monster() const
{
	Monster_Type monster_Types
		[NORMAL_MONSTER_TYPE_COUNT];

	Get_Current_Chapter_Monsters(monster_Types);

	int random_Index = rand() % NORMAL_MONSTER_TYPE_COUNT;

	return monster_Types[random_Index];
}

//=============================================================================
// 5. 정예 몬스터 파트
//=============================================================================

// 5-1. 정예 몬스터 등장 확률 판정
bool Dungeon_Manager::Check_Elite_Monster_Appearance() const
{
	int appearance_Roll = rand() % 100 + 1;

	return
		appearance_Roll <= ELITE_APPEARANCE_RATE;
}
// 5-2. 챕터별 정예 문제 랜덤 선택
Elite_Question Dungeon_Manager::Get_Elite_Question(Chapter_Type chapter_Type) const
{
	Elite_Question elite_Questions[3];

	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		elite_Questions[0].question = "다음 중 정수값을 저장하는 자료형은 무엇인가?";

		elite_Questions[0].choices[0] = "int";
		elite_Questions[0].choices[1] = "bool";
		elite_Questions[0].choices[2] = "if";
		elite_Questions[0].choices[3] = "while";

		elite_Questions[0].correct_Answer = 1;


		elite_Questions[1].question =
			"다음 코드에서 출력되는 결과는 무엇인가?\n"
			"int number = 10;\n"
			"if (number > 5)\n"
			"{\n"
			"\tcout << \"통과\";\n"
			"}";

		elite_Questions[1].choices[0] = "아무것도 출력되지 않음";
		elite_Questions[1].choices[1] = "통과";
		elite_Questions[1].choices[2] = "10";
		elite_Questions[1].choices[3] = "오류 발생";

		elite_Questions[1].correct_Answer = 2;


		elite_Questions[2].question = "참 또는 거짓만 저장할 수 있는 자료형은 무엇인가?";

		elite_Questions[2].choices[0] = "int";
		elite_Questions[2].choices[1] = "string";
		elite_Questions[2].choices[2] = "bool";
		elite_Questions[2].choices[3] = "float";

		elite_Questions[2].correct_Answer = 3;

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		elite_Questions[0].question = "다음 배열에서 두 번째 값은 무엇인가?\n" "int numbers[3] = { 10, 20, 30 };";

		elite_Questions[0].choices[0] = "10";
		elite_Questions[0].choices[1] = "20";
		elite_Questions[0].choices[2] = "30";
		elite_Questions[0].choices[3] = "3";

		elite_Questions[0].correct_Answer = 2;


		elite_Questions[1].question = "반복 횟수가 정해져 있을 때 주로 사용하는 반복문은 무엇인가?";

		elite_Questions[1].choices[0] = "if";
		elite_Questions[1].choices[1] = "switch";
		elite_Questions[1].choices[2] = "for";
		elite_Questions[1].choices[3] = "return";

		elite_Questions[1].correct_Answer = 3;


		elite_Questions[2].question =
			"다음 반복문은 몇 번 실행되나요?\n"
			"int count = 0;\n"
			"while (count < 3)\n"
			"{\n"
			"\tcount++;\n"
			"}";

		elite_Questions[2].choices[0] = "1번";
		elite_Questions[2].choices[1] = "2번";
		elite_Questions[2].choices[2] = "3번";
		elite_Questions[2].choices[3] = "무한 반복";

		elite_Questions[2].correct_Answer = 3;

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		elite_Questions[0].question = "함수에 값을 전달하기 위해 사용하는 것은 무엇인가?";

		elite_Questions[0].choices[0] = "반환값";
		elite_Questions[0].choices[1] = "매개변수";
		elite_Questions[0].choices[2] = "조건문";
		elite_Questions[0].choices[3] = "배열";

		elite_Questions[0].correct_Answer = 2;


		elite_Questions[1].question = "함수에서 계산한 결과를 돌려줄 때 사용하는 키워드는 무엇인가?";

		elite_Questions[1].choices[0] = "return";
		elite_Questions[1].choices[1] = "break";
		elite_Questions[1].choices[2] = "continue";
		elite_Questions[1].choices[3] = "switch";

		elite_Questions[1].correct_Answer = 1;


		elite_Questions[2].question =
			"다음 함수의 반환값은 무엇인가요?\n"
			"int Add(int number_A, int number_B)\n"
			"{\n"
			"\treturn number_A + number_B;\n"
			"}\n"
			"Add(3, 5);";

		elite_Questions[2].choices[0] = "2";
		elite_Questions[2].choices[1] = "3";
		elite_Questions[2].choices[2] = "5";
		elite_Questions[2].choices[3] = "8";

		elite_Questions[2].correct_Answer = 4;

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		elite_Questions[0].question = "변수의 메모리 주소를 저장하는 변수는 무엇인가?";

		elite_Questions[0].choices[0] = "배열";
		elite_Questions[0].choices[1] = "포인터";
		elite_Questions[0].choices[2] = "함수";
		elite_Questions[0].choices[3] = "반복문";

		elite_Questions[0].correct_Answer = 2;


		elite_Questions[1].question = "포인터가 아무 주소도 가리키지 않음을 나타내는 값은 무엇인가?";

		elite_Questions[1].choices[0] = "false";
		elite_Questions[1].choices[1] = "zero";
		elite_Questions[1].choices[2] = "nullptr";
		elite_Questions[1].choices[3] = "empty";

		elite_Questions[1].correct_Answer = 3;


		elite_Questions[2].question = "다음 코드에서 pointer에 저장되는 것은 무엇인가?\n" "int number = 10;\n" "int* pointer = &number;";

		elite_Questions[2].choices[0] = "number의 값 10";
		elite_Questions[2].choices[1] = "number의 메모리 주소";
		elite_Questions[2].choices[2] = "pointer의 이름";
		elite_Questions[2].choices[3] = "nullptr";

		elite_Questions[2].correct_Answer = 2;

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		elite_Questions[0].question = "데이터와 기능을 하나로 묶어 표현하는 문법은 무엇인가?";

		elite_Questions[0].choices[0] = "class";
		elite_Questions[0].choices[1] = "while";
		elite_Questions[0].choices[2] = "return";
		elite_Questions[0].choices[3] = "if";

		elite_Questions[0].correct_Answer = 1;


		elite_Questions[1].question = "기존 클래스의 기능을 새로운 클래스가 물려받는 것은 무엇인가?";

		elite_Questions[1].choices[0] = "반복";
		elite_Questions[1].choices[1] = "상속";
		elite_Questions[1].choices[2] = "조건";
		elite_Questions[1].choices[3] = "포인터";

		elite_Questions[1].correct_Answer = 2;


		elite_Questions[2].question = "크기를 자유롭게 늘리거나 줄일 수 있는 STL 컨테이너는 무엇인가?";

		elite_Questions[2].choices[0] = "if";
		elite_Questions[2].choices[1] = "int";
		elite_Questions[2].choices[2] = "vector";
		elite_Questions[2].choices[3] = "return";

		elite_Questions[2].correct_Answer = 3;

		break;
	}

	default:
	{
		elite_Questions[0].question = "정수를 저장하는 자료형은 무엇인가?";

		elite_Questions[0].choices[0] = "int";
		elite_Questions[0].choices[1] = "bool";
		elite_Questions[0].choices[2] = "if";
		elite_Questions[0].choices[3] = "while";

		elite_Questions[0].correct_Answer = 1;

		elite_Questions[1] = elite_Questions[0];

		elite_Questions[2] = elite_Questions[0];

		break;
	}
	}

	int random_Question_Index =
		rand() % 3;

	return
		elite_Questions[random_Question_Index];
}
// 5-3. 정예 문제 출력 및 정답 판정
bool Run_Elite_Question(const Elite_Question& elite_Question);
// 5-4. 정예 몬스터 퀴즈 전체 진행
bool Dungeon_Manager::Run_Elite_Quiz(Monster& elite_Monster)
{
	Elite_Question elite_Question = Get_Elite_Question(elite_Monster.getChapterType());

	int player_Answer = 0;

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 정예 몬스터 등장 ]" << endl;
	cout << elite_Monster.getName() << "이(가) 나타났습니다!" << endl;
	cout << "\"코드스니펫을 복사했습니다.\"" << endl;
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
		(player_Answer == elite_Question.correct_Answer)
	{
		cout << endl;
		cout << "정답입니다!" << endl;
		cout << "코드스니펫의 망령을 처치했습니다." << endl;

		return true;
	}

	cout << endl;
	cout << "오답입니다!" << endl;
	cout << "코드스니펫의 망령이 비웃으며 도망갔습니다.ㅋ" << endl;

	return false;
}

//=============================================================================
// 6. 튜터 보스 파트
//=============================================================================

// 6-1. 챕터별 튜터 문제 구성
void Dungeon_Manager::Get_Tutor_Questions(Chapter_Type chapter_Type, Tutor_Question tutor_Questions[]) const
{
	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		tutor_Questions[0].description = "정수를 저장할 자료형을 입력하세요.";
		tutor_Questions[0].code = "____ score = 100;";
		tutor_Questions[0].correct_Answer = "int";

		tutor_Questions[1].description = "참 또는 거짓을 저장할 자료형을 입력하세요.";
		tutor_Questions[1].code = "____ is_Clear = true;";
		tutor_Questions[1].correct_Answer = "bool";

		tutor_Questions[2].description = "조건을 검사하는 코드를 입력하세요.";
		tutor_Questions[2].code = "____ (score >= 100)\n" "{\n" "\tcout << \"입장 가능\";\n" "}";
		tutor_Questions[2].correct_Answer = "if";

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		tutor_Questions[0].description = "여러 값을 순서대로 저장하는 자료구조의 이름을 입력하세요.";
		tutor_Questions[0].code = "int numbers[3] = { 1, 2, 3 };\n" "// 위 자료구조의 이름: ____";
		tutor_Questions[0].correct_Answer = "array";

		tutor_Questions[1].description = "정해진 횟수만큼 반복하는 코드를 입력하세요.";
		tutor_Questions[1].code = "____ (int i = 0; i < 3; i++)\n" "{\n" "\tcout << i << endl;\n" "}";
		tutor_Questions[1].correct_Answer = "for";

		tutor_Questions[2].description = "조건이 참인 동안 반복하는 코드를 입력하세요.";
		tutor_Questions[2].code = "____ (count < 3)\n" "{\n" "\tcount++;\n" "}";
		tutor_Questions[2].correct_Answer = "while";

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		tutor_Questions[0].description = "함수로 전달받는 number의 역할을 영어로 입력하세요.";
		tutor_Questions[0].code = "void Print_Number(int number)\n" "{\n" "\tcout << number;\n" "}\n" "// number의 역할: ____";
		tutor_Questions[0].correct_Answer = "parameter";

		tutor_Questions[1].description = "함수의 계산 결과를 반환하는 코드를 입력하세요.";
		tutor_Questions[1].code = "int Add(int number_A, int number_B)\n" "{\n" "\t____ number_A + number_B;\n" "}";
		tutor_Questions[1].correct_Answer = "return";

		tutor_Questions[2].description = "Add와 같이 특정 기능을 묶은 코드 단위를 영어로 입력하세요.";
		tutor_Questions[2].code = "int Add(int number_A, int number_B)\n" "{\n" "\treturn number_A + number_B;\n" "}\n" "// 위 코드 단위: ____";
		tutor_Questions[2].correct_Answer = "function";

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		tutor_Questions[0].description = "메모리 주소를 저장하는 변수의 종류를 영어로 입력하세요.";
		tutor_Questions[0].code = "int value = 10;\n" "int* value_Pointer = &value;\n" "// value_Pointer의 종류: ____";
		tutor_Questions[0].correct_Answer = "pointer";

		tutor_Questions[1].description = "포인터가 아무 주소도 가리키지 않는 상태를 영어로 입력하세요.";
		tutor_Questions[1].code = "int* value_Pointer = nullptr;\n" "// 값이 없는 상태: ____";
		tutor_Questions[1].correct_Answer = "null";

		tutor_Questions[2].description = "변수의 값이 저장되는 공간을 영어로 입력하세요.";
		tutor_Questions[2].code = "int value = 10;\n" "// value가 저장되는 공간: ____";
		tutor_Questions[2].correct_Answer = "memory";

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		tutor_Questions[0].description = "객체를 만들기 위한 설계도를 선언하는 코드를 입력하세요.";
		tutor_Questions[0].code = "____ Player\n" "{\n" "public:\n" "\tint hp;\n" "};";
		tutor_Questions[0].correct_Answer = "class";

		tutor_Questions[1].description = "부모 클래스의 기능을 자식 클래스가 물려받는 관계를 영어로 입력하세요.";
		tutor_Questions[1].code = "class Child : public Parent\n" "{\n" "};\n" "// 위 클래스 관계: ____";
		tutor_Questions[1].correct_Answer = "inheritance";

		tutor_Questions[2].description = "크기가 동적으로 변하는 STL 컨테이너를 입력하세요.";
		tutor_Questions[2].code = "____<int> numbers;\n" "numbers.push_back(10);";
		tutor_Questions[2].correct_Answer = "vector";

		break;
	}

	default:
	{
		tutor_Questions[0].description = "정수를 저장할 자료형을 입력하세요.";
		tutor_Questions[0].code = "____ score = 100;";
		tutor_Questions[0].correct_Answer = "int";

		tutor_Questions[1].description = "참 또는 거짓을 저장할 자료형을 입력하세요.";
		tutor_Questions[1].code = "____ is_Clear = true;";
		tutor_Questions[1].correct_Answer = "bool";

		tutor_Questions[2].description = "조건을 검사하는 코드를 입력하세요.";
		tutor_Questions[2].code = "____ (score >= 100)";
		tutor_Questions[2].correct_Answer = "if";

		break;
	}
	}
}
// 6-2. 챕터별 튜터 대사 구성
Tutor_Dialogue Dungeon_Manager::Get_Tutor_Dialogue(Chapter_Type chapter_Type) const
{
	Tutor_Dialogue tutor_Dialogue;

	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		tutor_Dialogue.appearance_Message = "등장";
		tutor_Dialogue.correct_Message = "맞음";
		tutor_Dialogue.wrong_Message = "틀림";
		tutor_Dialogue.exit_Message = "퇴장";

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		tutor_Dialogue.appearance_Message = "등장";
		tutor_Dialogue.correct_Message = "맞음";
		tutor_Dialogue.wrong_Message = "틀림";
		tutor_Dialogue.exit_Message = "퇴장";

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		tutor_Dialogue.appearance_Message = "등장";
		tutor_Dialogue.correct_Message = "맞음";
		tutor_Dialogue.wrong_Message = "틀림";
		tutor_Dialogue.exit_Message = "퇴장";

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		tutor_Dialogue.appearance_Message = "등장";
		tutor_Dialogue.correct_Message = "맞음";
		tutor_Dialogue.wrong_Message = "틀림";
		tutor_Dialogue.exit_Message = "퇴장";

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		tutor_Dialogue.appearance_Message = "등장";
		tutor_Dialogue.correct_Message = "맞음";
		tutor_Dialogue.wrong_Message = "틀림";
		tutor_Dialogue.exit_Message = "퇴장";

		break;
	}

	default:
	{
		tutor_Dialogue.appearance_Message = "등장";
		tutor_Dialogue.correct_Message = "맞음";
		tutor_Dialogue.wrong_Message = "틀림";
		tutor_Dialogue.exit_Message = "퇴장";

		break;
	}
	}

	return tutor_Dialogue;
}
// 6-3. 튜터 코드 문제 3개 진행
bool Dungeon_Manager::Run_Tutor_Code_Challenge(const Monster& tutor_Monster)
{
	Tutor_Question tutor_Questions[TUTOR_QUESTION_COUNT];

	Get_Tutor_Questions(_current_Chapter, tutor_Questions);

	Tutor_Dialogue tutor_Dialogue = Get_Tutor_Dialogue(_current_Chapter);

	int correct_Count = 0;

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ " << tutor_Monster.getName() << " 코드 검증 ]" << endl;
	cout << "========================================" << endl;
	cout << tutor_Monster.getName() << ": " << tutor_Dialogue.appearance_Message << endl;
	cout << endl;
	cout << "현재 챕터: " << Get_Chapter_Name(_current_Chapter) << endl;
	cout << "3문제 중 2문제 이상 맞히면 클리어됩니다." << endl;

	for
		(
			int question_Index = 0;
			question_Index < TUTOR_QUESTION_COUNT;
			question_Index++
			)
	{
		cout << endl;
		cout << "----------------------------------------" << endl;
		cout << "[ 문제 " << question_Index + 1 << " ]" << endl;
		cout << tutor_Questions[question_Index].description << endl;
		cout << endl;
		cout << tutor_Questions[question_Index].code << endl;
		cout << endl;
		cout << "정답: ";

		string player_Answer;

		cin >> player_Answer;

		if
			(
				player_Answer
				== tutor_Questions[question_Index].correct_Answer
				)
		{
			correct_Count += 1;

			cout << "정답입니다." << endl;
			cout << tutor_Monster.getName() << ": " << tutor_Dialogue.correct_Message << endl;
		}
		else
		{
			cout << "오답입니다." << endl;
			cout << "정답: " << tutor_Questions[question_Index].correct_Answer << endl;
			cout << tutor_Monster.getName() << ": " << tutor_Dialogue.wrong_Message << endl;
		}
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "정답 수: " << correct_Count << " / " << TUTOR_QUESTION_COUNT << endl;

	bool is_Cleared = correct_Count >= TUTOR_CLEAR_CORRECT_COUNT;

	if (is_Cleared)
	{
		cout << tutor_Monster.getName() << "의 코드 검증을 통과했습니다!" << endl;
	}
	else
	{
		cout << tutor_Monster.getName() << "의 코드 검증에 실패했습니다." << endl;
		cout << "2문제 이상 맞혀야 챕터를 클리어할 수 있습니다." << endl;
	}
	cout << tutor_Monster.getName() << ": " << tutor_Dialogue.exit_Message << endl;
	cout << "========================================" << endl;

	return is_Cleared;
}
// 6-4. 튜터 도전 및 클리어 처리
void Dungeon_Manager::Run_Tutor_Challenge(Player* player, Inventory<Item>& inventory)
{
	if
		(Check_Tutor_Challenge_Available() == false)
	{
		int required_Score = Get_Required_Tutor_Score();

		int remaining_Score = required_Score - _current_Chapter_Score;

		cout << endl;
		cout << "========================================" << endl;
		cout << "튜터님의 시험 조건을 충족하지 못했습니다." << endl;
		cout << "현재 점수: " << _current_Chapter_Score << " / " << required_Score << endl;
		cout << "필요한 추가 점수: " << remaining_Score << endl;
		cout << "========================================" << endl;

		return;
	}

	Monster tutor_Monster;

	tutor_Monster.Initialize_Tutor_Monster(_current_Chapter);

	bool is_Cleared = Run_Tutor_Code_Challenge(tutor_Monster);

	if (is_Cleared == false)
	{
		Apply_Tutor_Gimmick_Failure_Penalty();

		cout << endl;
		cout << "튜터님 시험에 실패했습니다." << endl;
		cout << "부족한 점수를 다시 모은 뒤 도전할 수 있습니다." << endl;

		return;
	}

	bool is_Tutor_Item_Given = Give_Tutor_Clear_Item(_current_Chapter, inventory);

	if (is_Tutor_Item_Given == false)
	{
		return;
	}

	if (player != nullptr)
	{
		player->Gain_Exp(tutor_Monster.getExpReward());
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ " << tutor_Monster.getName() << " 클리어 보상 ]" << endl;
	cout << "========================================" << endl;
	cout << "획득 경험치: " << tutor_Monster.getExpReward() << endl;
	cout << "획득 고유 아이템: " << Create_Tutor_Clear_Item(_current_Chapter)._Item_Name << endl;
	cout << "========================================" << endl;

	Record_Monster_Kill(tutor_Monster);

	Clear_Current_Chapter();
}

//=============================================================================
// 8. 기믹 실패 패널티 처리 파트
//=============================================================================

// 8-1. 정예 몬스터 기믹 실패 시 플레이어 HP 감소
void Dungeon_Manager::Apply_Elite_Gimmick_Failure_Penalty(Player* player)
{
	if (player == nullptr)
	{
		return;
	}

	int previous_HP = player->Get_Hp();

	int changed_HP = previous_HP - ELITE_GIMMICK_HP_PENALTY;

	if (changed_HP < MINIMUM_BATTLE_HP)
	{
		changed_HP = MINIMUM_BATTLE_HP;
	}

	player->Set_Hp
	(changed_HP);

	int decreased_HP = previous_HP - player->Get_Hp();

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 정예 몬스터 기믹 실패 패널티 ]" << endl;
	cout << "========================================" << endl;
	cout << "플레이어의 HP가 " << decreased_HP << " 감소했습니다." << endl;
	cout << "현재 HP: " << previous_HP << " -> " << player->Get_Hp() << endl;
	cout << "========================================" << endl;
}
// 8-2. 중간보스 튜터 기믹 실패 시 현재 챕터 점수 감소
void Dungeon_Manager::Apply_Tutor_Gimmick_Failure_Penalty()
{
	int previous_Score = _current_Chapter_Score;

	_current_Chapter_Score -= TUTOR_GIMMICK_SCORE_PENALTY;

	if (_current_Chapter_Score < 0)
	{
		_current_Chapter_Score = 0;
	}

	int decreased_Score = previous_Score - _current_Chapter_Score;

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 튜터님 기믹 실패 패널티 ]" << endl;
	cout << "========================================" << endl;
	cout << "현재 챕터 점수가 " << decreased_Score << " 감소했습니다." << endl;
	cout << "현재 챕터 점수: " << previous_Score << " -> " << _current_Chapter_Score << endl;
	cout << "튜터님에게 다시 도전하려면 부족한 점수를 다시 모아야 합니다." << endl;
	cout << "========================================" << endl;
}


//=============================================================================
// 8. 처치 기록 및 일반 보상 파트
//=============================================================================

// 8-1. 몬스터 처치 및 튜터 클리어 기록 저장
void Dungeon_Manager::Record_Monster_Kill(const Monster& monster)
{
	Monster_Type monster_Type = monster.getMonsterType();

	Monster_Kill_Record& kill_Record = _monster_Kill_Log
		[_current_Chapter]
		[monster_Type];

	if (kill_Record.monster_Name.empty())
	{
		kill_Record.monster_Name = monster.getName();
	}

	kill_Record.monster_Grade = monster.getMonsterGrade();

	kill_Record.kill_Count += 1;

	kill_Record.earned_Score += monster.getScoreReward();

	Monster_Kill_Count += 1;

	if
		(monster.getMonsterGrade() != Monster_Grade::TUTOR)
	{
		Add_Chapter_Score(monster.getScoreReward());
	}
}
// 8-2. 현재 챕터 처치 기록 출력
void Dungeon_Manager::Print_Current_Chapter_Kill_Log() const
{
	cout << endl;
	cout << "========================================" << endl;
	cout << "[ " << Get_Chapter_Name(_current_Chapter) << " 처치 기록 ]" << endl;
	cout << "========================================" << endl;

	auto chapter_Log = _monster_Kill_Log.find(_current_Chapter);

	if
		(
			chapter_Log
			== _monster_Kill_Log.end()
			|| chapter_Log->second.empty()
			)
	{
		cout << "아직 처치한 몬스터가 없습니다." << endl;
		cout << "========================================" << endl;

		return;
	}

	int total_Kill_Count = 0;
	int total_Earned_Score = 0;

	for
		(const auto& monster_Log : chapter_Log->second)
	{
		const Monster_Kill_Record& kill_Record = monster_Log.second;

		cout << kill_Record.monster_Name << ": " << kill_Record.kill_Count;

		if
			(kill_Record.monster_Grade == Monster_Grade::TUTOR)
		{
			cout << "회 클리어";
		}
		else
		{
			cout << "마리";
		}

		cout << " / 획득 점수 " << kill_Record.earned_Score << endl;

		total_Kill_Count += kill_Record.kill_Count;
		total_Earned_Score += kill_Record.earned_Score;
	}

	cout << "----------------------------------------" << endl;
	cout << "현재 챕터 총 처치 수: " << total_Kill_Count << "마리" << endl;
	cout << "누적 획득 점수: " << total_Earned_Score << endl;
	cout << "현재 적용 점수: " << _current_Chapter_Score << " / " << Get_Required_Tutor_Score() << endl;
	cout << "========================================" << endl;
}
// 8-3. 드롭 아이템 인벤토리 지급
void Dungeon_Manager::Give_Drop_Items_To_Inventory(const Monster& monster, Inventory<Item>& inventory)
{
	const std::vector<Item>& drop_Items = monster.getDropItems();

	for
		(const Item& drop_Item : drop_Items)
	{
		bool is_Added = inventory.Add_Or_Increase_Item(drop_Item);

		if (is_Added == false)
		{
			cout << drop_Item._Item_Name << " 획득을 취소했습니다." << endl;
		}
	}
}

//=============================================================================
// 9. 챕터 점수 및 이동 파트
//=============================================================================

// 9-1. 현재 챕터 점수 추가
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
		cout << "튜터님 시험 조건을 달성했습니다!" << endl;
	}
}
// 9-2. 챕터별 튜터 도전 요구 점수 계산
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
// 9-3. 튜터 도전 가능 여부 확인
bool Dungeon_Manager::Check_Tutor_Challenge_Available() const
{
	return
		_current_Chapter_Score >= Get_Required_Tutor_Score();
}
// 9-4. 현재 챕터 클리어 처리
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
// 9-5. 다음 챕터 이동
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
// 9-6. 최종보스방 입장 및 최종보스 생성
void Dungeon_Manager::Run_Final_Boss_Room(Player* player,Inventory<Item>& inventory)
{
	if (_is_All_Chapter_Cleared == false)
	{
		cout << endl;
		cout << "아직 모든 챕터를 클리어하지 못했습니다." << endl;

		return;
	}

	if
		(Check_Final_Boss_Room_Available(inventory) == false)
	{
		cout << endl;
		cout << "튜터님들의 고유 아이템이 부족합니다." << endl;
		cout << "고유 아이템 5종을 모두 모아야 최종보스방에 입장할 수 있습니다." << endl;

		return;
	}

	Monster kim_Dong_Hyun_Manager;

	kim_Dong_Hyun_Manager.Initialize_Final_Boss(Monster_Type::KIM_DONG_HYUN_MANAGER);

	Monster moon_Seung_Ho_Manager;

	moon_Seung_Ho_Manager.Initialize_Final_Boss(Monster_Type::MOON_SEUNG_HO_MANAGER);

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 최종보스방 ]" << endl;
	cout << "========================================" << endl;
	cout << "튜터님들의 고유 아이템이 하나의 열쇠로 반응합니다." << endl;
	cout << "잠겨 있던 최종보스방의 문이 열렸습니다." << endl;
	cout << endl;
	cout << "첫 번째 최종보스 " << kim_Dong_Hyun_Manager.getName() << "이(가) 등장했습니다!" << endl;

	kim_Dong_Hyun_Manager.Print_Attack_Message();

	cout << endl;
	cout << "[ 1차 최종보스 정보 ]" << endl;

	kim_Dong_Hyun_Manager.Print_Monster_Info();

	cout << endl;
	cout << "두 번째 최종보스는 " << moon_Seung_Ho_Manager.getName() << "입니다." << endl;
	cout << "김동현 매니저님을 물리치면 두 번째 전투가 시작됩니다." << endl;
	cout << "========================================" << endl;
}

//=============================================================================
// 10. 튜터 고유 아이템 및 최종보스방 조건 파트
//=============================================================================

// 10-1. 챕터별 튜터 고유 아이템 생성
Item Dungeon_Manager::Create_Tutor_Clear_Item(Chapter_Type chapter_Type) const
{
	Item tutor_Item;
	tutor_Item._Item_Price = 0;
	tutor_Item._Item_Count = 1;
	tutor_Item._Item_Type_Usable = false;
	tutor_Item._Item_Type_Wearable = false;

	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		tutor_Item._Item_Name = "손승현 튜터님의 로지텍 마우스";
		tutor_Item._Item_Weight = 0;

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		tutor_Item._Item_Name = "박은일 튜터님의 갈축 키포드";
		tutor_Item._Item_Weight = 0;

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		tutor_Item._Item_Name = "강신호 튜터님의 게이밍 헤드셋";
		tutor_Item._Item_Weight = 0;

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		tutor_Item._Item_Name = "문승현 튜터님의 고양이 버츄얼";
		tutor_Item._Item_Weight = 0;

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		tutor_Item._Item_Name = "김하늘 튜터님의 도수높은 안경";
		tutor_Item._Item_Weight = 0;

		break;
	}

	default:
	{
		tutor_Item._Item_Name = "";
		tutor_Item._Item_Count = 0;
		tutor_Item._Item_Weight = 0;

		break;
	}
	}

	return tutor_Item;
}
// 10-2. 인벤토리 아이템 보유 여부 확인
bool Dungeon_Manager::Has_Item_In_Inventory(Inventory<Item>& inventory, const std::string& item_Name) const
{
	for
		(
			int item_Index = 0;
			item_Index < inventory.Get_Size();
			item_Index++
			)
	{
		Item* inventory_Item = inventory.Get_Item_By_Index(item_Index);

		if
			(
				inventory_Item != nullptr
				&& inventory_Item->_Item_Name == item_Name
				&& inventory_Item->_Item_Count > 0
				)
		{
			return true;
		}
	}

	return false;
}
// 10-3. 튜터 고유 아이템 확정 지급
bool Dungeon_Manager::Give_Tutor_Clear_Item(Chapter_Type chapter_Type, Inventory<Item>& inventory)
{
	Item tutor_Item =Create_Tutor_Clear_Item(chapter_Type);

	if
		(tutor_Item._Item_Name.empty() || tutor_Item._Item_Count <= 0)
	{
		cout << "튜터 고유 아이템 정보를 찾지 못했습니다." << endl;

		return false;
	}

	if
		(Has_Item_In_Inventory(inventory, tutor_Item._Item_Name))
	{
		cout << tutor_Item._Item_Name << "을(를) 이미 보유하고 있습니다." << endl;

		return true;
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 튜터님 고유 아이템 획득 ]" << endl;
	cout << "========================================" << endl;

	cout << "획득 아이템: " << tutor_Item._Item_Name << endl;

	cout << "수량: " << tutor_Item._Item_Count << "개" << endl;

	cout << "무게: " << tutor_Item._Item_Weight << endl;

	bool is_Added = inventory.Add_Or_Increase_Item(tutor_Item);

	if (is_Added == false)
	{
		cout << "고유 아이템을 인벤토리에 넣지 못했습니다." << endl;
		cout << "인벤토리를 정리한 뒤 다시 도전해주세요." << endl;
		cout << "========================================" << endl;

		return false;
	}

	cout << "최종보스방을 여는 열쇠 아이템을 획득했습니다." << endl;
	cout << "========================================" << endl;

	return true;
}
// 10-4. 최종보스방 개방 조건 확인
bool Dungeon_Manager::Check_Final_Boss_Room_Available(Inventory<Item>& inventory) const
{
	bool has_Mouse = Has_Item_In_Inventory(inventory, "손승현 튜터님의 로지텍 마우스");

	bool has_Keyboard = Has_Item_In_Inventory (inventory, "박은일 튜터님의 갈축 키포드");

	bool has_Headset = Has_Item_In_Inventory(inventory, "강신호 튜터님의 게이밍 헤드셋");

	bool has_Virtual_Cat = Has_Item_In_Inventory(inventory, "문승현 튜터님의 고양이 버츄얼");

	bool has_Glasses = Has_Item_In_Inventory
		(inventory, "김하늘 튜터님의 도수높은 안경");

	return
		has_Mouse
		&& has_Keyboard
		&& has_Headset
		&& has_Virtual_Cat
		&& has_Glasses;
}
// 10-5. 튜터 아이템 5종 보유 여부 확인
void Dungeon_Manager::Print_Tutor_Item_Status(Inventory<Item>& inventory) const
{
	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 튜터님 고유 아이템 수집 현황 ]" << endl;
	cout << "========================================" << endl;

	std::string tutor_Item_Names[5] =
	{
		"손승현 튜터님의 로지텍 마우스",
		"박은일 튜터님의 갈축 키포드",
		"강신호 튜터님의 게이밍 헤드셋",
		"문승현 튜터님의 고양이 버츄얼",
		"김하늘 튜터님의 도수높은 안경"
	};

	int obtained_Item_Count = 0;

	for
		(
			int item_Index = 0;
			item_Index < 5;
			item_Index++
			)
	{
		bool has_Item = Has_Item_In_Inventory
			(inventory, tutor_Item_Names[item_Index]);

		cout << item_Index + 1 << ". " << tutor_Item_Names[item_Index] << " - ";

		if (has_Item)
		{
			cout << "보유" << endl;
			obtained_Item_Count += 1;
		}
		else
		{
			cout << "미보유" << endl;
		}
	}

	cout << "----------------------------------------" << endl;
	cout << "수집한 고유 아이템: " << obtained_Item_Count << " / 5" << endl;

	if
		(Check_Final_Boss_Room_Available(inventory))
	{
		cout << "고유 아이템이 모두 모였습니다." << endl;
		cout << "최종보스방이 열렸습니다!" << endl;
	}
	else
	{
		cout << "최종보스방은 아직 잠겨 있습니다." << endl;
	}
	cout << "========================================" << endl;
}
// 10-6. 튜터 고유 아이템 수집 현황 출력
bool Dungeon_Manager::Run_Elite_Question(const Elite_Question& elite_Question)
{
	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 코드스니펫의 망령 문제 ]" << endl;
	cout << "========================================" << endl;
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

	cout << "----------------------------------------" << endl;
	cout << "정답 번호 입력: ";

	int player_Answer = 0;

	cin >> player_Answer;

	if
		(
			player_Answer
			== elite_Question.correct_Answer
			)
	{
		cout << endl;
		cout << "정답입니다!" << endl;
		cout << "코드스니펫의 망령을 물리쳤습니다." << endl;

		return true;
	}

	cout << endl;
	cout << "오답입니다." << endl;

	cout << "정답은 " << elite_Question.correct_Answer << "번입니다." << endl;

	cout << "코드스니펫의 망령이 도망갔습니다." << endl;

	return false;
}
