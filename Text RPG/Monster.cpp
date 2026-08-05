#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

using namespace std;

namespace
{
	// 기본 경험치 및 점수
	constexpr int BASE_EXP_REWARD = 35;
	constexpr int BASE_SCORE_REWARD = 100;
	// 챕터별 보상 증가 배율
	constexpr double CHAPTER_REWARD_MULTIPLIER = 1.3;
	// 아이템별 독립 드롭 확률
	constexpr int CODE_FRAGMENT_DROP_CHANCE = 45;
	constexpr int CUP_RAMEN_DROP_CHANCE = 25;
	constexpr int ENERGY_DRINK_DROP_CHANCE = 20;
	// 아이템별 무게값
	constexpr int CODE_FRAGMENT_WEIGHT = 1;
	constexpr int CUP_RAMEN_WEIGHT = 1;
	constexpr int ENERGY_DRINK_WEIGHT = 1;
}

//=============================================================================
// 1. 몬스터 생성 파트
//=============================================================================

// 1-1. 기본 몬스터 생성자
Monster::Monster()
	: _monster_Type(Monster_Type::INT_SLIME),
	_chapter_Type(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_monster_Grade(Monster_Grade::NORMAL),
	_monster_Level(1),
	_monster_Name("int 슬라임"),
	_monster_Ascii_Art(""),
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
// 1-2. 몬스터 타입 지정 생성자
Monster::Monster(Monster_Type monster_Type)
	: Monster()
{
	Initialize_Monster(monster_Type);
}
// 1-3. 외부 데이터 입력 생성자
Monster::Monster(string monster_Name, int monster_HP, int monster_Power, int monster_Defence, string drop_Item_Name, int drop_Item_Price)
	: _monster_Type(Monster_Type::INT_SLIME),
	_chapter_Type(Chapter_Type::VARIABLE_CONDITION_FOREST),
	_monster_Grade(Monster_Grade::NORMAL),
	_monster_Level(1),
	_monster_Name(monster_Name),
	_monster_Ascii_Art(""),
	_evasion(80),
	_accuracy(80),
	_exp_Reward(0),
	_score_Reward(0),
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

//=============================================================================
// 2. 몬스터 초기화 파트
//=============================================================================

// 2-1. 일반 몬스터 정보 초기화
void Monster::Initialize_Monster(Monster_Type monster_Type)
{
	_monster_Type = monster_Type;
	_monster_Ascii_Art = "";
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
	_drop_Items.clear();

	switch (_monster_Type)
	{
	case Monster_Type::INT_SLIME:
	{
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Name = "int 슬라임";
		_monster_Ascii_Art =
			R"(      .-""""-.
   .-'  INT   '-.
  /  0       0   \
 |      ___       |
 |   { 1234 }     |
  \      ^       /
   '._       _.'
      '-----')";

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
		_monster_Ascii_Art =
			R"(      .-""""""-.
    .' T BOOL F '.
   /  [1]  [0]   \
  /______________\
      / o  o \
     |  ____  |
     | |____| |
      \__||__/
         ||)";

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
		_monster_Ascii_Art =
			_monster_Ascii_Art =
			R"(       __/\__
    .-/ IF ? \-.
   /  o    o    \
  |   { == }     |
  |  /|  ||  |\  |
  | /_|__||__|_\ |
   \    /\     /
    \__/  \___/)";

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
		_monster_Ascii_Art =
			R"(   .[0][1][2].
 .' ARRAY[]   '.
/  o       o   \
|     ___      |
 \___________/
   \ | | | /
    \| | |/
     | | |
    [0][1][2])";

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
		_monster_Ascii_Art =
			R"(         __
  ______/o \___
<| FOR(i++)    _>
  \____==_____/
      /  \
 ____/    \__)";

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
		_monster_Ascii_Art =
			R"(      _________
 ____/ WHILE   \__
/  o      TRUE   \
|      LOOP      )
\____       ____/
     \_____/
       ||)";

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
		_monster_Name = "parameter 거대파리";
		_monster_Ascii_Art =
			R"( \  /\  /\  /
  \/  \/  \/
 .- PARAM -.
(  o      o )
 \   \__/  /
 /|  ( )  |\
/_|__| |__|_\
   /_/ \_\)";

		_stat[MONSTER_HP] = 2;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 2;
		_stat[MONSTER_SPEED] = 5;

		_attack_Message = "parameter 거대파리가 매개변수를 날렸습니다.";

		break;
	}

	case Monster_Type::RETURN_GARGOYLE:
	{
		_chapter_Type = Chapter_Type::FUNCTION_RUINS;
		_monster_Name = "return 가고일";
		_monster_Ascii_Art =
			R"( /\   RETURN   /\
/  \__________/  \
|   o        o   |
|      /\        |
|   __/  \__     |
 \_/  {;}  \___/
   \___||___/
      /  \)";

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
		_monster_Ascii_Art =
			R"(       /\
      /FN\
     /____\
   .-'o  o'-.
  /  FUNC()  \
 |    /|\     |
 |   /_|_\    |
  \___/ \____/
      / \)";

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
		_monster_Ascii_Art =
			R"(      .------.
    .' PTR*   '.
   /  o     o   \
  |    ->0x00    |
  |     NULL     |
   \    ____    /
    '._/    \_.'
       \____/)";

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
		_monster_Ascii_Art =
			_monster_Ascii_Art =
			R"(    .-NULLPTR-.
  .'          '.
 /   x      x   \
|      ----      |
|   < ACCESS >   |
 \      !!      /
  '._        _.'
     '------')";

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
		_monster_Ascii_Art =
			_monster_Ascii_Art =
			R"(      ______
    .' MEM  '.
   /  x  x   \
  |   [HEAP]  |
   \___||____/
      /||\    _
  ___/ || \__/ )
 /____/  \____/)";

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
		_monster_Ascii_Art =
			R"(    .[ CLASS ].
   /  o     o  \
  |    [==]     |
 /|---[OBJ]---|\
/_|   /||\   |_\
     /_||_\
      /  \)";

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
		_monster_Ascii_Art =
			R"( /\   BASE   /\
/  \________/  \
| o  DERIVED o |
|   /_A__B_\   |
 \__\  ||  /__/
    \__||__/
      /  \)";

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
		_monster_Ascii_Art =
			_monster_Ascii_Art =
			R"(   .< VECTOR >.
  / [0][1][2] \
 |      +      |
  \____===____/
    /  |  \
  --   |   --
      / \)";

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

	case Monster_Type::KIM_DONG_HYUN_MANAGER:
	case Monster_Type::MOON_SEUNG_HO_MANAGER:
	{
		Initialize_Final_Boss(_monster_Type);

		return;
	}

	default:
	{
		_monster_Type = Monster_Type::INT_SLIME;
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Name = "int 슬라임";
		_monster_Ascii_Art =
			R"(      .-""""-.
   .-'  INT   '-.
  /  0       0   \
 |      ___       |
 |   { 1234 }     |
  \      ^       /
   '._       _.'
      '-----')";

		_stat[MONSTER_HP] = 3;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 3;
		_stat[MONSTER_DEFENCE] = 3;
		_stat[MONSTER_SPEED] = 3;

		_attack_Message = "int 슬라임이 정수 덩어리를 던졌습니다.";

		break;
	}
	}
	Apply_Normal_Balance_By_Rating();
	_monster_Level = Generate_Random_Level();
	Apply_Level_Bonus();
	_exp_Reward = Calculate_Exp_Reward() + Calculate_Level_Exp_Bonus();
	_score_Reward = Calculate_Score_Reward();
}
// 2-2. 정예 몬스터 정보 초기화
void Monster::Initialize_Elite_Monster(Chapter_Type chapter_Type)
{
	_monster_Type = Monster_Type::CODE_SNIPPET_WRAITH;
	_chapter_Type = chapter_Type;
	_monster_Grade = Monster_Grade::ELITE;
	_monster_Level = Get_Chapter_Number() * 3 + 1;
	_monster_Name = "코드 스니펫의 망령";
	_monster_Ascii_Art =
		R"(        .-={ CODE FRAGMENT }=-.
     .-' [ERR][404][NULL]    '-.
    /   o                o      \
   |       { BROKEN(); }         |
   | 0101   STACK   1010         |
   |      /\/\ /\/\              |
    \    < SEG_FAULT >           /
     '.___  ____  ____  _____.'
         \_/    \/    \_/
           /   ||   \
          /____||____\)";
	_attack_Message = "코드 스니펫의 망령이 문제를 제시했다.";

	_stat[MONSTER_HP] = 0;
	_stat[MONSTER_MP] = 0;
	_stat[MONSTER_POWER] = 0;
	_stat[MONSTER_DEFENCE] = 0;
	_stat[MONSTER_SPEED] = 0;

	_evasion = 0;
	_accuracy = 0;

	_exp_Reward = Calculate_Exp_Reward() * 2;
	_score_Reward = Calculate_Score_Reward();

	_drop_Item_Name = "";
	_drop_Item_Count = 0;
	_gold_Reward = 0;
}
// 2-3. 튜터 몬스터 정보 초기화
void Monster::Initialize_Tutor_Monster(Chapter_Type chapter_Type)
{
	_chapter_Type = chapter_Type;

	_monster_Grade = Monster_Grade::TUTOR;

	_stat[MONSTER_HP] = 0;
	_stat[MONSTER_MP] = 0;
	_stat[MONSTER_POWER] = 0;
	_stat[MONSTER_DEFENCE] = 0;
	_stat[MONSTER_SPEED] = 0;

	_evasion = 0;
	_accuracy = 0;

	switch (_chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	{
		_monster_Type = Monster_Type::VARIABLE_CONDITION_TUTOR;
		_monster_Name = "손승현 튜터님";
		_monster_Ascii_Art =
			R"(      .------------------.
      | TUTOR_01 : VARIF |
      | STATUS : READY   |
      '------------------'
           .-^^^^-.
          /  o  o  \
         |    ^     |
         |  [ OK ]  |
          \  ___   /
        ___|/___\|___
       /   | IF? |   \
      /____|_____|____\
           /   \)";
		_attack_Message = "변수와 조건문 코드 시험을 시작합니다.";

		break;
	}

	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		_monster_Type = Monster_Type::ARRAY_LOOP_TUTOR;
		_monster_Name = "박은일 튜터님";
		_monster_Ascii_Art =
			R"(      .------------------.
      | TUTOR_02 : LOOP  |
      | INDEX : 0 .. N   |
      '------------------'
           .------.
          /  o  o  \
         |  [i++]   |
         |   ===    |
          \  ___   /
        ___|/___\|___
       /  [0][1][2] \
      /____|___|_____\
          /     \)";
		_attack_Message = "배열과 반복문 코드 시험을 시작합니다.";

		break;
	}

	case Chapter_Type::FUNCTION_RUINS:
	{
		_monster_Type = Monster_Type::FUNCTION_TUTOR;
		_monster_Name = "강신호 튜터님";
		_monster_Ascii_Art =
			R"(      .--------------------.
      | TUTOR_03 : FUNCTION |
      | RETURN : VALUE      |
      '--------------------'
           .------.
          /  o  o  \
         |   FUNC   |
         | RETURN;  |
          \  ___   /
        ___|/___\|___
       /   | ( ) |   \
      /____|_____|____\
           /   \)";
		_attack_Message = "함수 코드 시험을 시작합니다.";

		break;
	}

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		_monster_Type = Monster_Type::POINTER_MEMORY_TUTOR;
		_monster_Name = "문승현 튜터님";
		_monster_Ascii_Art =
			R"(      .------------------.
      | TUTOR_04 : PTR   |
      | ADDR : 0x7FF     |
      '------------------'
           .------.
          /  o  o  \
         |   -> *   |
         |  [MEM]   |
          \  ___   /
        ___|/___\|___
       /   | PTR |   \
      /____|_____|____\
           /   \)";
		_attack_Message = "포인터와 메모리 코드 시험을 시작합니다.";

		break;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		_monster_Type = Monster_Type::OBJECT_STL_TUTOR;
		_monster_Name = "김하늘 튜터님";
		_monster_Ascii_Art =
			R"(      .------------------.
      | TUTOR_05 : OOP   |
      | STL : VECTOR     |
      '------------------'
           .------.
          /  o  o  \
         |  CLASS   |
         | <T, N>   |
          \  ___   /
        ___|/___\|___
       /  <VECTOR>  \
      /____|___|_____\
          /     \)";
		_attack_Message = "객체지향과 STL 코드 시험을 시작합니다.";

		break;
	}

	default:
	{
		_chapter_Type = Chapter_Type::VARIABLE_CONDITION_FOREST;
		_monster_Type = Monster_Type::VARIABLE_CONDITION_TUTOR;
		_monster_Name = "손승현 튜터님";
		_monster_Ascii_Art =
			R"(      .------------------.
      | TUTOR_01 : VARIF |
      | STATUS : READY   |
      '------------------'
           .-^^^^-.
          /  o  o  \
         |    ^     |
         |  [ OK ]  |
          \  ___   /
        ___|/___\|___
       /   | IF? |   \
      /____|_____|____\
           /   \)";
		_attack_Message = "변수와 조건문 코드 시험을 시작합니다.";

		break;
	}
	}

	_monster_Level = Get_Chapter_Number() * 3 + 2;
	_exp_Reward = Calculate_Exp_Reward() * 3;
	_score_Reward = 0;
	_drop_Item_Name = "";
	_drop_Item_Price = 0;
	_drop_Item_Count = 0;
	_gold_Reward = 0;
}
// 2-4. 최종보스 정보 초기화
void Monster::Initialize_Final_Boss(Monster_Type final_Boss_Type)
{
	_monster_Type = final_Boss_Type;
	_chapter_Type = Chapter_Type::ALL_CHAPTER_CLEARED;
	_monster_Grade = Monster_Grade::FINAL_BOSS;
	_monster_Level = 1;
	_monster_Name = "";
	_monster_Ascii_Art = "";
	_attack_Message = "";

	_stat[MONSTER_HP] = 0;
	_stat[MONSTER_MP] = 0;
	_stat[MONSTER_POWER] = 0;
	_stat[MONSTER_DEFENCE] = 0;
	_stat[MONSTER_SPEED] = 0;

	_evasion = 0;
	_accuracy = 0;
	_exp_Reward = 0;
	_score_Reward = 0;
	_drop_Item_Name = "";
	_drop_Item_Price = 0;
	_drop_Item_Count = 0;
	_gold_Reward = 0;
	_drop_Items.clear();

	switch (_monster_Type)
	{
	case Monster_Type::KIM_DONG_HYUN_MANAGER:
	{
		_monster_Name = "김동현 매니저님";
		_monster_Ascii_Art =
			R"(        .--------------------------------------.
        | FINAL_MANAGER_01 :: CODE REVIEW MODE |
        | SYSTEM STATUS : STRICT / ONLINE      |
        '--------------------------------------'
                    _________
                  /|  _____  |\
                 / | | o o | | \
                |  | |  ^  | |  |
                |  | |[OK?]| |  |
                |  | |_____| |  |
                 \ |___| |___| /
                  \____| |____/
                    __/||\__
             ______/___||___\______
            /     [ CODE REVIEW ]   \
           /___ERR___WARN___PASS_____\
              /      ||      \
             /_______||_______\)";
		_monster_Level = 16;

		_stat[MONSTER_HP] = 240;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 26;
		_stat[MONSTER_DEFENCE] = 12;
		_stat[MONSTER_SPEED] = 12;

		_evasion = 65;
		_accuracy = 90;
		_attack_Message = "자 여러분들 좋은 아침입니다. 코드카타 시작해보겠습니다.";

		break;
	}

	case Monster_Type::MOON_SEUNG_HO_MANAGER:
	{
		_monster_Name ="문승호 매니저님";
		_monster_Ascii_Art =
			R"(        .-------------------------------------------.
        | FINAL_MANAGER_02 :: LAST VALIDATION MODE |
        | DEPLOYMENT GATE : LOCKED                 |
        '-------------------------------------------'
                    ___________
                  /|  _______  |\
                 / | |  o o  | | \
                |  | |   ^   | |  |
                |  | | FINAL | |  |
                |  | |_______| |  |
                 \ |____| |____| /
                  \_____| |_____/
                   ___/||||\___
            ______/___||||___\______
           / [ BUILD ][ TEST ][ RUN ] \
          /____FAIL____WARN____PASS____\
              /       ||       \
             /________||________\)";

		_stat[MONSTER_HP] = 280;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 30;
		_stat[MONSTER_DEFENCE] = 15;
		_stat[MONSTER_SPEED] = 14;

		_evasion = 70;
		_accuracy = 90;
		_attack_Message = "자 여러분들 잠깐 스포라이트 하겠습니다.";

		break;
	}

	default:
	{
		_monster_Type = Monster_Type::KIM_DONG_HYUN_MANAGER;
		_monster_Name = "김동현 매니저님";
		_monster_Ascii_Art =
			R"(        .--------------------------------------.
        | FINAL_MANAGER_01 :: CODE REVIEW MODE |
        | SYSTEM STATUS : STRICT / ONLINE      |
        '--------------------------------------'
                    _________
                  /|  _____  |\
                 / | | o o | | \
                |  | |  ^  | |  |
                |  | |[OK?]| |  |
                |  | |_____| |  |
                 \ |___| |___| /
                  \____| |____/
                    __/||\__
             ______/___||___\______
            /     [ CODE REVIEW ]   \
           /___ERR___WARN___PASS_____\
              /      ||      \
             /_______||_______\)";
		_monster_Level = 16;

		_stat[MONSTER_HP] = 240;
		_stat[MONSTER_MP] = 0;
		_stat[MONSTER_POWER] = 26;
		_stat[MONSTER_DEFENCE] = 12;
		_stat[MONSTER_SPEED] = 12;

		_evasion = 65;
		_accuracy = 90;
		_attack_Message = "자 여러분들 좋은 아침입니다. 코드카타 시작해보겠습니다.";

		break;
	}
	}
}

//=============================================================================
// 3. 몬스터 레벨 및 능력치 보정 파트
//=============================================================================

// 3-1. 플레이어 레벨 비례 능력치 증가
void Monster::Apply_Player_Level_Scaling(int player_Level)
{
	if
		(_monster_Grade!= Monster_Grade::NORMAL)
	{
		return;
	}

	if (player_Level < 1)
	{
		player_Level = 1;
	}

	constexpr int HP_BONUS_PER_PLAYER_LEVEL = 3;
	constexpr int POWER_BONUS_PER_PLAYER_LEVEL = 1;
	constexpr int DEFENCE_BONUS_PER_PLAYER_LEVEL = 0;
	constexpr int PLAYER_LEVELS_PER_SPEED_BONUS = 3;

	int player_Level_Up_Count = player_Level - 1;

	_stat[MONSTER_HP] += player_Level_Up_Count * HP_BONUS_PER_PLAYER_LEVEL;
	_stat[MONSTER_POWER] += player_Level_Up_Count * POWER_BONUS_PER_PLAYER_LEVEL;
	_stat[MONSTER_DEFENCE] += player_Level_Up_Count * DEFENCE_BONUS_PER_PLAYER_LEVEL;
	_stat[MONSTER_SPEED] += player_Level_Up_Count / PLAYER_LEVELS_PER_SPEED_BONUS;
}
// 3-2. 챕터 번호 변환
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
// 3-3. 챕터별 몬스터 랜덤 레벨 생성
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
// 3-4. 몬스터 랜덤 레벨 보너스 적용
void Monster::Apply_Level_Bonus()
{
	constexpr int LEVELS_PER_CHAPTER = 3;
	constexpr int HP_BONUS_PER_LEVEL = 4;
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
// 3-5. 챕터별 몬스터 능력치 등급 보정
void Monster::Apply_Normal_Balance_By_Rating()
{
	if (_monster_Grade != Monster_Grade::NORMAL)
	{
		return;
	}

	auto Clamp_Rating = [](int rating)
		{
			if (rating < 1)
			{
				return 1;
			}

			if (rating > 5)
			{
				return 5;
			}

			return rating;
		};

	int chapter_Index = Get_Chapter_Number() - 1;

	if (chapter_Index < 0)
	{
		chapter_Index = 0;
	}

	if (chapter_Index > 4)
	{
		chapter_Index = 4;
	}

	int hp_Rating = Clamp_Rating(_stat[MONSTER_HP]) - 1;
	int power_Rating = Clamp_Rating(_stat[MONSTER_POWER]) - 1;
	int defence_Rating =Clamp_Rating(_stat[MONSTER_DEFENCE]) - 1;
	int speed_Rating =Clamp_Rating(_stat[MONSTER_SPEED]) - 1;

	const int HP_TABLE[5][5] =
	{
		{ 24, 28, 34, 40, 46 },
		{ 38, 46, 54, 62, 70 },
		{ 54, 64, 74, 84, 94 },
		{ 70, 82, 94, 106, 118 },
		{ 88, 102, 116, 130, 145 }
	};

	const int POWER_TABLE[5][5] =
	{
		{ 7, 9, 11, 13, 15 },
		{ 10, 12, 14, 16, 18 },
		{ 13, 15, 17, 19, 21 },
		{ 16, 18, 20, 23, 26 },
		{ 20, 23, 26, 29, 32 }
	};

	const int DEFENCE_TABLE[5][5] =
	{
		{ 0, 1, 2, 3, 4 },
		{ 2, 3, 4, 5, 6 },
		{ 4, 5, 6, 8, 10 },
		{ 6, 8, 10, 12, 14 },
		{ 8, 10, 12, 14, 16 }
	};

	const int SPEED_TABLE[5][5] =
	{
		{ 4, 5, 6, 7, 8 },
		{ 5, 6, 7, 8, 9 },
		{ 6, 7, 8, 9, 10 },
		{ 7, 8, 9, 10, 11 },
		{ 8, 9, 10, 11, 12 }
	};

	_stat[MONSTER_HP] = HP_TABLE[chapter_Index][hp_Rating];
	_stat[MONSTER_POWER] = POWER_TABLE[chapter_Index][power_Rating];
	_stat[MONSTER_DEFENCE] = DEFENCE_TABLE[chapter_Index][defence_Rating];
	_stat[MONSTER_SPEED] = SPEED_TABLE[chapter_Index][speed_Rating];
	_evasion = 45 + (speed_Rating + 1) * 4;
	_accuracy = 85 + speed_Rating * 2;
}
//=============================================================================
// 4. 몬스터 보상 계산 파트
//=============================================================================

// 4-1. 챕터별 코드 조각 이름 결정
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

int Monster::Get_Code_Fragment_Price() const
{
	switch (_chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
	case Chapter_Type::ARRAY_LOOP_OCEAN:
	{
		return 20;
	}

	case Chapter_Type::FUNCTION_RUINS:
	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
	{
		return 30;
	}

	case Chapter_Type::OBJECT_STL_FACTORY:
	{
		return 50;
	}

	default:
	{
		return 20;
	}
	}
}

// 4-2. 챕터별 기본 경험치 계산
int Monster::Calculate_Exp_Reward() const
{
	double exp_Reward = static_cast<double>(BASE_EXP_REWARD);

	int chapter_Number = Get_Chapter_Number();

	for (int i = 1; i < chapter_Number; i++)
	{
		exp_Reward *= CHAPTER_REWARD_MULTIPLIER;
	}

	return static_cast<int>(exp_Reward + 0.5);
}
// 4-3. 랜덤 레벨 경험치 보너스 계산
int Monster::Calculate_Level_Exp_Bonus() const
{
	constexpr int LEVELS_PER_CHAPTER = 3;
	constexpr int EXP_BONUS_PER_LEVEL = 5;

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
// 4-4. 챕터별 점수 계산
int Monster::Calculate_Score_Reward() const
{
	double score_Reward = static_cast<double>(BASE_SCORE_REWARD);

	int chapter_Number = Get_Chapter_Number();

	for (int i = 1; i < chapter_Number; i++)
	{
		score_Reward *= CHAPTER_REWARD_MULTIPLIER;
	}

	return static_cast<int>(score_Reward + 0.5);
}
// 4-5. 훈련장려금 랜덤 계산
int Monster::Calculate_Gold_Reward() const
{
	int chapter_Number = Get_Chapter_Number();

	int min_Gold = 20 + (chapter_Number - 1) * 10;
	int max_Gold = 45 + (chapter_Number - 1) * 15;

	return rand() % (max_Gold - min_Gold + 1) + min_Gold;
}

//=============================================================================
// 5. 몬스터 드롭 보상 생성 파트
//=============================================================================

// 5-1. 아이템별 독립 랜덤 드롭 생성
void Monster::Generate_Drop_Reward()
{
	_drop_Items.clear();
	_drop_Item_Name = "";
	_drop_Item_Price = 0;
	_drop_Item_Count = 0;

	if(_monster_Grade == Monster_Grade::FINAL_BOSS)
	{
		_gold_Reward = 0;

		return;
	}

	_gold_Reward = Calculate_Gold_Reward();

	int code_Fragment_Roll = rand() % 100;

	if
		(code_Fragment_Roll < CODE_FRAGMENT_DROP_CHANCE)
	{
		Item code_Fragment;
		code_Fragment._Item_Name = Get_Code_Fragment_Name();
		code_Fragment._Item_Ascii_Art =
			R"(+--------+
|{CODE;} |
|01010101|
+--------+)";
		code_Fragment._Item_Price = Get_Code_Fragment_Price();
		code_Fragment._Item_Count = 1;
		code_Fragment._Item_Weight = CODE_FRAGMENT_WEIGHT;
		code_Fragment._Item_Type_Usable = false;
		code_Fragment._Item_Type_Wearable = false;
		code_Fragment._Item_Description =
			"깨진 코드 몬스터에게서 떨어져 나온 코드 조각. "
			"아이템 제작과 코드 연구에 사용할 수 있다.";
		_drop_Items.push_back(code_Fragment);
	}

	int cup_Ramen_Roll = rand() % 100;

	if
		(cup_Ramen_Roll < CUP_RAMEN_DROP_CHANCE)
	{
		Item cup_Ramen;
		cup_Ramen._Item_Name = "컵라면";
		cup_Ramen._Item_Ascii_Art =
			R"( .------.
 |RAMEN |
 |~~~~~~|
 '------')";
		cup_Ramen._Item_Price = 15;
		cup_Ramen._Item_Count = 1;
		cup_Ramen._Item_Weight = CUP_RAMEN_WEIGHT;
		cup_Ramen._Item_Type_Usable = true;
		cup_Ramen._Item_Type_Wearable = false;
		cup_Ramen._Item_Description =
			"지친 체력을 채워 주는 컵라면. "
			"사용하면 HP를 50 회복한다.";
		_drop_Items.push_back (cup_Ramen);
	}
	int energy_Drink_Roll = rand() % 100;

	if
		(energy_Drink_Roll < ENERGY_DRINK_DROP_CHANCE)
	{
		Item energy_Drink;
		energy_Drink._Item_Name = "에너지드링크";
		energy_Drink._Item_Ascii_Art =
			R"( .------.
 |ENRG++|
 |[MP50]|
 '------')";
		energy_Drink._Item_Price = 15;
		energy_Drink._Item_Count = 1;
		energy_Drink._Item_Weight = ENERGY_DRINK_WEIGHT;
		energy_Drink._Item_Type_Usable = true;
		energy_Drink._Item_Type_Wearable = false;
		energy_Drink._Item_Description =
			"집중력을 끌어올리는 에너지드링크. "
			"사용하면 MP를 50 회복한다.";
		_drop_Items.push_back(energy_Drink);
	}

	if (_drop_Items.empty())
	{
		Item minimum_Reward;
		minimum_Reward._Item_Name = Get_Code_Fragment_Name();
		minimum_Reward._Item_Ascii_Art =
			R"(+--------+
| CODE{} |
| 010101 |
+--------+)";
		minimum_Reward._Item_Price = Get_Code_Fragment_Price();
		minimum_Reward._Item_Count = 1;
		minimum_Reward._Item_Weight = CODE_FRAGMENT_WEIGHT;
		minimum_Reward._Item_Type_Usable = false;
		minimum_Reward._Item_Type_Wearable = false;
		minimum_Reward._Item_Description =
			"깨진 코드 몬스터에게서 떨어져 나온 코드 조각. "
			"아이템 제작에 사용할 수 있을 것 같다.";
		_drop_Items.push_back
		(minimum_Reward);
	}

	for
		(
			std::size_t item_Index = 0;
			item_Index < _drop_Items.size();
			item_Index++
			)
	{
		const Item& drop_Item = _drop_Items[item_Index];

		if (item_Index > 0)
		{
			_drop_Item_Name += ", ";
		}

		_drop_Item_Name += drop_Item._Item_Name;
		_drop_Item_Name += " ";
		_drop_Item_Name += std::to_string(drop_Item._Item_Count);
		_drop_Item_Name += "개";
		_drop_Item_Count += drop_Item._Item_Count;
		_drop_Item_Price += drop_Item._Item_Price * drop_Item._Item_Count;
	}
}

// 6-1. 몬스터 이름 조회
string Monster::getName() const
{
	return _monster_Name;
}
// 6-2. 몬스터 HP 조회
int Monster::getHP() const
{
	return _stat[MONSTER_HP];
}
// 6-3. 몬스터 공격력 조회
int Monster::getPower() const
{
	return _stat[MONSTER_POWER];
}
// 6-4. 몬스터 방어력 조회
int Monster::getDefence() const
{
	return _stat[MONSTER_DEFENCE];
}
// 6-5. 몬스터 스피드 조회
int Monster::getSpeed() const
{
	return _stat[MONSTER_SPEED];
}
// 6-6. 몬스터 회피율 조회
int Monster::getEvasion() const
{
	return _evasion;
}
// 6-7. 몬스터 명중률 조회
int Monster::getAccuracy() const
{
	return _accuracy;
}
// 6-8. 몬스터 레벨 조회
int Monster::getMonsterLevel() const
{
	return _monster_Level;
}
// 6-9. 몬스터 타입 조회
Monster_Type Monster::getMonsterType() const
{
	return _monster_Type;
}
// 6-10. 몬스터 소속 챕터 조회
Chapter_Type Monster::getChapterType() const
{
	return _chapter_Type;
}
// 6-11. 몬스터 등급 조회
Monster_Grade Monster::getMonsterGrade() const
{
	return _monster_Grade;
}
// 6-12. 몬스터 공격 대사 조회
string Monster::getAttackMessage() const
{
	return _attack_Message;
}

//=============================================================================
// 7. 몬스터 보상 정보 조회 파트
//=============================================================================

// 7-1. 경험치 보상 조회
int Monster::getExpReward() const
{
	return _exp_Reward;
}
// 7-2. 점수 보상 조회
int Monster::getScoreReward() const
{
	return _score_Reward;
}
// 7-3. 드롭 아이템 조회
string Monster::getDropItemName() const
{
	return _drop_Item_Name;
}
// 7-4. 드롭 아이템 가격 합계 조회
int Monster::getDropItemPrice() const
{
	return _drop_Item_Price;
}
// 7-5. 드롭 아이템 수량 합계 조회
int Monster::getDropItemCount() const
{
	return _drop_Item_Count;
}
// 7-6. 드롭 아이템 목록 조회
const std::vector<Item>& Monster::getDropItems() const
{
	return _drop_Items;
}
// 7-7. 훈련장려금 조회
int Monster::getGoldReward() const
{
	return _gold_Reward;
}

//=============================================================================
// 8. 몬스터 상태 변경 및 전투 파트
//=============================================================================

// 8-1. 몬스터 등급 변경
void Monster::setMonsterGrade(Monster_Grade monster_Grade)
{
	_monster_Grade = monster_Grade;
}
// 8-2. 몬스터 HP 변경
void Monster::setHP(int hp)
{
	_stat[MONSTER_HP] = hp;

	if (_stat[MONSTER_HP] < 0)
	{
		_stat[MONSTER_HP] = 0;
	}
}
// 8-3. 몬스터 공격 처리
void Monster::attack(Player* player) const
{
	(void)player;

	Print_Attack_Message();
}

//=============================================================================
// 9. 몬스터 정보 출력 파트
//=============================================================================

// 9-1. 몬스터 공격 대사 출력
void Monster::Print_Attack_Message() const
{
	cout << _attack_Message << endl;
}
// 9-2. 몬스터 아스키 아트 출력
void Monster::Print_Ascii_Art() const
{
	if (_monster_Ascii_Art.empty())
	{
		return;
	}

	cout << _monster_Ascii_Art << endl;
}
// 9-3. 몬스터 전체 정보 출력
void Monster::Print_Monster_Info() const
{
	cout << "╔════════════════════════════════════════════════════╗\n";
	cout << "[ 몬스터 데이터 ]" << endl;
	cout << "╠════════════════════════════════════════════════════╣\n";
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
	cout << "╚════════════════════════════════════════════════════╝\n";

	if
		(
			_drop_Item_Count > 0
			&& _drop_Item_Name.empty() == false
			)
	{
		cout << "드롭 아이템: " << _drop_Item_Name << " " << _drop_Item_Count << "개" << endl;
        cout << "훈련장려금: " << _gold_Reward << "원" << endl;
	}
}
// 9-4. 드롭 아이템과 무게 출력
void Monster::Print_Drop_Reward() const
{
	cout << endl;
	cout << "╔════════════════════════════════════════════════════╗\n";
	cout << "[ 코드 전리품 ]" << endl;
	cout << "╚════════════════════════════════════════════════════╝\n";

	if (_drop_Items.empty())
	{
		cout << "획득한 아이템이 없다." << endl;

		return;
	}

	for (const Item& drop_Item : _drop_Items)
	{
		cout
			<< drop_Item._Item_Name
			<< " "
			<< drop_Item._Item_Count
			<< "개 획득!"
			<< endl;

		cout
			<< "무게: "
			<< drop_Item._Item_Weight
			<< endl;
	}

	cout << "╠════════════════════════════════════════════════════╣\n";
}
// 9-5. 드롭 아이템 아스키 아트 출력
void Monster::Print_Drop_Item_Ascii_Art() const
{
	for
		(const Item& drop_Item : _drop_Items)
	{
		if (drop_Item._Item_Ascii_Art.empty())
		{
			continue;
		}

		drop_Item.Print_Ascii_Art();
	}
}

