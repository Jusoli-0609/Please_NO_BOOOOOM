#include "DungeonManager.h"

#include "Battle_Elite_Skill.h"
#include "Battle_System.h"

#include "Tutor_Engine.h"
#include "Tutor_Glasses.h"
#include "Tutor_Headset.h"
#include "Tutor_Keyboard.h"
#include "Tutor_Mouse.h"
#include "Console_Manager.h"

#include "Sound_Manager.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

using namespace std;

namespace
{
	constexpr int BASE_TUTOR_REQUIRED_SCORE = 500;
	constexpr double CHAPTER_SCORE_MULTIPLIER = 1.3;
	constexpr int NORMAL_MONSTER_TYPE_COUNT = 3;
	constexpr int ELITE_APPEARANCE_RATE = 20;
	constexpr int ELITE_GIMMICK_HP_PENALTY =20;
	constexpr int TUTOR_GIMMICK_SCORE_PENALTY =50;
	constexpr int MINIMUM_BATTLE_HP =1;
}
namespace
{
	void Print_Side_By_Side_Blocks(const std::vector<std::string>& left_Block, const std::vector<std::string>& right_Block,int gap = 8)
	{
		size_t left_Width = 0;

		for (const std::string& line : left_Block)
		{
			if (line.size() > left_Width)
			{
				left_Width = line.size();
			}
		}

		size_t max_Lines =std::max(left_Block.size(), right_Block.size());

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

			cout << right_Line << endl;
		}
	}

	std::vector<std::string> Get_Final_Manager_01_Intro_Block()
	{
		return
		{
			".-------------------------------------------.",
			"| FINAL_MANAGER_01 :: CODE REVIEW MODE      |",
			"| SYSTEM STATUS : STRICT / ONLINE           |",
			"'-------------------------------------------'",
			"              .-----------.",
			"             /|  o   o   |\\",
			"            / |    ^     | \\",
			"           |  |  [OK?]   |  |",
			"           |  |          |  |",
			"            \\ |__________| /",
			"             \\____||_____/ ",
			"                  ||       ",
			"             ____/||\\____  ",
			"            / [ CODE REVIEW ] \\",
			"           /__ERR__WARN__PASS_\\"
		};
	}

	std::vector<std::string> Get_Final_Manager_02_Intro_Block()
	{
		return
		{
			".-------------------------------------------.",
			"| FINAL_MANAGER_02 :: LAST VALIDATION MODE  |",
			"| DEPLOYMENT GATE : LOCKED                  |",
			"'-------------------------------------------'",
			"              .-----------.",
			"             /|  o   o   |\\",
			"            / |    ^     | \\",
			"           |  |  FINAL   |  |",
			"           |  |          |  |",
			"            \\ |__________| /",
			"             \\____||_____/ ",
			"                  ||       ",
			"             ____/||\\____  ",
			"            / [ BUILD ][ TEST ][ RUN ] \\",
			"           /__FAIL__WARN__PASS_________\\"
		};
	}

	void Print_Final_Boss_Duo_Intro_Art()
	{
		Print_Side_By_Side_Blocks( Get_Final_Manager_01_Intro_Block(), Get_Final_Manager_02_Intro_Block(), 10);
	}

	void Print_Final_Boss_Duo_Intro_Dialogue(const Monster& first_Boss, const Monster& second_Boss)
	{
		cout << endl;
		cout << "==================================================" << endl;
		cout << "[ 미지의 공간 ]" << endl;
		cout << "==================================================" << endl;
		cout << "모든 튜터님의 시험 기록이 동시에 반응하기 시작했다." << endl;
		cout << "입구를 막고 있던 코드들이 흩어졌다." << endl;
		cout << "스포트라이트가 켜졌다." << endl;
		cout << endl;
		cout << first_Boss.getName() << "와 " << second_Boss.getName() << "가 동시에 모습을 드러냈다." << endl;
		cout << "==================================================" << endl;

		Print_Final_Boss_Duo_Intro_Art();

		cout << endl;
		cout << "==================================================" << endl;
		cout << "[ 최종 코드 검증 시작 ]" << endl;
		cout << "==================================================" << endl;
		cout << "최종보스는 기본적으로 일반 공격을 사용한다." << endl;
		cout << "일정 확률로 코드 검증 기믹이 발동한다." << endl;
		cout << "객관식 정답 시 두 보스에게 광역 피해가 들어간다." << endl;
		cout << "주관식 정답 시 두 보스 중 하나를 선택해 그로기 공격을 사용한다." << endl;
		cout << "문제 오답 시 살아 있는 보스들의 공격이 2배로 강화된다." << endl;
		cout << "==================================================" << endl;
	}
}


//=============================================================================
// 1. 던전 생성 및 메뉴 실행 파트
//=============================================================================

Dungeon_Manager::Dungeon_Manager()
	: _current_Chapter(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_is_All_Chapter_Cleared(false),
	_is_Game_Cleared(false),
	_current_Chapter_Score(0),
	_has_Elite_Appeared_In_Current_Chapter(false)
{
}

void Dungeon_Manager::Open_Dungeon(Player* player,Inventory<Item>& inventory, Inventory_For_Equipments_Only& equipment_Inventory, const Currently_Equipped_Equipments&equipped_Equipments, Console_Manager& console)
{
	if (player == nullptr)
	{
		cout << "조원의 정보를 찾을 수 없다" << endl;
		return;
	}

	if (_is_Game_Cleared)
	{
		cout << endl;
		cout << "이미 매니저님께 인정을 받았다." << endl;
		cout << "모든 내일배움캠프 과정을 수료한 상태다." << endl;

		return;
	}

	if (_is_All_Chapter_Cleared)
	{
		cout << endl;
		cout << "========================================" << endl;
		cout << "	[ 최종 과정 선택 ]" << endl;
		cout << "========================================" << endl;

		cout << "모든 튜터님에게 인정받았다." << endl;

		Print_Tutor_Equipment_Status(equipment_Inventory, equipped_Equipments);

		bool is_Final_Boss_Room_Available = Check_Final_Boss_Room_Available(equipment_Inventory,equipped_Equipments);

		int final_Boss_Choice = -1;

		cout << endl;

		if (is_Final_Boss_Room_Available)
		{
			cout << "1. 미지의 공간으로 이동" << endl;
		}
		else
		{
			cout << "1. 미지의 공간으로 이동 [입장 불가]" << endl;
		}

		cout << "2. 오류 코드 해결 기록 확인" << endl;
		cout << "3. 코드 던전 입장" << endl;
		cout << "0. 메인 메뉴 복귀" << endl;
		cout << "선택: ";

		cin >> final_Boss_Choice;

		switch (final_Boss_Choice)
		{
		case 1:
		{
			if (!is_Final_Boss_Room_Available)
			{
				cout << endl;
				cout << "코드들이 입구를 막고있다. " << endl;

				Print_Tutor_Equipment_Status(equipment_Inventory, equipped_Equipments);

				break;
			}

			Run_Final_Boss_Room
			(player, inventory, equipment_Inventory, equipped_Equipments);

			break;
		}

		case 2:
		{
			Print_Total_Monster_Kill_Log();
			console.Wait_For_Key("아무 키나 누르면 돌아갑니다...");

			break;
		}

		case 3:
		{
			Select_Chapter_And_Enter(player, inventory, console);

			break;
		}

		case 0:
		{
			cout << "메인 메뉴로 돌아간다." << endl;

			break;
		}

		default:
		{
			cout << "잘못된 선택." << endl;

			break;
		}
		}

		return;
	}

	Print_Current_Chapter();

	if (Check_Tutor_Challenge_Available())
	{
		cout << "튜터님의 시험을 칠 수 있다!" << endl;
	}
	else
	{
		cout << "튜터님 시험까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았다." << endl;
	}

	int dungeon_Choice = -1;

	cout << endl;
	cout << "1. 현재 챕터 입장" << endl;
	cout << "2. 코드 해결 및 튜터님의 시험 기록" << endl;
	cout << "3. 튜터님 시험보기" << endl;
	cout << "0. 메인 메뉴" << endl;
	cout << "선택: ";

	cin >> dungeon_Choice;

	switch (dungeon_Choice)
	{
	case 1:
		Run_Current_Chapter(player, inventory, console);   // console 추가
		break;
	case 2:
		Print_Total_Monster_Kill_Log();
		console.Wait_For_Key("아무 키나 누르면 돌아갑니다...");
		break;
	case 3:
		Run_Tutor_Challenge(player, equipment_Inventory, equipped_Equipments);
		break;
	case 0:
		cout << "메인 메뉴로 돌아간다." << endl;
		break;
	default:
		cout << "잘못된 선택." << endl;
		break;
	}
}

//=============================================================================
// 2. 챕터 상태 조회 및 출력 파트
//=============================================================================

bool Dungeon_Manager::Check_All_Chapter_Cleared() const
{
	return _is_All_Chapter_Cleared;
}

bool Dungeon_Manager::Check_Game_Cleared() const
{
	return _is_Game_Cleared;
}

int Dungeon_Manager::Get_Current_Chapter_Score() const
{
	return _current_Chapter_Score;
}

void Dungeon_Manager::Print_Current_Chapter() const
{
	cout << endl;
	cout << "╔════════════════════════════════════════════════════╗\n";
	cout << "		현재 입장 가능한 코드 던전" << endl;
	cout <<		Get_Chapter_Name(_current_Chapter) << endl;
	cout << "╚════════════════════════════════════════════════════╝\n";
}

void Dungeon_Manager::Select_Chapter_And_Enter(Player* player, Inventory<Item>& inventory, Console_Manager& console)
{
	if (player == nullptr)
	{
		cout << "조원의 정보를 찾을 수 없다." << endl;

		return;
	}

	int chapter_Choice = -1;

	cout << endl;
	cout << "╔════════════════════════════════════════════════════╗\n";
	cout << "		[ 코드 던전 선택 ]" << endl;
	cout << "╚════════════════════════════════════════════════════╝\n";

	cout << "	1. 챕터 1 - 변수·조건문 숲" << endl;
	cout << "	2. 챕터 2 - 배열·반복문 바다" << endl;
	cout << "	3. 챕터 3 - 함수 유적" << endl;
	cout << "	4. 챕터 4 - 포인터·메모리 묘지" << endl;
	cout << "	5. 챕터 5 - 객체지향·STL 공장" << endl;
	cout << "	0. 이전 메뉴로 돌아가기" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	선택: ";

	cin >> chapter_Choice;

	Chapter_Type selected_Chapter = Chapter_Type::VARIABLE_CONDITION_FOREST;

	switch (chapter_Choice)
	{
	case 1:
	{
		selected_Chapter = Chapter_Type::VARIABLE_CONDITION_FOREST;

		break;
	}

	case 2:
	{
		selected_Chapter = Chapter_Type::ARRAY_LOOP_OCEAN;

		break;
	}

	case 3:
	{
		selected_Chapter = Chapter_Type::FUNCTION_RUINS;

		break;
	}

	case 4:
	{
		selected_Chapter = Chapter_Type::POINTER_MEMORY_GRAVEYARD;

		break;
	}

	case 5:
	{
		selected_Chapter = Chapter_Type::OBJECT_STL_FACTORY;

		break;
	}

	case 0:
	{
		cout << "이전 메뉴로 돌아간다." << endl;

		return;
	}

	default:
	{
		cout << "잘못된 코드 던전 선택." << endl;

		return;
	}
	}

	_current_Chapter = selected_Chapter;
	_current_Chapter_Score = 0;
	_has_Elite_Appeared_In_Current_Chapter = false;

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "		[ 선택한 코드 던전으로 이동 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << Get_Chapter_Name(_current_Chapter) << "진입!" << endl;
	cout << "오류 코드 탐색 시작!" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	Run_Current_Chapter(player, inventory, console);
}

string Dungeon_Manager::Get_Chapter_Name(Chapter_Type chapter_Type) const
{
	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
		return "챕터 1 - 변수·조건문 숲";
	case Chapter_Type::ARRAY_LOOP_OCEAN:
		return "챕터 2 - 배열·반복문 바다";
	case Chapter_Type::FUNCTION_RUINS:
		return "챕터 3 - 함수 유적";
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
		return "챕터 4 - 포인터·메모리 묘지";
	case Chapter_Type::OBJECT_STL_FACTORY:
		return "챕터 5 - 객체지향·STL 공장";
	default:
		return "모든 코드 던전 오류 해결";
	}
}

//=============================================================================
// 3. 현재 챕터 진행 파트
//=============================================================================

void Dungeon_Manager::Run_Current_Chapter(Player* player, Inventory<Item>& inventory, Console_Manager& console)
{
	if (player == nullptr) return;

	cout << endl;
	cout << Get_Chapter_Name(_current_Chapter) << "에 입장." << endl;

	bool is_Elite_Appeared = Check_Elite_Monster_Appearance();

	if (is_Elite_Appeared)
	{
		Monster elite_Monster;
		elite_Monster.Initialize_Elite_Monster(_current_Chapter);

		elite_Monster.Print_Ascii_Art();

		bool is_Correct = Run_Elite_Quiz(player, elite_Monster);

		if (is_Correct)
		{
			elite_Monster.Generate_Drop_Reward();
			player->Gain_Exp(elite_Monster.getExpReward());

			cout << endl;
			cout << "╠════════════════════════════════════════════════════╣\n";
			cout << "		[ 코드 스니펫을 복사했습니다. ]" << endl;
			cout << "╠════════════════════════════════════════════════════╣\n";
			cout << "획득 경험치: " << elite_Monster.getExpReward() << endl;
			cout << "획득 점수: " << elite_Monster.getScoreReward() << endl;

			Give_Drop_Items_To_Inventory(elite_Monster, inventory);

			cout << "획득 훈련장려금: " << elite_Monster.getGoldReward() << "원" << endl;
			cout << "╠════════════════════════════════════════════════════╣\n";

			Record_Monster_Kill(elite_Monster);
		}
		else
		{
			Apply_Elite_Gimmick_Failure_Penalty(player);

			cout << endl;
			cout << "코드 스니펫 복사를 실패했습니다." << endl;
		}
		return;
	}

	Monster_Type random_Monster_Type = Get_Random_Normal_Monster();
	Monster monster(random_Monster_Type);

	monster.Apply_Player_Level_Scaling(player->getLevel());
	monster.Print_Ascii_Art();

	Battle(player, monster, inventory, console);

	if (monster.getHP() > 0)
	{
		cout << endl;
		cout << "코드를 해결하지 못했습니다." << endl;
		return;
	}

	Record_Monster_Kill(monster);

	if (Check_Tutor_Challenge_Available())
	{
		cout << "튜터님 시험 조건을 달성했다!" << endl;
	}
	else
	{
		cout << "튜터님 시험까지 " << Get_Required_Tutor_Score() - _current_Chapter_Score << "점 남았다." << endl;
	}

	cout << "╠════════════════════════════════════════════════════╣\n";
}

//=============================================================================
// 4. 일반 몬스터 선택 파트
//=============================================================================

void Dungeon_Manager::Get_Current_Chapter_Monsters(Monster_Type monster_Types[]) const
{
	switch (_current_Chapter)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
		monster_Types[0] = Monster_Type::INT_SLIME;
		monster_Types[1] = Monster_Type::BOOL_MUSHROOM;
		monster_Types[2] = Monster_Type::IF_GOBLIN;
		break;
	case Chapter_Type::ARRAY_LOOP_OCEAN:
		monster_Types[0] = Monster_Type::ARRAY_JELLYFISH;
		monster_Types[1] = Monster_Type::FOR_SHARK;
		monster_Types[2] = Monster_Type::WHILE_WHALE;
		break;
	case Chapter_Type::FUNCTION_RUINS:
		monster_Types[0] = Monster_Type::PARAMETER_GIANT_FLY;
		monster_Types[1] = Monster_Type::RETURN_GARGOYLE;
		monster_Types[2] = Monster_Type::FUNCTION_MAGE;
		break;
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
		monster_Types[0] = Monster_Type::POINTER_GHOST;
		monster_Types[1] = Monster_Type::NULL_BANSHEE;
		monster_Types[2] = Monster_Type::MEMORY_REAPER;
		break;
	case Chapter_Type::OBJECT_STL_FACTORY:
		monster_Types[0] = Monster_Type::CLASS_MACHINE_DOLL;
		monster_Types[1] = Monster_Type::INHERITANCE_CHIMERA;
		monster_Types[2] = Monster_Type::VECTOR_DRONE;
		break;
	default:
		monster_Types[0] = Monster_Type::INT_SLIME;
		monster_Types[1] = Monster_Type::BOOL_MUSHROOM;
		monster_Types[2] = Monster_Type::IF_GOBLIN;
		break;
	}
}

Monster_Type Dungeon_Manager::Get_Random_Normal_Monster() const
{
	Monster_Type monster_Types[NORMAL_MONSTER_TYPE_COUNT];
	Get_Current_Chapter_Monsters(monster_Types);

	int random_Index = rand() % NORMAL_MONSTER_TYPE_COUNT;
	return monster_Types[random_Index];
}

//=============================================================================
// 5. 정예 몬스터 파트
//=============================================================================

bool Dungeon_Manager::Check_Elite_Monster_Appearance()
{
	if (_has_Elite_Appeared_In_Current_Chapter)
	{
		return false;
	}

	int appearance_Roll = rand() % 100 + 1;

	bool is_Elite_Appeared = appearance_Roll <= ELITE_APPEARANCE_RATE;

	if (is_Elite_Appeared)
	{
		_has_Elite_Appeared_In_Current_Chapter = true;
	}

	return is_Elite_Appeared;
}

bool Dungeon_Manager::Run_Elite_Quiz(Player* player,Monster& elite_Monster)
{
	if (player == nullptr)
	{
		return false;
	}

	return Ask_Random_Elite_Question(player,elite_Monster);
}

//=============================================================================
// 6. 튜터 문제 및 대사 파트
//=============================================================================

void Dungeon_Manager::Run_Tutor_Challenge(Player* player, Inventory_For_Equipments_Only& equipment_Inventory, const Currently_Equipped_Equipments& equipped_Equipments)
{
	if (player == nullptr)
	{
		return;
	}

	if (!Check_Tutor_Challenge_Available())
	{
		int required_Score = Get_Required_Tutor_Score();
		int remaining_Score = required_Score - _current_Chapter_Score;

		cout << endl;
		cout << "╔════════════════════════════════════════════════════╗\n";
		cout << "	튜터님의 시험 조건을 충족하지 못했다." << endl;
		cout << "	현재 점수: " << _current_Chapter_Score << " / " << required_Score << endl;
		cout << "	필요한 추가 점수: " << remaining_Score<< endl;
		cout << "╚════════════════════════════════════════════════════╝\n";

		return;
	}

	Sound_Manager::Get_Instance().Play_BGM(BGM_Type::Boss);

	Monster tutor_Monster;

	tutor_Monster.Initialize_Tutor_Monster(_current_Chapter);
	tutor_Monster.Print_Ascii_Art();

	bool is_Cleared = Run_Tutor_Code_Challenge(player,tutor_Monster);

	if (!is_Cleared)
	{
		Apply_Tutor_Gimmick_Failure_Penalty();

		cout << endl;
		cout << "다시 점수를 채워 튜터님 시험에 다시 도전하세요."<< endl;

		return;
	}

	bool is_Tutor_Equipment_Given = Give_Tutor_Clear_Equipment(_current_Chapter, equipment_Inventory, equipped_Equipments);

	if (!is_Tutor_Equipment_Given)
	{
		cout << endl;
		cout << "튜터 장비를 받지 못했지만 " << "시험 클리어 기록은 정상적으로 저장해줘." << endl;
	}

	player->Gain_Exp(tutor_Monster.getExpReward());

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "[ " << tutor_Monster.getName() << " 클리어 보상 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	획득 경험치: " << tutor_Monster.getExpReward() << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	Record_Monster_Kill(tutor_Monster);

	Clear_Current_Chapter();
}

bool Dungeon_Manager::Run_Tutor_Code_Challenge(Player* player, Monster& tutor_Monster)
{
	if (player == nullptr)
	{
		return false;
	}
	return Tutor_Test(player,tutor_Monster);
}

//=============================================================================
// 7. 기믹 실패 패널티 처리 파트
//=============================================================================

// 7-1 정예 몬스터 기믹 실패 시 HP 감소
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

	player->Set_Hp(changed_HP);

	int decreased_HP = previous_HP - player->Get_Hp();

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	[ 코드 스니펫을 복사하지 못했습니다. ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	플레이어의 HP가 " << decreased_HP << " 감소했습니다." << endl;
	cout << "	현재 HP: " << previous_HP << " -> " << player->Get_Hp() << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
}
// 7-2 튜터 기믹 실패 시 챕터 점수 감소
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
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	[ 튜터님의 잔소리 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	현재 챕터 점수가 " << decreased_Score << " 감소했습니다." << endl;
	cout << "	현재 챕터 점수: " << previous_Score << " -> " << _current_Chapter_Score << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
}

//=============================================================================
// 8. 처치 기록 및 보상 파트
//=============================================================================

void Dungeon_Manager::Record_Monster_Kill(const Monster& monster)
{
	Monster_Type monster_Type = monster.getMonsterType();
	Monster_Kill_Record& kill_Record = _monster_Kill_Log[_current_Chapter][monster_Type];

	if (kill_Record.monster_Name.empty())
	{
		kill_Record.monster_Name = monster.getName();
	}

	kill_Record.monster_Grade = monster.getMonsterGrade();
	kill_Record.kill_Count += 1;
	kill_Record.earned_Score += monster.getScoreReward();

	Monster_Kill_Count += 1;

	if (monster.getMonsterGrade() != Monster_Grade::TUTOR)
	{
		Add_Chapter_Score(monster.getScoreReward());
	}
}

void Dungeon_Manager::Print_Total_Monster_Kill_Log() const
{
	map
		<
		Monster_Type,
		Monster_Kill_Record
		> normal_Elite_Kill_Log;

	map
		<
		Monster_Type,
		Monster_Kill_Record
		> tutor_Kill_Log;

	for(const auto& chapter_Record : _monster_Kill_Log)
	{
		for
			(const auto& monster_Record : chapter_Record.second)
		{
			Monster_Type monster_Type = monster_Record.first;
			const Monster_Kill_Record& kill_Record = monster_Record.second;

			if
				(kill_Record.monster_Grade == Monster_Grade::NORMAL || kill_Record.monster_Grade == Monster_Grade::ELITE)
			{
				Monster_Kill_Record& total_Record = normal_Elite_Kill_Log[monster_Type];

				total_Record.monster_Name = kill_Record.monster_Name;
				total_Record.monster_Grade = kill_Record.monster_Grade;
				total_Record.kill_Count += kill_Record.kill_Count;
				total_Record.earned_Score += kill_Record.earned_Score;
			}
			else if
				(kill_Record.monster_Grade == Monster_Grade::TUTOR)
			{
				Monster_Kill_Record& total_Record = tutor_Kill_Log[monster_Type];

				total_Record.monster_Name = kill_Record.monster_Name;
				total_Record.monster_Grade = kill_Record.monster_Grade;
				total_Record.kill_Count += kill_Record.kill_Count;
				total_Record.earned_Score += kill_Record.earned_Score;
			}
		}
	}

	int normal_Elite_Total_Count = 0;
	int normal_Elite_Total_Score = 0;
	int tutor_Total_Count = 0;

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	[ 전체 코드 해결 기록 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << endl;
	cout << "	1. 아직 해결한 오류 코드가 없다." << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	if (normal_Elite_Kill_Log.empty())
	{
		cout << "아직 해결한 오류 코드가 없다." << endl;
	}
	else
	{
		for
			(const auto& monster_Record: normal_Elite_Kill_Log)
		{
			const Monster_Kill_Record& kill_Record = monster_Record.second;

			string monster_Grade_Name;

			if
				(kill_Record.monster_Grade == Monster_Grade::ELITE)
			{
				monster_Grade_Name = "정예";
			}
			else
			{
				monster_Grade_Name = "일반";
			}

			cout << "[" << monster_Grade_Name << "] " << kill_Record.monster_Name << endl;
			cout << "해결 횟수: " << kill_Record.kill_Count << "회" << endl;
			cout << "획득 점수: " << kill_Record.earned_Score << endl;
			cout << "╠════════════════════════════════════════════════════╣\n";

			normal_Elite_Total_Count += kill_Record.kill_Count;
			normal_Elite_Total_Score += kill_Record.earned_Score;
		}

		cout << "오류 코드 해결 수: " << normal_Elite_Total_Count << "회" << endl;
		cout << "종합 점수: " << normal_Elite_Total_Score << endl;
	}

	cout << endl;
	cout << "	2. 튜터" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	if (tutor_Kill_Log.empty())
	{
		cout << "인정한 튜터님이 없다." << endl;
	}
	else
	{
		for(const auto& monster_Record : tutor_Kill_Log)
		{
			const Monster_Kill_Record& kill_Record = monster_Record.second;

			cout << kill_Record.monster_Name << endl;
			cout << "	인정받은 횟수: " << kill_Record.kill_Count << "회" << endl;
			cout << "╠════════════════════════════════════════════════════╣\n";

			tutor_Total_Count += kill_Record.kill_Count;
		}

		cout << "	튜터님께 인정받은 횟수: " << tutor_Total_Count << "회" << endl;
	}
	cout << "╠════════════════════════════════════════════════════╣\n";
}

void Dungeon_Manager::Give_Drop_Items_To_Inventory(const Monster& monster, Inventory<Item>& inventory)
{
	const std::vector<Item>& drop_Items = monster.getDropItems();

	for (const Item& drop_Item : drop_Items)
	{
		bool is_Added = inventory.Add_Or_Increase_Item(drop_Item);
		if (!is_Added)
		{
			cout << drop_Item._Item_Name << " 획득을 취소했습니다." << endl;
			continue;
		}
		drop_Item.Print_Info();

		cout << endl;
	}
}

//=============================================================================
// 9. 챕터 점수 및 이동 파트
//=============================================================================

void Dungeon_Manager::Add_Chapter_Score(int score_Reward)
{
	if (score_Reward <= 0) return;

	int max_Chapter_Score = Get_Required_Tutor_Score();

	if (_current_Chapter_Score >= max_Chapter_Score)
	{
		_current_Chapter_Score = max_Chapter_Score;
		cout << "이정도면 튜터님께 시험을 치러 가도 되겠다." << endl;
		return;
	}

	int previous_Score = _current_Chapter_Score;
	_current_Chapter_Score += score_Reward;

	if (_current_Chapter_Score > max_Chapter_Score)
	{
		_current_Chapter_Score = max_Chapter_Score;
	}

	int added_Score = _current_Chapter_Score - previous_Score;

	cout << "챕터 점수 +" << added_Score << endl;
	cout << "현재 챕터 점수: " << _current_Chapter_Score << " / " << max_Chapter_Score << endl;

	if (_current_Chapter_Score >= max_Chapter_Score)
	{
		cout << "튜터님 시험 조건을 달성했다!" << endl;
	}
}

int Dungeon_Manager::Get_Required_Tutor_Score() const
{
	int chapter_Number = 1;

	switch (_current_Chapter)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST: chapter_Number = 1; break;
	case Chapter_Type::ARRAY_LOOP_OCEAN: chapter_Number = 2; break;
	case Chapter_Type::FUNCTION_RUINS: chapter_Number = 3; break;
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD: chapter_Number = 4; break;
	case Chapter_Type::OBJECT_STL_FACTORY: chapter_Number = 5; break;
	default: return 0;
	}

	double required_Score = BASE_TUTOR_REQUIRED_SCORE;

	for (int chapter_Index = 1; chapter_Index < chapter_Number; chapter_Index++)
	{
		required_Score *= CHAPTER_SCORE_MULTIPLIER;
	}

	return static_cast<int>(required_Score + 0.5);
}

bool Dungeon_Manager::Check_Tutor_Challenge_Available() const
{
	return _current_Chapter_Score >= Get_Required_Tutor_Score();
}

void Dungeon_Manager::Clear_Current_Chapter()
{
	cout << endl << Get_Chapter_Name(_current_Chapter) << "을(를) 해결했다!" << endl;

	Move_Next_Chapter();
	_current_Chapter_Score = 0;
	_has_Elite_Appeared_In_Current_Chapter = false;

	if (_is_All_Chapter_Cleared)
	{
		cout << "여기 있던 오류 코드를 해결했다!" << endl;
	}
	else
	{
		cout << Get_Chapter_Name(_current_Chapter) << "이(가) 열렸습니다!" << endl;
	}
}

void Dungeon_Manager::Move_Next_Chapter()
{
	switch (_current_Chapter)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
		_current_Chapter = Chapter_Type::ARRAY_LOOP_OCEAN;
		break;
	case Chapter_Type::ARRAY_LOOP_OCEAN:
		_current_Chapter = Chapter_Type::FUNCTION_RUINS;
		break;
	case Chapter_Type::FUNCTION_RUINS:
		_current_Chapter = Chapter_Type::POINTER_MEMORY_GRAVEYARD;
		break;
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
		_current_Chapter = Chapter_Type::OBJECT_STL_FACTORY;
		break;
	case Chapter_Type::OBJECT_STL_FACTORY:
		_current_Chapter = Chapter_Type::ALL_CHAPTER_CLEARED;
		_is_All_Chapter_Cleared = true;
		break;
	default:
		_is_All_Chapter_Cleared = true;
		break;
	}
}

//=============================================================================
// 10. 튜터 고유 아이템 파트
//=============================================================================

Equipment Dungeon_Manager::Create_Tutor_Clear_Equipment(Chapter_Type chapter_Type) const
{
	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		return Tutor_Mouse();
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		return Tutor_Keyboard();
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		return Tutor_Headset();
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		return Tutor_Engine();
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		return Tutor_Glasses();
	}

	default:
	{
		return Equipment();
	}
	}
}

bool Dungeon_Manager::Has_Tutor_Equipment(const Inventory_For_Equipments_Only&equipment_Inventory, const Currently_Equipped_Equipments&equipped_Equipments, const string& equipment_Name) const
{
	if(equipment_Inventory.Has_Equipment_By_Name(equipment_Name))
	{
		return true;
	}

	if(equipped_Equipments.Has_Equipment_By_Name(equipment_Name))
	{
		return true;
	}

	return false;
}

bool Dungeon_Manager::Give_Tutor_Clear_Equipment(Chapter_Type chapter_Type, Inventory_For_Equipments_Only& equipment_Inventory, const Currently_Equipped_Equipments& equipped_Equipments)
{
	Equipment tutor_Equipment = Create_Tutor_Clear_Equipment(chapter_Type);

	if(tutor_Equipment.Get_Equipment_Type() == Equipment_Type::Empty)
	{
		cout << "튜터 전용 장비 정보를 찾지 못했다."<< endl;

		return false;
	}

	if
		(Has_Tutor_Equipment(equipment_Inventory, equipped_Equipments, tutor_Equipment.Get_Equipment_Name()))
	{
		cout << tutor_Equipment.Get_Equipment_Name() << "을(를) 이미 보유하고 있다." << endl;

		return true;
	}

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	[ 튜터님이 선물을 주셨다. ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	bool is_Added = equipment_Inventory.Add_Equipment(tutor_Equipment);

	if (!is_Added)
	{
		cout << "장비 인벤토리에 공간이 없어 " << "튜터 장비를 받지 못했다." << endl;

		return false;
	}

	tutor_Equipment.Print_Equipment_Info();

	cout << "╠════════════════════════════════════════════════════╣\n";

	return true;
}

bool Dungeon_Manager::Check_Final_Boss_Room_Available(const Inventory_For_Equipments_Only& equipment_Inventory, const Currently_Equipped_Equipments& equipped_Equipments) const
{
	(void)equipment_Inventory;
	(void)equipped_Equipments;

	return _is_All_Chapter_Cleared;
}

void Dungeon_Manager::Print_Tutor_Equipment_Status(const Inventory_For_Equipments_Only& equipment_Inventory, const Currently_Equipped_Equipments& equipped_Equipments) const
{
	const Chapter_Type tutor_Chapters[5] =
	{
		Chapter_Type::VARIABLE_CONDITION_FOREST,
		Chapter_Type::ARRAY_LOOP_OCEAN,
		Chapter_Type::FUNCTION_RUINS,
		Chapter_Type::POINTER_MEMORY_GRAVEYARD,
		Chapter_Type::OBJECT_STL_FACTORY
	};

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	[ 튜터님께 받은 선물 현황 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	int obtained_Count = 0;

	for (int chapter_Index = 0;
		chapter_Index < 5;
		chapter_Index++)
	{
		Equipment tutor_Equipment = Create_Tutor_Clear_Equipment(tutor_Chapters[chapter_Index]);

		bool has_Equipment = Has_Tutor_Equipment(equipment_Inventory, equipped_Equipments, tutor_Equipment.Get_Equipment_Name());

		cout << chapter_Index + 1 << ". " << tutor_Equipment.Get_Equipment_Name() << " - " << (has_Equipment ? "보유" : "미보유") << endl;

		if (has_Equipment)
		{
			obtained_Count++;
		}
	}

	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "	튜터님께 받은 선물 : " << obtained_Count << " / 5" << endl;

	if (Check_Final_Boss_Room_Available(equipment_Inventory, equipped_Equipments))
	{
		cout << " " << "최종 과정에 입장할 수 있다." << endl;
	}
	else
	{
		cout << "	아직 모든 오류 코드를 해결하지 못했다." << endl;
	}

	cout << "╠════════════════════════════════════════════════════╣\n";
}

//=============================================================================
// 10. 최종보스방 파트
//=============================================================================

void Dungeon_Manager::Run_Final_Boss_Room(Player* player, Inventory<Item>& inventory, const Inventory_For_Equipments_Only& equipment_Inventory, const Currently_Equipped_Equipments& equipped_Equipments)
{
	if (player == nullptr)
	{
		cout << "조원의 정보를 찾을 수 없다." << endl;
		return;
	}

	if (_is_Game_Cleared)
	{
		cout << "이미 매니저님들의 최종 시험을 통과했다." << endl;
		return;
	}

	if (!_is_All_Chapter_Cleared)
	{
		cout << "모든 내일배움캠프 과정을 수료하지 못했다." << endl;
		return;
	}

	if (!Check_Final_Boss_Room_Available(equipment_Inventory, equipped_Equipments))
	{
		cout << endl;
		cout << "╠════════════════════════════════════════════════════╣\n";
		cout << "		[ 미지의 공간 입장 실패 ]" << endl;
		cout << "╠════════════════════════════════════════════════════╣\n";
		cout << "아직 모든 오류 코드를 해결하지 못했다." << endl;

		Print_Tutor_Equipment_Status(equipment_Inventory, equipped_Equipments);

		cout << "╠════════════════════════════════════════════════════╣\n";

		return;
	}

	Monster kim_Dong_Hyun_Manager;
	kim_Dong_Hyun_Manager.Initialize_Final_Boss(Monster_Type::KIM_DONG_HYUN_MANAGER);

	Monster moon_Seung_Ho_Manager;
	moon_Seung_Ho_Manager.Initialize_Final_Boss(Monster_Type::MOON_SEUNG_HO_MANAGER);

	Print_Final_Boss_Duo_Intro_Dialogue(kim_Dong_Hyun_Manager, moon_Seung_Ho_Manager);

	cout << "==================================================" << endl;
	cout << "최종보스 기본 패턴: 일반 공격!" << endl;
	cout << "랜덤 코드 검증 기믹 발동!" << endl;
	cout << "객관식 정답: 전체 광역 피해!" << endl;
	cout << "주관식 정답: 대상 선택 후 그로기 공격!" << endl;
	cout << "오답: 보스 공격 2배 강화!" << endl;
	cout << "==================================================" << endl;

	bool is_Final_Boss_Cleared = Final_Boss_Duo_Battle(player, kim_Dong_Hyun_Manager, moon_Seung_Ho_Manager, inventory);

	if (!is_Final_Boss_Cleared)
	{
		cout << endl;
		cout << "==================================================" << endl;
		cout << "[ 최종 시험 실패 ]" << endl;
		cout << "==================================================" << endl;
		cout << "매니저님의 최종 시험을 통과하지 못했다." << endl;
		cout << "재정비소에서 상태를 정비한 뒤 다시 도전할 수 있다." << endl;
		cout << "==================================================" << endl;
		return;
	}

	_is_Game_Cleared = true;

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "		[ 최종 시험 통과 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << kim_Dong_Hyun_Manager.getName() << "와 " << moon_Seung_Ho_Manager.getName() << "의 시험을 모두 통과했다." << endl;
	cout << "검증실을 뒤덮고 있던 오류 메시지가 사라지기 시작했다." << endl;
	cout << "마지막 모니터에 새로운 문장이 출력됐다." << endl;
	cout << endl;
	cout << "\"최종 시험 통과!!!\"" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";

	Run_Ending(player);
}

void Dungeon_Manager::Run_Ending(const Player* player) const
{
	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "		[ 매니저님들의 인정 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "김동현 매니저님과 문승호 매니저님의 " << "최종 시험을 모두 통과했습니다." << endl;
	cout << endl;

	if (player != nullptr)
	{
		cout << "드디어 내일배움캠프를 수료했다." << endl;
	}

	cout << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << "              눈떠보니 코드마스터" << endl;
	cout << "                   GAME CLEAR" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
	cout << endl;
	cout << "게임을 플레이해 주셔서 감사합니다." << endl;
}
