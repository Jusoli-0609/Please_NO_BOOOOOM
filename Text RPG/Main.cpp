#include "Game_Manager.h"
#include <filesystem>

using namespace std;

void PrintLine()
{
    cout << string(50, '=') << endl;
}

int main()
{
    char buffer[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, buffer);
    std::cout << "현재 작업 폴더: " << buffer << std::endl;
    system("pause");
    Game_Manager game;
    game.Run();
    return 0;
}