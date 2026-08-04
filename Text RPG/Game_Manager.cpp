#include "Game_Manager.h"
#include "Player.h"
#include "Job_Selection.h"
#include "JYJ.h"  
#include <iostream>

using namespace std;

Game_Manager::Game_Manager()
    : _Console(120, 40)
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

    Create_Player();
    Show_Main_Menu();
}

void Game_Manager::Create_Player()
{
    int job = Job_Selection();  
    switch (job)
    {
    case 1:
        _Player = new JYJ("JYJ");
        break;

    default:
        cout << "잘못된 직업 선택입니다. 기본 직업으로 시작합니다." << endl;
        _Player = new JYJ("JYJ");
        break;
    }
        // 플레이어에게 장비와 튜터 정보를 연결
        if (_Player != nullptr)
        {
            _Player->Set_Status_References
            (
                &_Currently_Equipped_Equipments,
                &_Currently_Equipped_Tutor
            );
    }

}

void Game_Manager::Show_Main_Menu()
{
    bool is_Running = true;

    while (is_Running)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "1. 던전 입장" << endl;
        cout << "2. 인벤토리" << endl;
		cout << "3. 상태창" << endl;
        cout << "0. 게임 종료" << endl;
        cout << "선택: ";

        int choice = -1;
        cin >> choice;

        switch (choice)
        {
        case 1:
            _Dungeon.Open_Dungeon(_Player, _Inventory);
            break;

        case 2:
        {
            _Inventory.Print_Inventory_Menu(_Currently_Equipped_Equipments, _Equipment_Inventory);
            break;
        }

		case 3:
			if (_Player != nullptr)
			{
				_Player->Print_Status();
			}
			else
			{
				cout << "플레이어 정보가 없습니다." << endl;
			}
			break;

        case 0:
            cout << "게임 종료!" << endl;
            is_Running = false;
            break;

        default:
            cout << "잘못된 선택!" << endl;
            break;
        }

        if (_Player != nullptr && _Player->Get_Hp() <= 0)
        {
            cout << endl;
            cout << "실패! 다시 시작해보자!" << endl;
            is_Running = false;
        }
    }
}