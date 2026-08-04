#pragma once
#include "Console_Manager.h"
#include "Ascii_Art_Manager.h"
#include "Intro.h"
#include "DungeonManager.h"
#include "Equipment.h"
#include "Inventory.h"
#include "Item.h"
#include "Tutor.h"

class Player;

class Game_Manager
{
public:
    Game_Manager();
    ~Game_Manager();
    void Run();

private:
    void Create_Player();
    void Show_Main_Menu();

    Console_Manager    _Console;
    Ascii_Art_Manager  _Art;
    Intro              _Intro;
    Dungeon_Manager    _Dungeon;
    Inventory<Item>    _Inventory;
    Inventory_For_Equipments_Only _Equipment_Inventory;
    Currently_Equipped_Equipments _Currently_Equipped_Equipments;
    Currently_Equipped_Tutor _Currently_Equipped_Tutor;
    Player* _Player;
};