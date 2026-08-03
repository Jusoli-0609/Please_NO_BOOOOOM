#include "Game_Manager.h"
#include "Monster.h"

Game_Manager::Game_Manager()
    : _Console(120, 40)
{
}

void Game_Manager::Run()
{
    _Console.Set_Console_Font();
    _Console.Set_Console_Size();
    _Console.Clear();

    _Intro.Show(_Console, _Art);   // 인트로
}