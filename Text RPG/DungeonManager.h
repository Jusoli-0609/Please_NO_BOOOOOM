#pragma once
#include "Inventory.h"
#include "Monster.h"
#include "Player.h"
#include <string>
#include <map>

// 1. 정예 몬스터 문제 데이터 파트
struct Elite_Question
{
	std::string question;
	std::string choices[4];
	int correct_Answer = 1;
};

// 2. 튜터 문제 및 대사 데이터 파트
struct Tutor_Dialogue
{
	std::string appearance_Message;
	std::string correct_Message;
	std::string wrong_Message;
	std::string exit_Message;
};
struct Tutor_Question
{
	std::string description;
	std::string code;
	std::string correct_Answer;
};

// 3. 몬스터 처치 기록 데이터 파트
struct Monster_Kill_Record
{
	std::string monster_Name;
	Monster_Grade monster_Grade = Monster_Grade::NORMAL;
	int kill_Count = 0;
	int earned_Score = 0;
};

// 4. 던전 공통 상수 파트
constexpr int MONSTERS_PER_CHAPTER = 3;
constexpr int TUTOR_QUESTION_COUNT = 3;
constexpr int TUTOR_CLEAR_CORRECT_COUNT = 2;

class Dungeon_Manager
{
public:
	// 5. 던전 생성 및 메뉴 실행 파트
	Dungeon_Manager();
	void Open_Dungeon(Player* player, Inventory<Item>& inventory);

	// 6. 던전 상태 조회 및 기록 출력 파트
	bool Check_All_Chapter_Cleared() const;
	bool Check_Game_Cleared() const;
	int Get_Current_Chapter_Score() const;
	void Print_Total_Monster_Kill_Log() const;
	int Monster_Kill_Count = 0;

	// 외부 참조 public 유틸리티
	Item Create_Tutor_Clear_Item(Chapter_Type chapter_Type) const;
	bool Check_Final_Boss_Room_Available(Inventory<Item>& inventory) const;
	void Print_Tutor_Item_Status(Inventory<Item>& inventory) const;

private:
	// 7. 현재 챕터 실행 파트
	void Print_Current_Chapter() const;
	void Run_Current_Chapter(Player* player, Inventory<Item>& inventory);
	std::string Get_Chapter_Name(Chapter_Type chapter_Type) const;

	// 8. 일반 몬스터 선택 파트
	void Get_Current_Chapter_Monsters(Monster_Type monster_Types[]) const;
	Monster_Type Get_Random_Normal_Monster() const;

	// 9. 정예 몬스터 문제 파트
	bool Check_Elite_Monster_Appearance();
	Elite_Question Get_Elite_Question(Chapter_Type chapter_Type) const;
	bool Run_Elite_Question(const Elite_Question& elite_Question);
	bool Run_Elite_Quiz(Player* player, Monster& elite_Monster);

	// 10. 튜터 문제 및 대사 파트
	void Get_Tutor_Questions(Chapter_Type chapter_Type, Tutor_Question tutor_Questions[]) const;
	Tutor_Dialogue Get_Tutor_Dialogue(Chapter_Type chapter_Type) const;
	bool Run_Tutor_Code_Challenge(Player* player, Monster& tutor_Monster);
	void Run_Tutor_Challenge(Player* player, Inventory<Item>& inventory);

	// 11. 기믹 실패 패널티
	void Apply_Elite_Gimmick_Failure_Penalty(Player* player);
	void Apply_Tutor_Gimmick_Failure_Penalty();

	// 12. 처치 기록 및 일반 보상 파트
	void Record_Monster_Kill(const Monster& monster);
	void Give_Drop_Items_To_Inventory(const Monster& monster, Inventory<Item>& inventory);

	// 13. 챕터 점수 및 이동 파트
	void Add_Chapter_Score(int score_Reward);
	int Get_Required_Tutor_Score() const;
	bool Check_Tutor_Challenge_Available() const;
	void Clear_Current_Chapter();
	void Move_Next_Chapter();

	// 14. 튜터 고유 아이템 및 최종보스방
	bool Has_Item_In_Inventory(Inventory<Item>& inventory, const std::string& item_Name) const;
	bool Give_Tutor_Clear_Item(Chapter_Type chapter_Type, Inventory<Item>& inventory);
	void Run_Final_Boss_Room(Player* player,Inventory<Item>& inventory);
	void Run_Ending(const Player* player) const;
	// 15. 던전 진행 상태 데이터 파트
	Chapter_Type _current_Chapter;
	bool _is_All_Chapter_Cleared;
	bool _is_Game_Cleared;
	int _current_Chapter_Score;
	bool _has_Elite_Appeared_In_Current_Chapter;

	// 16. 챕터별 몬스터 처치 기록 데이터 파트
	std::map<Chapter_Type, std::map<Monster_Type, Monster_Kill_Record>> _monster_Kill_Log;
};