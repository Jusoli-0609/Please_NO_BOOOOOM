#pragma once
#include "Console_Manager.h"

class GameManager
{
private:
    Console_Manager Console;

public:
    // TODO: GameManager 생성자 선언
    GameManager();

    // TODO: 게임 초기화 함수 선언
    void Init();

    // TODO: 게임 실행 함수 선언
    void Run();

    // TODO: 화면 출력 함수 선언
    void Render();
};