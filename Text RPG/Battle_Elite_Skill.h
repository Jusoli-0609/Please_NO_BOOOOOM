#pragma once

#include "Player.h"
#include "Monster.h"
#include "Quiz_Bank.h"

// 엘리트 / 튜터 스킬 발동 조건
bool Check_Elite_Skill(Monster& monster, int turnCount);
// 정예 몬스터 객관식 문제
bool Ask_Quiz(Player* player, Monster&monster, const Quiz& quiz);
bool Ask_Random_Elite_Question(Player* player, Monster& monster);
// 튜터 보스 주관식 문제
bool Ask_Tutor_Question(const Tutor_Question& question);
bool Tutor_Test(Player* player, Monster& monster);

void Execute_Elite_Skill(Player* player, Monster& monster);

// 기존 코드 호환용 래퍼 함수
void Code_Snippet_Question(Player* player, Monster& monster);
void Variable_Condition_Question(Player* player, Monster& monster);
void Array_Loop_Question(Player* player, Monster& monster);
void Function_Question(Player* player, Monster& monster);
void Pointer_Memory_Question(Player* player, Monster& monster);
void Object_Stl_Question(Player* player, Monster& monster);

bool Is_Tutor(Monster& monster);