#pragma once
#include "Inventory.h"
#include "Monster.h"
#include "Player.h"
#include <string>

struct Elite_Question
{
	std::string question;
	std::string choices[4];
	int correct_Answer;
};

constexpr int MONSTERS_PER_CHAPTER = 3;

class Dungeon_Manager
{
public:
	Dungeon_Manager();

	void Open_Dungeon(Player* player, Inventory& inventory);

	bool Check_All_Chapter_Cleared() const;

	int Get_Current_Chapter_Score() const;

private:
	void Print_Current_Chapter() const;

	void Run_Current_Chapter
	(Player* player, Inventory& inventory);

	Elite_Question Get_Elite_Question(Chapter_Type chapter_Type) const;

	bool Run_Elite_Quiz(Monster& elite_Monster);

	void Get_Current_Chapter_Monsters(Monster_Type monster_Types[]) const;

	Monster_Type Get_Random_Normal_Monster() const;

	bool Check_Elite_Monster_Appearance() const;

	void Add_Chapter_Score(int score_Reward);

	int Get_Required_Tutor_Score() const;

	bool Check_Tutor_Challenge_Available() const;

	void Clear_Current_Chapter();
	void Move_Next_Chapter();

	std::string Get_Chapter_Name(Chapter_Type chapter_Type) const;

	Chapter_Type _current_Chapter;

	bool _is_All_Chapter_Cleared;

	int _current_Chapter_Score;
};