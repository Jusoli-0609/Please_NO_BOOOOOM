#pragma once

#include <memory>
#include "Console_Manager.h"

class Character_Creator;
class Job_Selector;
class Main_Menu;
class Dungeon_Manager;
class Ending_Manager;
//전방선언 도전

class GameManager
{
private:
    Console_Manager Console;

    std::unique_ptr<Job_Selector> JobSelector;
    std::unique_ptr<Main_Menu> MainMenu;
    std::unique_ptr<Dungeon_Manager> DungeonManager;
    std::unique_ptr<Ending_Manager> EndingManager;

public:
    GameManager();
    ~GameManager();

    void Init();
    void Run();

private:
    void Render();
};