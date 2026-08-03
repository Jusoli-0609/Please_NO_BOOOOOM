#pragma once

class Main_Menu
{
public:
    Main_Menu();

    void Render() const;
    // 메뉴 출력

    int Input() const;
    // 사용자 입력

    int Open() const;
    // 메뉴 실행
};