#pragma once

#include "Player.h"
#include "Monster.h"

#include <vector>
#include <string>

struct Quiz
{
	std::string question;
	std::vector<std::string> choices;
	int answer;
};

bool Check_Elite_Skill(Monster& monster, int turnCount);

void Execute_Elite_Skill(Player* player, Monster& monster);

void Code_Snippet_Question(Player* player, Monster& monster);

void Variable_Condition_Question(Player* player, Monster& monster);

void Array_Loop_Question(Player* player, Monster& monster);

void Function_Question(Player* player, Monster& monster);

void Pointer_Memory_Question(Player* player, Monster& monster);

void Object_Stl_Question(Player* player, Monster& monster);

bool Ask_Random_Elite_Question(Player* player, Monster& monster);

bool Tutor_Test(Player* player, Monster& monster);

// void Final_Boss_Skill(Player* player, Monster& monster);