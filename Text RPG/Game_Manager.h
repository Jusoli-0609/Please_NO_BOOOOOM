#pragma once
#include "Player.h"
#include "DungeonManager.h"
#include "Console_Manager.h"
#include "Battle_System.h"
#include "Intro.h"
#include "Ascii_Art_Manager.h"

class Game_Manager
{
private:
    Console_Manager   _Console;
    Ascii_Art_Manager _Art;
    Intro             _Intro;      

public:
    Game_Manager();
    void Run();
};