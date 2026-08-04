#pragma once
#include <string>
class Console_Manager;  //전방선언
class Player;           //전방선언

class UI_Manager
{
public:
    UI_Manager(Console_Manager& console);

    void Draw_Main_Menu(const Player* player);
    void Draw_Game_Over();

private:
    Console_Manager& _Console;

    // 문자열 반복용
    std::string Repeat_Text(const std::string& text,int count);

    // 박스 출력
    void Draw_Box(int x,int y,int width,int height);

    // 제목 출력
    void Draw_Title_Box();

    // 플레이어 정보 박스
    void Draw_Player_Box(const Player* player);

    // 메뉴 박스
    void Draw_Menu_Box();

    // 입력 박스
    void Draw_Input_Box();

    void Draw_Horizontal_Line(int x,int y,int length,char character = '-');
};