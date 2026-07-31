#pragma once
#include "Inventory.h"
#include "Monster.h"
#include "Player.h"
#include <string>
#include <map>

struct Elite_Question
{
	std::string question;
	std::string choices[4];
	int correct_Answer;
};

struct Monster_Kill_Record
{
	std::string monster_Name;
	int kill_Count = 0;
	int earned_Score = 0;
};

constexpr int MONSTERS_PER_CHAPTER = 3;

class Dungeon_Manager
{
public:
	Dungeon_Manager();

	void Open_Dungeon(Player* player, Inventory<Item>& inventory);

	bool Check_All_Chapter_Cleared() const;

	int Get_Current_Chapter_Score() const;

	void Print_Current_Chapter_Kill_Log() const;

	int Monster_Kill_Count=0;

private:
	void Print_Current_Chapter() const;

	void Run_Current_Chapter
	(Player* player, Inventory<Item>& inventory);

	Elite_Question Get_Elite_Question(Chapter_Type chapter_Type) const;

	bool Run_Elite_Quiz(Monster& elite_Monster);

	void Get_Current_Chapter_Monsters(Monster_Type monster_Types[]) const;

	Monster_Type Get_Random_Normal_Monster() const;

	bool Check_Elite_Monster_Appearance() const;

	void Record_Monster_Kill(const Monster& monster);
	void Add_Chapter_Score(int score_Reward);

	int Get_Required_Tutor_Score() const;

	bool Check_Tutor_Challenge_Available() const;

	void Clear_Current_Chapter();
	void Move_Next_Chapter();

	std::string Get_Chapter_Name(Chapter_Type chapter_Type) const;

	Chapter_Type _current_Chapter;

	bool _is_All_Chapter_Cleared;

	int _current_Chapter_Score;

	std::map
		<
		Chapter_Type,
		std::map
		<
		Monster_Type,
		Monster_Kill_Record
		>
		> _monster_Kill_Log;
};