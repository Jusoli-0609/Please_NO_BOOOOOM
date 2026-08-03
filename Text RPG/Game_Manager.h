#pragma once
#include "Console_Manager.h"
#include "Ascii_Art_Manager.h"
#include "Intro.h"
#include "DungeonManager.h"
#include "Inventory.h"
#include "Item.h"

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
    Player* _Player;
};