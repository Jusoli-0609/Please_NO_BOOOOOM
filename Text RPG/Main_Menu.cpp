#include "Main_Menu.h"
#include <iostream>

using namespace std;

Main_Menu::Main_Menu()
{
}

void Main_Menu::Render() const
{
    cout << "            메인 메뉴\n";

    cout << "1. 던전 입장\n";
    cout << "2. 인벤토리\n";
    cout << "3. 스테이터스\n";
    cout << "4. 저장\n";
    cout << "5. 종료\n";

    cout << "=====================================\n";
}

int Main_Menu::Input() const
{
    int Select;

    cout << "선택 : ";
    cin >> Select;

    return Select;
}

int Main_Menu::Open() const
{
    Render();

    return Input();
}