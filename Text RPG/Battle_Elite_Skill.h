#pragma once

#include "Player.h"
#include "Monster.h"
#include "Quiz_Bank.h"

#include <vector>

//======================================================
// 스킬 및 퀴즈 관련 함수 선언
//======================================================
bool Check_Elite_Skill(Monster& monster, int turnCount);
bool Ask_Quiz(Player* player, Monster& monster, const Quiz& quiz);
bool Ask_Random_Elite_Question(Player* player, Monster& monster);

std::vector<Quiz>* Get_Tutor_Quiz(Monster_Type type);
bool Tutor_Test(Player* player, Monster& monster);
void Execute_Elite_Skill(Player* player, Monster& monster);

// 문제 출제 래퍼 함수들
void Code_Snippet_Question(Player* player, Monster& monster);
void Variable_Condition_Question(Player* player, Monster& monster);
void Array_Loop_Question(Player* player, Monster& monster);
void Function_Question(Player* player, Monster& monster);
void Pointer_Memory_Question(Player* player, Monster& monster);
void Object_Stl_Question(Player* player, Monster& monster);

bool Is_Tutor(Monster& monster);