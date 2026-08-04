#pragma once
#define NOMINMAX
#include <windows.h>
#include <cstdlib>
#include <string>


class Console_Manager
    //콘솔 화면 기능을 모아둔 클래스 
{
private:
    int _Width;
    int _Height;
    //콘솔의 가로, 세로 크기 저장


public:
    Console_Manager();
    //생성자

    Console_Manager(int width, int height);
    //객체 선언

    void Set_Console_Size();
    //콘솔 창 크기 설정

    void Set_Cursor_Position(int x, int y);
    //커서 위치 이동 함수

    void Clear();
    //화면 초기화 함수

    void Slow_Print(const std::string& Text, int DelayMs);

    int Get_Width() const
    {
        return _Width;
    }

    int Get_Height() const
    {
        return _Height;
    }
    // private 멤버 읽는용 함수입니다.

    void Print_At(int x, int y, const std::string& Text);
    void Wait_For_Key(const std::string& Message = "계속하려면 아무 키나 누르세요...");
};