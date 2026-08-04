#pragma once

class Console_Manager;  //전방선언
class Player;           //전방선언

class UI_Manager
{
    private:Console_Manager& _Console;

        void Draw_Box(int x, int y, int width, int height);
        // 사각형 테두리
        void Draw_Horizontal_Line(int x, int y, int length, char character = '-');
        // 가로선

    public:
        UI_Manager(Console_Manager& console);
        void Draw_Main_Menu(const Player* player);
        // 메인 메뉴 화면 그리기
        void Draw_Game_Over();
        // 게임 종료 화면 그리기
};

