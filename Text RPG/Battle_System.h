#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"
#include "Quiz_Bank.h" // [추가] Quiz 및 vector<Quiz> 인식을 위해 필수


#include <vector>

// 전투 메뉴 상수
enum Battle_Menu
{
    ATTACK = 1,
    SKILL = 2,
    ITEM = 3
};

void Battle(Player* player, Monster& monster, Inventory<Item>& inventory);

void Show_Battle_Start(Player* player, Monster& monster);
void Show_Battle_Status(Player* player, Monster& monster, int turnCount);
void Show_Battle_Menu();
void Show_Battle_End(Player* player, Monster& monster);

void Player_Turn(Player* player, Monster& monster, Inventory<Item>& inventory);
void Use_Item(Player* player, Monster& monster, Inventory<Item>& inventory);
void Attack(Player* player, Monster& monster);

bool Skill_Menu_Process(Player* player, Monster& monster);
void Skill(Player* player, Monster& monster);

void Monster_Turn(Player* player, Monster& monster, int turnCount);
void Monster_Attack(Player* player, Monster& monster);

bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory);
void Give_Battle_Item_Reward(Player* player, Monster& monster, Inventory<Item>& inventory);

void Boss_Battle(Player* player, Monster& monster, Inventory<Item>& inventory);

void First_Impression_Duo_Phase(Player* player, Monster& kim, Monster& moon, std::vector<Quiz>& kimQuizPool, std::vector<Quiz>& moonQuizPool);

// 플레이어 턴 (공격 대상 선택)
void Duo_Player_Turn(Player* player, Monster& kim, Monster& moon, Inventory<Item>& inventory);

// 듀오 보스 턴
void Duo_Boss_Turn(Player* player, Monster& kim, Monster& moon, int turnCount, std::vector<Quiz>& kimQuizPool, std::vector<Quiz>& moonQuizPool);

// 듀오전 종료 확인
bool Check_Duo_Battle_End(Player* player, Monster& kim, Monster& moon, Inventory<Item>& inventory);

// 듀오 상태 출력
void Show_Duo_Battle_Status(Player* player, Monster& kim, Monster& moon, int turnCount);
// ===================================================
// [최종 보스전 전용 함수 선언]
// ===================================================
bool Ask_Single_Quiz(const Quiz& quiz);
void First_Impression_Quiz_Phase(Player* player, Monster& monster, std::vector<Quiz>& quizPool);
void Final_Boss_Monster_Turn(Player* player, Monster& monster, int turnCount, std::vector<Quiz>& quizPool);

#endif // BATTLE_SYSTEM_H