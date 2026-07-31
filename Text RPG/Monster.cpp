#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace
{
	constexpr int BASE_EXP_REWARD = 100;
	constexpr int BASE_SCORE_REWARD = 100;

	constexpr double CHAPTER_REWARD_MULTIPLIER = 1.3;
}

Monster::Monster()
	: _monster_Type(Monster_Type::INT_SLIME),
	_chapter_Type(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_monster_Grade(Monster_Grade::NORMAL),
	_monster_Level(1),
	_monster_Name("int 슬라임"),
	_evasion(80),
	_accuracy(80),
	_exp_Reward(0),
	_score_Reward(0),
	_attack_Message("int 슬라임이 공격했다."),
	_drop_Item_Name(""),
	_drop_Item_Price(0),
	_drop_Item_Count(0),
	_gold_Reward(0)
{
	_stat[MONSTER_HP] = 3;
	_stat[MONSTER_MP] = 0;
	_stat[MONSTER_POWER] = 3;
	_stat[MONSTER_DEFENCE] = 3;
	_stat[MONSTER_SPEED] = 3;

	_exp_Reward = Calculate_Exp_Reward();
	_score_Reward = Calculate_Score_Reward();
}

Monster::Monster(Monster_Type monster_Type)
	: Monster()
{
	Initialize_Monster(monster_Type);
}

Monster::Monster
(
	string monster_Name,
	int monster_HP,
	int monster_Power,
	int monster_Defence,
	string drop_Item_Name,
	int drop_Item_Price
)
	: _monster_Type(Monster_Type::INT_SLIME),
	_chapter_Type(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_monster_Grade(Monster_Grade::NORMAL),
	_monster_Level(1),
	_monster_Name(monster_Name),
	_evasion(80),
	_accuracy(80),
	_exp_Reward(0),
	_score_Reward(0),
	_attack_Message(monster_Name + "이(가) 공격했다."),
	_drop_Item_Name(drop_Item_Name),
	_drop_Item_Price(drop_Item_Price),
	_drop_Item_Count(0),
	_gold_Reward(0)
{
	_stat[MONSTER_HP] = monster_HP;
	_stat[MONSTER_MP] = 0;
	_stat[MONSTER_POWER] = monster_Power;
	_stat[MONSTER_DEFENCE] = monster_Defence;
	_stat[MONSTER_SPEED] = 3;

	_exp_Reward = Calculate_Exp_Reward();
	_score_Reward = Calculate_Score_Reward();
}

void Monster::Initialize_Monster(Monster_Type monster_Type)
{
	_monster_Type = monster_Type;
	_monster_Grade = Monster_Grade::NORMAL;
	_monster_Level = 1;
	_evasion = 80;
	_accuracy = 80;
	_exp_Reward = 0;
	_score_Reward = 0;
	_drop_Item_Name = "";
	_drop_Item_Price = 0;
	_drop_Item_Count = 0;
	_gold_Reward = 0;

	switch (_monster_Type)
	{
	case Monster_Type::INT_SLIME:
	{
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Name = "int 슬라임";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 3;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "int 슬라임이 정수 덩어리를 던졌습니다.";

		break;
	}

	case Monster_Type::BOOL_MUSHROOM:
	{
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Name = "bool 버섯";

		_stat[MONSTER_HP] = 4;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 2;
		_stat[MONSTER_DEFENCE] = 4;
		_stat[MONSTER_SPEED] = 1;

		_attack_Message = "bool 버섯이 참·거짓 포자를 뿌렸습니다.";

		break;
	}

	case Monster_Type::IF_GOBLIN:
	{
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Name = "if 고블린";

		_stat[MONSTER_HP] = 2;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 4;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 4;

		_attack_Message = "if 고블린이 조건을 확인하고 공격했습니다.";

		break;
	}

	case Monster_Type::ARRAY_JELLYFISH:
	{
		_chapter_Type = Chapter_Type::ARRAY_LOOP_OCEAN;
		_monster_Name = "array 해파리";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 3;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "array 해파리가 촉수 배열로 공격했습니다.";

		break;
	}

	case Monster_Type::FOR_SHARK:
	{
		_chapter_Type = Chapter_Type::ARRAY_LOOP_OCEAN;
		_monster_Name = "for 상어";

		_stat[MONSTER_HP] = 2;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 4;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 5;

		_attack_Message = "for 상어가 반복해서 돌진했습니다.";

		break;
	}

	case Monster_Type::WHILE_WHALE:
	{
		_chapter_Type = Chapter_Type::ARRAY_LOOP_OCEAN;
		_monster_Name = "while 고래";

		_stat[MONSTER_HP] = 5;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 4;
		_stat[MONSTER_SPEED] = 1;

		_attack_Message = "while 고래가 조건이 참인 동안 공격했습니다.";

		break;
	}

	case Monster_Type::PARAMETER_GIANT_FLY:
	{
		_chapter_Type = Chapter_Type::FUNCTION_RUINS;
		_monster_Name = "parameter 왕파리";

		_stat[MONSTER_HP] = 2;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 5;

		_attack_Message = "parameter 왕파리가 매개변수를 날렸습니다.";

		break;
	}

	case Monster_Type::RETURN_GARGOYLE:
	{
		_chapter_Type = Chapter_Type::FUNCTION_RUINS;
		_monster_Name = "return 가고일";

		_stat[MONSTER_HP] = 4;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 2;
		_stat[MONSTER_DEFENCE] = 5;
		_stat[MONSTER_SPEED] = 1;

		_attack_Message = "return 가고일이 공격 결과를 반환했습니다.";

		break;
	}

	case Monster_Type::FUNCTION_MAGE:
	{
		_chapter_Type = Chapter_Type::FUNCTION_RUINS;
		_monster_Name = "function 마법사";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 5;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "function 마법사가 공격 함수를 호출했습니다.";

		break;
	}

	case Monster_Type::POINTER_GHOST:
	{
		_chapter_Type = Chapter_Type::POINTER_MEMORY_GRAVEYARD;
		_monster_Name = "pointer 유령";

		_stat[MONSTER_HP] = 2;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 4;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 5;

		_attack_Message = "pointer 유령이 위험한 주소를 가리켰습니다.";

		break;
	}

	case Monster_Type::NULL_BANSHEE:
	{
		_chapter_Type = Chapter_Type::POINTER_MEMORY_GRAVEYARD;
		_monster_Name = "null 밴시";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 5;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 5;

		_attack_Message = "null 밴시가 비어 있는 메모리의 비명을 질렀습니다.";

		break;
	}

	case Monster_Type::MEMORY_REAPER:
	{
		_chapter_Type = Chapter_Type::POINTER_MEMORY_GRAVEYARD;
		_monster_Name = "memory 사신";

		_stat[MONSTER_HP] = 4;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 4;
		_stat[MONSTER_DEFENCE] = 4;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "memory 사신이 메모리 공간을 베었습니다.";

		break;
	}

	case Monster_Type::CLASS_MACHINE_DOLL:
	{
		_chapter_Type = Chapter_Type::OBJECT_STL_FACTORY;
		_monster_Name = "class 기계인형";

		_stat[MONSTER_HP] = 4;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 4;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "class 기계인형이 객체를 생성해 공격했습니다.";

		break;
	}

	case Monster_Type::INHERITANCE_CHIMERA:
	{
		_chapter_Type = Chapter_Type::OBJECT_STL_FACTORY;
		_monster_Name = "inheritance 키메라";

		_stat[MONSTER_HP] = 4;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 5;
		_stat[MONSTER_DEFENCE] = 3;
		_stat[MONSTER_SPEED] = 2;

		_attack_Message = "inheritance 키메라가 상속받은 기술을 사용했습니다.";

		break;
	}

	case Monster_Type::VECTOR_DRONE:
	{
		_chapter_Type = Chapter_Type::OBJECT_STL_FACTORY;
		_monster_Name = "vector 드론";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 5;

		_attack_Message = "vector 드론이 동적 배열을 발사했습니다.";

		break;
	}

	case Monster_Type::CODE_SNIPPET_WRAITH:
	{
		Initialize_Elite_Monster(_chapter_Type);

		return;
	}
	default:
	{
		_monster_Type = Monster_Type::INT_SLIME;
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Name = "int 슬라임";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 3;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "int 슬라임이 정수 덩어리를 던졌습니다.";

		break;
	}
	}
	_monster_Level = Generate_Random_Level();
	Apply_Level_Bonus();
	_exp_Reward = Calculate_Exp_Reward() + Calculate_Level_Exp_Bonus();
	_score_Reward = Calculate_Score_Reward();
}

void Monster::Initialize_Elite_Monster(Chapter_Type chapter_Type)
{
	_monster_Type = Monster_Type::CODE_SNIPPET_WRAITH;
	_chapter_Type = chapter_Type;
	_monster_Grade = Monster_Grade::ELITE;
	_monster_Level = Get_Chapter_Number() * 3 + 1;
	_monster_Name = "코드 스니펫의 망령";
	_attack_Message = "코드 스니펫의 망령이 문제를 제시했다.";

	_stat[MONSTER_HP] = 0;
	_stat[MONSTER_MP] = 0;
	_stat[MONSTER_POWER] = 0;
	_stat[MONSTER_DEFENCE] = 0;
	_stat[MONSTER_SPEED] = 0;

	_evasion = 0;
	_accuracy = 0;

	_exp_Reward = Calculate_Exp_Reward() * 2;

	_score_Reward = Calculate_Score_Reward() * 2;

	_drop_Item_Name = "";
	_drop_Item_Count = 0;
	_gold_Reward = 0;
}

std::string Monster::Get_Code_Fragment_Name() const
{
	switch (_chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		return "하급 코드 조각";
	}

	case Chapter_Type::FUNCTION_RUINS:
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		return "중급 코드 조각";
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		return "상급 코드 조각";
	}

	default:
	{
		return "하급 코드 조각";
	}
	}
}

int Monster::Calculate_Gold_Reward() const
{
	return rand() % 31 + 20;
}

void Monster::Generate_Drop_Reward()
{
	_drop_Item_Count = 1;
	_gold_Reward = Calculate_Gold_Reward();

	int item_Roll = rand() % 3;

	switch (item_Roll)
	{
	case 0:
	{
		_drop_Item_Name = Get_Code_Fragment_Name();

		break;
	}

	case 1:
	{
		_drop_Item_Name = "컵라면";

		break;
	}

	case 2:
	{
		_drop_Item_Name = "에너지드링크";

		break;
	}

	default:
	{
		_drop_Item_Name = Get_Code_Fragment_Name();

		break;
	}
	}
}

int Monster::Get_Chapter_Number() const
{
	switch (_chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		return 1;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		return 2;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		return 3;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		return 4;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		return 5;
	}

	default:
	{
		return 1;
	}
	}
}

int Monster::Generate_Random_Level() const
{
	int chapter_Number = Get_Chapter_Number();

	if (chapter_Number < 1)
	{
		return 1;
	}

	int minimum_Level = (chapter_Number - 1) * 3 + 1;
	int maximum_Level = chapter_Number * 3;
	int level_Range = maximum_Level - minimum_Level + 1;

	return
		rand() % level_Range + minimum_Level;
}

void Monster::Apply_Level_Bonus()
{
	constexpr int LEVELS_PER_CHAPTER = 3;
	constexpr int HP_BONUS_PER_LEVEL = 2;
	constexpr int POWER_BONUS_PER_LEVEL = 1;
	constexpr int DEFENCE_BONUS_PER_LEVEL = 1;

	int chapter_Number = Get_Chapter_Number();
	int minimum_Level = (chapter_Number - 1) * LEVELS_PER_CHAPTER + 1;
	int level_Offset = _monster_Level - minimum_Level;

	if (level_Offset < 0)
	{
		level_Offset = 0;
	}

	_stat[MONSTER_HP] += level_Offset * HP_BONUS_PER_LEVEL;
	_stat[MONSTER_POWER] += level_Offset * POWER_BONUS_PER_LEVEL;
	_stat[MONSTER_DEFENCE] += level_Offset * DEFENCE_BONUS_PER_LEVEL;
}

int Monster::Calculate_Level_Exp_Bonus() const
{
	constexpr int LEVELS_PER_CHAPTER = 3;
	constexpr int EXP_BONUS_PER_LEVEL = 20;

	int chapter_Number = Get_Chapter_Number();
	int minimum_Level = (chapter_Number - 1) * LEVELS_PER_CHAPTER + 1;
	int level_Offset = _monster_Level - minimum_Level;

	if (level_Offset < 0)
	{
		level_Offset = 0;
	}

	return
		level_Offset * EXP_BONUS_PER_LEVEL;
}

int Monster::Calculate_Exp_Reward() const
{
	double exp_Reward = static_cast<double>(BASE_EXP_REWARD);

	int chapter_Number = Get_Chapter_Number();

	for (int i = 1; i < chapter_Number; i++)
	{
		exp_Reward *= CHAPTER_REWARD_MULTIPLIER;
	}

	return static_cast<int> (exp_Reward + 0.5);
}

int Monster::Calculate_Score_Reward() const
{
	double score_Reward = static_cast<double>(BASE_SCORE_REWARD);

	int chapter_Number = Get_Chapter_Number();

	for (int i = 1; i < chapter_Number; i++)
	{ score_Reward *= CHAPTER_REWARD_MULTIPLIER;
	}

	return static_cast<int> (score_Reward + 0.5);
}

string Monster::getName() const
{
	return _monster_Name;
}

int Monster::getHP() const
{
	return _stat[MONSTER_HP];
}

int Monster::getPower() const
{
	return _stat[MONSTER_POWER];
}

int Monster::getDefence() const
{
	return _stat[MONSTER_DEFENCE];
}

int Monster::getSpeed() const
{
	return _stat[MONSTER_SPEED];
}

int Monster::getEvasion() const
{
	return _evasion;
}

int Monster::getAccuracy() const
{
	return _accuracy;
}

int Monster::getExpReward() const
{
	return _exp_Reward;
}

int Monster::getScoreReward() const
{
	return _score_Reward;
}

int Monster::getMonsterLevel() const
{
	return _monster_Level;
}

string Monster::getDropItemName() const
{
	return _drop_Item_Name;
}

int Monster::getDropItemPrice() const
{
	return _drop_Item_Price;
}

int Monster::getDropItemCount() const
{
	return _drop_Item_Count;
}

int Monster::getGoldReward() const
{
	return _gold_Reward;
}

Monster_Type Monster::getMonsterType() const
{
	return _monster_Type;
}

Chapter_Type Monster::getChapterType() const
{
	return _chapter_Type;
}

string Monster::getAttackMessage() const
{
	return _attack_Message;
}

Monster_Grade Monster::getMonsterGrade() const
{
	return _monster_Grade;
}

void Monster::setMonsterGrade
(
	Monster_Grade monster_Grade
)
{
	_monster_Grade = monster_Grade;
}

void Monster::setHP(int hp)
{
	_stat[MONSTER_HP] = hp;

	if (_stat[MONSTER_HP] < 0)
	{
		_stat[MONSTER_HP] = 0;
	}
}

void Monster::attack(Player* player) const
{
	(void)player;

	Print_Attack_Message();
}

void Monster::Print_Monster_Info() const
{
	cout << "========================================" << endl;
	cout << "몬스터 이름: " << _monster_Name << endl;
	cout << "레벨: " << _monster_Level << endl;
	cout << "HP: " << _stat[MONSTER_HP] << endl;
	cout << "공격력: " << _stat[MONSTER_POWER] << endl;
	cout << "방어력: " << _stat[MONSTER_DEFENCE] << endl;
	cout << "스피드: " << _stat[MONSTER_SPEED] << endl;
	cout << "회피율: " << _evasion << "%" << endl;
	cout << "명중률: " << _accuracy << "%" << endl;
	cout << "경험치: " << _exp_Reward << endl;
	cout << "점수: " << _score_Reward << endl;
	cout << "========================================" << endl;
	cout << "드롭 아이템: " << _drop_Item_Name << " " << _drop_Item_Count << "개" << endl;
	cout << "훈련장려금: " << _gold_Reward << " 원" << endl;

}

void Monster::Print_Attack_Message() const
{
	cout << _attack_Message << endl;
}