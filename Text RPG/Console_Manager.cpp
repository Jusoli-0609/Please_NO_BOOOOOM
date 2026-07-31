#include "Console_Manager.h"
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

Console_Manager::Console_Manager()
{
    _Width = 120;
    _Height = 40;
}
//임시값입니다. 추후 수정.


Console_Manager::Console_Manager(int Width, int Height)
{
    _Width = Width;
    _Height = Height;
}

void Console_Manager::Set_Console_Size()
{
    std::string Width_Text = std::to_string(_Width);
    std::string Height_Text = std::to_string(_Height);
    //system에서 int를 못 받아서 문자열로 변경

    std::string command =
        "mode con cols=" + Width_Text + " lines=" + Height_Text;

    system(command.c_str());
}

void Console_Manager::Set_Cursor_Position(int x, int y)
{
    COORD pos;
    //windows에서 제공하는 좌표 구조체인데
    //이 구조체에서 int가 아니라 SHORT 타입이어서 아래에서 변환
    //SHORT 쓰는 이유는 큰 숫자가 들어갈 필요가 없기 때문

    pos.X = static_cast<SHORT>(x);
    pos.Y = static_cast<SHORT>(y);

    SetConsoleCursorPosition
    (
        GetStdHandle(STD_OUTPUT_HANDLE),
        pos
    );
}
//windows에서 꺼내온 함수라 네이밍 수정 불가


void Console_Manager::Clear()
{
    system("cls");
}

void Console_Manager::Slow_Print(const std::string& Text, int DelayMs)
{
    for (char ch : Text)
    {
        cout << ch << flush;
        this_thread::sleep_for(chrono::milliseconds(DelayMs));
    }

    cout << endl;
}
//이거 어떤식으로 호출하냐면
//Console.Slow_Print("당신은 8시 55분에 눈을 떴다!", 50);
//이런식으로 써주시면 됩니다.