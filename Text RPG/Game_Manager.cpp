#include "Game_Manager.h"
#include "Player.h"
#include "Job_Selection.h"
#include "JYJ.h"  
#include "JSR.h"
#include "JWH.h"
#include "LYB.h"
#include "LMR.h"
#include "PSB.h"
#include "Camp_Manager.h"
#include <iostream>

using namespace std;

Game_Manager::Game_Manager()
    : _Console(120, 40)
    , _UI(_Console)
    , _Inventory(20, 100)
    , _Player(nullptr)
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
}

Game_Manager::~Game_Manager()
{
    delete _Player;   //소멸자에서 반드시 해제
}

void Game_Manager::Run()
{
    _Console.Set_Console_Size();
    _Console.Clear();

    _Intro.Show(_Console, _Art);   // 멤버 함수 호출
    _Console.Clear();

    Create_Player();
    Show_Main_Menu();
}

void Game_Manager::Create_Player()
{
    int job = Job_Selection();
    switch (job)
    {
    case 1:
    {
        _Player = new JYJ("JYJ");
        break;
    }

    case 2:
    {
        _Player = new JSR("JSR");
        break;
    }

    case 3:
    {
        _Player = new JWH("JWH");
        break;
    }

    case 4:
    {
        _Player = new LYB("LYB");
        break;
    }

    case 5:
    {
        _Player = new LMR("LMR");
        break;
    }

    case 6:
    {
        _Player = new PSB("PSB");
        break;
    }

    default:
    {
        cout << "잘못된 직업 선택! " << "기본 직업으로 시작!" << endl;
        _Player = new JYJ("JYJ");
        break;
    }
    }

    if (_Player != nullptr)
    {
        _Player->Set_Status_References(&_Currently_Equipped_Equipments, &_Currently_Equipped_Tutor);
    }
}

void Game_Manager::Show_Main_Menu()
{
    bool is_Running = true;

    while (is_Running)
    {
        // 이전 화면 삭제 + 메인 UI 재출력
        _UI.Draw_Main_Menu(_Player);

        int choice = -1;
        cin >> choice;

        switch (choice)
        {
        case 1:
            _Console.Clear();

            _Dungeon.Open_Dungeon(
                _Player,
                _Inventory,
                _Equipment_Inventory,
                _Currently_Equipped_Equipments,
                _Console
            );
            break;

        case 2:
            _Console.Clear();

            _Inventory.Print_Inventory_Menu(
                _Currently_Equipped_Equipments,
                _Equipment_Inventory,
                *_Player
            );
            break;

        case 3:
            _Console.Clear();

            if (_Player != nullptr)
            {
                _Player->Print_Status();
            }

            _Console.Wait_For_Key();
            break;

        case 4:
        {
            _Console.Clear();

            Camp_Manager camp_Manager(
                *_Player,
                _Inventory,
                _Equipment_Inventory,
                _Currently_Equipped_Equipments
            );

            camp_Manager.Open_Camp_Menu();
            break;
        }

        case 5:
            _Console.Clear();

            Print_Tutor_Menu(
                _Equipment_Inventory,
                _Currently_Equipped_Equipments,
                _Currently_Equipped_Tutor,
                _Player
            );
            break;

        case 0:
            _UI.Draw_Game_Over();
            is_Running = false;
            break;

        default:
            _Console.Wait_For_Key(
                "잘못된 입력!."
            );
            break;
        }
    }
}