#include "DungeonManager.h"
#include "Battle_System.h"
#include "Battle_Elite_Skill.h"

#include <cstdlib>
#include <iostream>
#include <limits>

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

//=============================================================================
// 1. 던전 생성 및 메뉴 실행 파트
//=============================================================================

Dungeon_Manager::Dungeon_Manager()
	: _current_Chapter(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_is_All_Chapter_Cleared(false),
	_current_Chapter_Score(0)
{
}

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

		if(Check_Final_Boss_Room_Available(inventory) == false)
		{
			return;
		}

		int final_Boss_Choice = -1;

		cout << endl;
		cout << "1. 최종보스방 입장" << endl;
		cout << "0. 메인 메뉴로 돌아가기" << endl;
		cout << "선택: ";

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
			cout
				<< "메인 메뉴로 돌아갑니다." << endl;

			break;
		}

		default:
		{
			cout
				<< "잘못된 선택입니다." << endl;

			break;
		}
		}

		return;
	}

	Print_Current_Chapter();

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
		Run_Current_Chapter(player, inventory);
		break;
	case 2:
		Print_Current_Chapter_Kill_Log();
		break;
	case 3:
		Run_Tutor_Challenge(player, inventory);
		break;
	case 0:
		cout << "메인 메뉴로 돌아갑니다." << endl;
		break;
	default:
		cout << "잘못된 선택입니다." << endl;
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

int Dungeon_Manager::Get_Current_Chapter_Score() const
{
	return _current_Chapter_Score;
}

void Dungeon_Manager::Print_Current_Chapter() const
{
	cout << endl;
	cout << "========================================" << endl;
	cout << "현재 입장 가능한 던전" << endl;
	cout << Get_Chapter_Name(_current_Chapter) << endl;
	cout << "========================================" << endl;
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
		return "모든 일반 챕터 클리어";
	}
}

//=============================================================================
// 3. 현재 챕터 진행 파트
//=============================================================================

void Dungeon_Manager::Run_Current_Chapter(Player* player, Inventory<Item>& inventory)
{
	if (player == nullptr) return; // NULL 포인터 방지

	cout << endl;
	cout << Get_Chapter_Name(_current_Chapter) << "에 입장했습니다." << endl;

	bool is_Elite_Appeared = Check_Elite_Monster_Appearance();

	if (is_Elite_Appeared)
	{
		Monster elite_Monster;
		elite_Monster.Initialize_Elite_Monster(_current_Chapter);

		cout << endl;
		cout << "========================================" << endl;
		cout << "[ 정예 몬스터 등장! ]" << endl;
		cout << elite_Monster.getName() << "이(가) 나타났습니다!" << endl;
		cout << "========================================" << endl;

		bool is_Correct = Run_Elite_Quiz(player, elite_Monster);

		if (is_Correct)
		{
			elite_Monster.Generate_Drop_Reward();
			player->Gain_Exp(elite_Monster.getExpReward());

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

			Record_Monster_Kill(elite_Monster);
		}
		else
		{
			Apply_Elite_Gimmick_Failure_Penalty(player);

			cout << endl;
			cout << "코드스니펫의 망령이 도망갔습니다." << endl;
			cout << "보상을 획득하지 못했습니다." << endl;
		}
		return;
	}

	Monster_Type random_Monster_Type = Get_Random_Normal_Monster();
	Monster monster(random_Monster_Type);

	monster.Apply_Player_Level_Scaling(player->getLevel());

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

bool Dungeon_Manager::Check_Elite_Monster_Appearance() const
{
	int appearance_Roll = rand() % 100 + 1;
	return appearance_Roll <= ELITE_APPEARANCE_RATE;
}

Elite_Question Dungeon_Manager::Get_Elite_Question(Chapter_Type chapter_Type) const
{
	Elite_Question elite_Questions[3];

	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
		elite_Questions[0].question = "다음 중 정수값을 저장하는 자료형은 무엇인가?";
		elite_Questions[0].choices[0] = "int";
		elite_Questions[0].choices[1] = "bool";
		elite_Questions[0].choices[2] = "if";
		elite_Questions[0].choices[3] = "while";
		elite_Questions[0].correct_Answer = 1;
		break;

	default:
		elite_Questions[0].question = "정수를 저장하는 자료형은 무엇인가?";
		elite_Questions[0].choices[0] = "int";
		elite_Questions[0].choices[1] = "bool";
		elite_Questions[0].choices[2] = "if";
		elite_Questions[0].choices[3] = "while";
		elite_Questions[0].correct_Answer = 1;
		break;
	}

	int random_Question_Index = rand() % 3;
	return elite_Questions[random_Question_Index];
}

bool Dungeon_Manager::Run_Elite_Question(const Elite_Question& elite_Question)
{
	cout << endl << "========================================" << endl;
	cout << "[ 정예 문제 ]" << endl << elite_Question.question << endl;

	for (int i = 0; i < 4; i++)
	{
		cout << i + 1 << ". " << elite_Question.choices[i] << endl;
	}

	int answer = 0;
	cout << "정답 입력 (1~4): ";
	cin >> answer;

	return answer == elite_Question.correct_Answer;
}

bool Dungeon_Manager::Run_Elite_Quiz(Player* player, Monster& elite_Monster)
{
	if (player == nullptr) return false;

	return Ask_Random_Elite_Question(player, elite_Monster);
}

//=============================================================================
// 6. 튜터 문제 및 대사 파트
//=============================================================================

void Dungeon_Manager::Get_Tutor_Questions(Chapter_Type chapter_Type, Tutor_Question tutor_Questions[]) const
{
	tutor_Questions[0].description = "정수를 저장할 자료형을 입력하세요.";
	tutor_Questions[0].code = "____ score = 100;";
	tutor_Questions[0].correct_Answer = "int";
}

Tutor_Dialogue Dungeon_Manager::Get_Tutor_Dialogue(Chapter_Type chapter_Type) const
{
	Tutor_Dialogue dialogue;
	dialogue.appearance_Message = "등장했습니다.";
	dialogue.correct_Message = "정답입니다.";
	dialogue.wrong_Message = "오답입니다.";
	dialogue.exit_Message = "퇴장합니다.";
	return dialogue;
}

bool Dungeon_Manager::Run_Tutor_Code_Challenge(Player* player, Monster& tutor_Monster)
{
	if (player == nullptr) return false;
	return Tutor_Test(player, tutor_Monster);
}

void Dungeon_Manager::Run_Tutor_Challenge(Player* player, Inventory<Item>& inventory)
{
	if (player == nullptr) return;

	if (!Check_Tutor_Challenge_Available())
	{
		int required_Score = Get_Required_Tutor_Score();
		int remaining_Score = required_Score - _current_Chapter_Score;

		cout << endl << "========================================" << endl;
		cout << "튜터님의 시험 조건을 충족하지 못했습니다." << endl;
		cout << "현재 점수: " << _current_Chapter_Score << " / " << required_Score << endl;
		cout << "필요한 추가 점수: " << remaining_Score << endl;
		cout << "========================================" << endl;
		return;
	}

	Monster tutor_Monster;
	tutor_Monster.Initialize_Tutor_Monster(_current_Chapter);

	bool is_Cleared = Run_Tutor_Code_Challenge(player, tutor_Monster);

	if (!is_Cleared)
	{
		Apply_Tutor_Gimmick_Failure_Penalty();

		cout << endl << "튜터님에게 다시 도전할 수 있습니다." << endl;
		return;
	}

	bool is_Tutor_Item_Given = Give_Tutor_Clear_Item(_current_Chapter, inventory);

	if (!is_Tutor_Item_Given) return;

	player->Gain_Exp(tutor_Monster.getExpReward());

	cout << endl << "========================================" << endl;
	cout << "[ " << tutor_Monster.getName() << " 클리어 보상 ]" << endl;
	cout << "========================================" << endl;
	cout << "획득 경험치: " << tutor_Monster.getExpReward() << endl;
	cout << "획득 고유 아이템: " << Create_Tutor_Clear_Item(_current_Chapter)._Item_Name << endl;
	cout << "========================================" << endl;

	Record_Monster_Kill(tutor_Monster);
	Clear_Current_Chapter();
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
	cout << "========================================" << endl;
	cout << "[ 정예 몬스터 기믹 실패 패널티 ]" << endl;
	cout << "========================================" << endl;
	cout << "플레이어의 HP가 " << decreased_HP << " 감소했습니다." << endl;
	cout << "현재 HP: " << previous_HP << " -> " << player->Get_Hp() << endl;
	cout << "========================================" << endl;
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
	cout << "========================================" << endl;
	cout << "[ 중간보스 기믹 실패 패널티 ]" << endl;
	cout << "========================================" << endl;
	cout << "현재 챕터 점수가 " << decreased_Score << " 감소했습니다." << endl;
	cout << "현재 챕터 점수: " << previous_Score << " -> " << _current_Chapter_Score << endl;
	cout << "========================================" << endl;
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

void Dungeon_Manager::Print_Current_Chapter_Kill_Log() const
{
	cout << endl << "========================================" << endl;
	cout << "[ " << Get_Chapter_Name(_current_Chapter) << " 처치 기록 ]" << endl;
	cout << "========================================" << endl;

	auto chapter_Log = _monster_Kill_Log.find(_current_Chapter);

	if (chapter_Log == _monster_Kill_Log.end() || chapter_Log->second.empty())
	{
		cout << "아직 처치한 몬스터가 없습니다." << endl;
		cout << "========================================" << endl;
		return;
	}

	int total_Kill_Count = 0;
	int total_Earned_Score = 0;

	for (const auto& monster_Log : chapter_Log->second)
	{
		const Monster_Kill_Record& kill_Record = monster_Log.second;

		cout << kill_Record.monster_Name << ": " << kill_Record.kill_Count;
		cout << (kill_Record.monster_Grade == Monster_Grade::TUTOR ? "회 클리어" : "마리");
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

void Dungeon_Manager::Give_Drop_Items_To_Inventory(const Monster& monster, Inventory<Item>& inventory)
{
	const std::vector<Item>& drop_Items = monster.getDropItems();

	for (const Item& drop_Item : drop_Items)
	{
		bool is_Added = inventory.Add_Or_Increase_Item(drop_Item);
		if (!is_Added)
		{
			cout << drop_Item._Item_Name << " 획득을 취소했습니다." << endl;
		}
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
		cout << "현재 챕터 점수가 이미 최대입니다." << endl;
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
		cout << "튜터님 시험 조건을 달성했습니다!" << endl;
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
	cout << endl << Get_Chapter_Name(_current_Chapter) << "을(를) 클리어했습니다!" << endl;

	Move_Next_Chapter();
	_current_Chapter_Score = 0;

	if (_is_All_Chapter_Cleared)
	{
		cout << "모든 일반 챕터를 클리어했습니다!" << endl;
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
		tutor_Item._Item_Name = "손승현 튜터님의 로지텍 마우스";
		break;
	case Chapter_Type::ARRAY_LOOP_OCEAN:
		tutor_Item._Item_Name = "박은일 튜터님의 갈축 키보드";
		break;
	case Chapter_Type::FUNCTION_RUINS:
		tutor_Item._Item_Name = "강신호 튜터님의 게이밍 헤드셋";
		break;
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
		tutor_Item._Item_Name = "문승현 튜터님의 고양이 버츄얼";
		break;
	case Chapter_Type::OBJECT_STL_FACTORY:
		tutor_Item._Item_Name = "김하늘 튜터님의 도수높은 안경";
		break;
	default:
		tutor_Item._Item_Name = "";
		tutor_Item._Item_Count = 0;
		break;
	}

	tutor_Item._Item_Weight = 0;
	return tutor_Item;
}

bool Dungeon_Manager::Has_Item_In_Inventory(Inventory<Item>& inventory, const std::string& item_Name) const
{
	for (int item_Index = 0; item_Index < inventory.Get_Size(); item_Index++)
	{
		Item* inventory_Item = inventory.Get_Item_By_Index(item_Index);

		if (inventory_Item != nullptr && inventory_Item->_Item_Name == item_Name && inventory_Item->_Item_Count > 0)
		{
			return true;
		}
	}
	return false;
}

bool Dungeon_Manager::Give_Tutor_Clear_Item(Chapter_Type chapter_Type, Inventory<Item>& inventory)
{
	Item tutor_Item = Create_Tutor_Clear_Item(chapter_Type);

	if (tutor_Item._Item_Name.empty() || tutor_Item._Item_Count <= 0)
	{
		cout << "튜터 고유 아이템 정보를 찾지 못했습니다." << endl;
		return false;
	}

	if (Has_Item_In_Inventory(inventory, tutor_Item._Item_Name))
	{
		cout << tutor_Item._Item_Name << "을(를) 이미 보유하고 있습니다." << endl;
		return true;
	}

	cout << endl << "========================================" << endl;
	cout << "[ 튜터님 고유 아이템 획득 ]" << endl;
	cout << "========================================" << endl;
	cout << "획득 아이템: " << tutor_Item._Item_Name << endl;

	bool is_Added = inventory.Add_Or_Increase_Item(tutor_Item);

	if (!is_Added)
	{
		cout << "고유 아이템을 인벤토리에 넣지 못했습니다." << endl;
		return false;
	}

	cout << "최종보스방을 여는 열쇠 아이템을 획득했습니다." << endl;
	cout << "========================================" << endl;

	return true;
}

bool Dungeon_Manager::Check_Final_Boss_Room_Available(Inventory<Item>& inventory) const
{
	return Has_Item_In_Inventory(inventory, "손승현 튜터님의 로지텍 마우스")
		&& Has_Item_In_Inventory(inventory, "박은일 튜터님의 갈축 키보드")
		&& Has_Item_In_Inventory(inventory, "강신호 튜터님의 게이밍 헤드셋")
		&& Has_Item_In_Inventory(inventory, "문승현 튜터님의 고양이 버츄얼")
		&& Has_Item_In_Inventory(inventory, "김하늘 튜터님의 도수높은 안경");
}

void Dungeon_Manager::Print_Tutor_Item_Status(Inventory<Item>& inventory) const
{
	cout << endl << "========================================" << endl;
	cout << "[ 튜터님 고유 아이템 수집 현황 ]" << endl;
	cout << "========================================" << endl;

	std::string tutor_Item_Names[5] =
	{
		"손승현 튜터님의 로지텍 마우스",
		"박은일 튜터님의 갈축 키보드",
		"강신호 튜터님의 게이밍 헤드셋",
		"문승현 튜터님의 고양이 버츄얼",
		"김하늘 튜터님의 도수높은 안경"
	};

	int obtained_Item_Count = 0;

	for (int item_Index = 0; item_Index < 5; item_Index++)
	{
		bool has_Item = Has_Item_In_Inventory(inventory, tutor_Item_Names[item_Index]);
		cout << item_Index + 1 << ". " << tutor_Item_Names[item_Index] << " - " << (has_Item ? "보유" : "미보유") << endl;
		if (has_Item) obtained_Item_Count++;
	}

	cout << "----------------------------------------" << endl;
	cout << "수집한 고유 아이템: " << obtained_Item_Count << " / 5" << endl;

	if (Check_Final_Boss_Room_Available(inventory))
	{
		cout << "최종보스방이 열렸습니다!" << endl;
	}
	else
	{
		cout << "최종보스방은 아직 잠겨 있습니다." << endl;
	}
	cout << "========================================" << endl;
}

//=============================================================================
// 10. 최종보스방 파트
//=============================================================================

void Dungeon_Manager::Run_Final_Boss_Room(Player* player, Inventory<Item>& inventory)
{
	if (player == nullptr)
	{
		cout << "플레이어 정보가 없습니다." << endl;
		return;
	}

	// [체크 1] 챕터 클리어 조건 체크 (만약 튜터 아이템만으로 입장시키려면 이 조건문을 주석 처리하거나 제거하세요)
	if (_is_All_Chapter_Cleared == false)
	{
		cout << "아직 모든 챕터를 클리어하지 못했습니다." << endl;
		return;
	}

	// [체크 2] 튜터 아이템 5종 보유 체크
	if (Check_Final_Boss_Room_Available(inventory) == false)
	{
		cout << "튜터님 고유 아이템 5종이 부족합니다." << endl;
		return;
	}

	// 최종 보스 객체 생성 및 초기화
	Monster kim_Dong_Hyun_Manager;
	kim_Dong_Hyun_Manager.Initialize_Final_Boss(Monster_Type::KIM_DONG_HYUN_MANAGER);

	Monster moon_Seung_Ho_Manager;
	moon_Seung_Ho_Manager.Initialize_Final_Boss(Monster_Type::MOON_SEUNG_HO_MANAGER);

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 최종보스방 개방 ]" << endl;
	cout << "========================================" << endl;
	cout << "튜터님들의 고유 아이템이 반응합니다." << endl;
	cout << "최종보스방의 문이 열렸습니다." << endl;

	// ----------------------------------------------------
	// [1차 최종보스전 시작: 김동현 매니저님]
	// ----------------------------------------------------
	cout << endl << "[ 1차 최종보스전 진입 ]" << endl;
	kim_Dong_Hyun_Manager.Print_Monster_Info();

	// 전투 실행
	Boss_Battle(player, kim_Dong_Hyun_Manager, inventory);

	// 1차 보스 전투 후 플레이어 사망 시 퇴장
	if (player->getHP() <= 0)
	{
		cout << "\n김동현 매니저님의 심사를 통과하지 못했습니다..." << endl;
		return;
	}

	// ----------------------------------------------------
	// [2차 최종보스전 시작: 문승호 매니저님]
	// ----------------------------------------------------
	cout << endl;
	cout << "========================================" << endl;
	cout << "김동현 매니저님을 물리쳤습니다!" << endl;
	cout << "문승호 매니저님의 최종 수료 심사가 시작됩니다." << endl;
	cout << "========================================" << endl;

	moon_Seung_Ho_Manager.Print_Monster_Info();

	// 연속 전투 실행
	Boss_Battle(player, moon_Seung_Ho_Manager, inventory);

	// 2차 보스 처치 여부 확인 (최종 게임 클리어)
	if (moon_Seung_Ho_Manager.getHP() <= 0)
	{
		cout << endl;
		cout << "========================================" << endl;
		cout << "   [ 축 하 합 니 다 ! 게 임 클 리 어 ]" << endl;
		cout << " 모든 매니저님의 심사를 완벽히 통과하셨습니다!" << endl;
		cout << "========================================" << endl;
	}
	else
	{
		cout << "\n문승호 매니저님의 최종 심사에서 탈락하셨습니다..." << endl;
	}
}