#include "Console_Manager.h"
#include <string>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

Console_Manager::Console_Manager()
{
    _Width = 120;
    _Height = 50;
}
//임시값입니다. 추후 수정.

Console_Manager::Console_Manager(int Width, int Height)
{
    _Width = Width;
    _Height = Height;
}

void Console_Manager::Set_Console_Size()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    COORD bufferSize;
    bufferSize.X = static_cast<SHORT>(_Width);
    bufferSize.Y = static_cast<SHORT>(_Height);

    SetConsoleScreenBufferSize(hConsole, bufferSize);

    SMALL_RECT rect;
    rect.Left = 0;
    rect.Top = 0;
    rect.Right = _Width - 1;
    rect.Bottom = _Height - 1;

    SetConsoleWindowInfo(hConsole, TRUE, &rect);
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
//windows에서 꺼내온 함수라 네이밍 수정 불가!


void Console_Manager::Clear()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD written;

    COORD home = { 0, 0 };

    // 화면의 모든 문자를 공백으로 채움
    FillConsoleOutputCharacter(
        hConsole,
        ' ',
        consoleSize,
        home,
        &written
    );

    // 글자 색상도 초기화
    FillConsoleOutputAttribute(
        hConsole,
        csbi.wAttributes,
        consoleSize,
        home,
        &written
    );

    // 커서를 (0,0)으로 이동
    SetConsoleCursorPosition(hConsole, home);
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

void Console_Manager::Print_At(int x, int y, const std::string& text)
{
    Set_Cursor_Position(x, y);
    std::cout << text << std::flush;
}