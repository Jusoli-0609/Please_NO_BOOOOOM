#include "UI_Manager.h"

#include "Console_Manager.h"
#include "Player.h"

#include <string>

UI_Manager::UI_Manager(Console_Manager& console): _Console(console)
{
}

void UI_Manager::Draw_Horizontal_Line(int x,int y,int length,char character)
{
    if (length <= 0)
    {
        return;
    }
    //길이가 0 이하이면 선X

    std::string line(
        static_cast<std::size_t>(length),
        character
    );
    //character 문자를 length만큼 반복한 문자열을 만들기

    _Console.Print_At(x, y, line);
    //완성한 문자열을 지정한 좌표에 출력
}

void UI_Manager::Draw_Box(int x,int y,int width,int height)
{
    if (width < 2 || height < 2)
    {
        return;
    }
    //가로or세로가 2보다 작으면
    //사각형 형태X

    std::string horizontal_Line(static_cast<std::size_t>(width - 2),'-');
    //사각형 위아래에 사용할 가로선

    _Console.Print_At(
        x,
        y,
        "+" + horizontal_Line + "+"
    );
    // 사각형 위쪽

    // 사각형 왼쪽과 오른쪽
    for (int row = 1; row < height - 1; ++row)
    {
        _Console.Print_At(
            x,
            y + row,
            "|"
        );

        _Console.Print_At(
            x + width - 1,
            y + row,
            "|"
        );
    }

    // 사각형 아래쪽
    _Console.Print_At(
        x,
        y + height - 1,
        "+" + horizontal_Line + "+"
    );
}

void UI_Manager::Draw_Main_Menu(const Player* player)
{
    // 이전 화면을 모두 지웁니다.
    _Console.Clear();

    // 콘솔 전체 크기에 맞는 바깥 테두리를 그립니다.
    Draw_Box(
        0,
        0,
        _Console.Get_Width(),
        _Console.Get_Height()
    );

    // 게임 제목
    _Console.Print_At(
        4,
        2,
        "[ 눈 떠보니 코드 마스터 ]"
    );

    // 제목 아래 구분선
    Draw_Horizontal_Line(
        1,
        4,
        _Console.Get_Width() - 2,
        '='
    );

    // 플레이어 객체가 정상적으로 존재하는 경우에만
    // 플레이어 정보를 출력합니다.
    if (player != nullptr)
    {
        _Console.Print_At(
            4,
            6,
            "플레이어 : " + player->Get_Name()
        );

        _Console.Print_At(
            4,
            7,
            "HP : " + std::to_string(player->Get_Hp())
        );

        _Console.Print_At(
            4,
            8,
            "LEVEL : " + std::to_string(player->getLevel())
        );
    }
    else
    {
        _Console.Print_At(
            4,
            6,
            "플레이어 정보를 찾을 수 없습니다."
        );
    }

    // 메인 메뉴
    _Console.Print_At(10, 13, "[1] 던전 입장");
    _Console.Print_At(10, 16, "[2] 인벤토리");
    _Console.Print_At(10, 19, "[3] 캐릭터 정보");
    _Console.Print_At(10, 22, "[4] 내일배움캠프 재정비소");
    _Console.Print_At(10, 25, "[5] 튜터 선택");
    _Console.Print_At(10, 28, "[0] 게임 종료");

    // 화면 아래쪽 구분선
    Draw_Horizontal_Line(
        1,
        _Console.Get_Height() - 5,
        _Console.Get_Width() - 2,
        '='
    );

    // 입력 안내
    _Console.Print_At(
        4,
        _Console.Get_Height() - 3,
        "선택 : "
    );

    // 사용자가 입력할 위치로 커서를 옮깁니다.
    _Console.Set_Cursor_Position(
        11,
        _Console.Get_Height() - 3
    );
}

void UI_Manager::Draw_Game_Over()
{
    // 이전 화면을 지웁니다.
    _Console.Clear();

    // 바깥 테두리
    Draw_Box(
        0,
        0,
        _Console.Get_Width(),
        _Console.Get_Height()
    );

    // 종료 문구
    _Console.Print_At(
        52,
        18,
        "GAME OVER"
    );

    _Console.Print_At(
        47,
        21,
        "게임을 종료합니다."
    );
}