#pragma once

#include "Player.h"
#include "Monster.h"
#include "Inventory.h"
#include "Item.h"

// =======================
// 전투 메뉴
// =======================

enum Battle_Menu
{
    ATTACK = 1,
    SKILL,
    ITEM
};

// =======================
// 전투 시작
// =======================

void Battle(Player* player, Monster& monster, Inventory<Item>& inventory);

// =======================
// UI (UI 담당)
// =======================

void Show_Battle_Start(Player* player, Monster& monster);

void Show_Battle_Status(Player* player, Monster& monster, int turnCount);

void Show_Battle_Menu();

void Show_Battle_End(Player* player, Monster& monster);

// =======================
// 플레이어 턴
// =======================

void Player_Turn(Player*, Monster& monster, Inventory<Item>& inventory);

void Attack(Player* player, Monster& monster);

void Skill(Player* player, Monster& monster);

void Use_Item(Player* player, Inventory<Item>& inventory);

// =======================
// 몬스터 턴
// =======================

void Monster_Turn(Player* player, Monster& monster, int turnCount);

void Monster_Attack(Player* player, Monster& monster);

void Monster_Skill(Player* player, Monster& monster);

// =======================
// 전투 종료
// =======================

bool Check_Battle_End(Player* player, Monster& monster, Inventory<Item>& inventory);