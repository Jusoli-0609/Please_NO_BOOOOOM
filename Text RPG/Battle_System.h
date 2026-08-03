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

bool Run_Final_Boss_Quiz_Phase(Monster_Type bossType);
void Final_Boss_Monster_Turn(Player* player, Monster& monster);

#endif // BATTLE_SYSTEM_H