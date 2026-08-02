#ifndef BATTLE_SYSTEM_H
#define BATTLE_SYSTEM_H

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"

// 전투 메뉴 상수
enum Battle_Menu
{
    ATTACK = 1,
    SKILL = 2,
    ITEM = 3
};

// 함수 선언부
void Battle(Player* player, Monster& monster, Inventory<Item>& inventory);

void Show_Battle_Start(Player* player, Monster& monster);
void Show_Battle_Status(Player* player, Monster& monster, int turnCount);
void Show_Battle_Menu();
void Show_Battle_End(Player* player, Monster& monster);

void Player_Turn(Player* player, Monster& monster, Inventory<Item>& inventory);
void Use_Item(Player* player, Monster& monster, Inventory<Item>& inventory);
void Attack(Player* player, Monster& monster);

// ★ 이 위치에 추가
bool Skill_Menu_Process(Player* player, Monster& monster);
void Skill(Player* player, Monster& monster);

void Monster_Turn(Player* player, Monster& monster, int turnCount);
void Monster_Attack(Player* player, Monster& monster);

bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory);
void Give_Battle_Item_Reward(Player* player, Monster& monster, Inventory<Item>& inventory);

#endif // BATTLE_SYSTEM_H