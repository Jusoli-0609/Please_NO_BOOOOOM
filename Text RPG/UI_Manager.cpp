#include "UI_Manager.h"

#include "Console_Manager.h"
#include "Player.h"

#include <string>

UI_Manager::UI_Manager(Console_Manager& console): _Console(console)
{
}

std::string UI_Manager::Repeat_Text(
    const std::string& text,
    int count
)
{
    if (count <= 0)
    {
        return "";
    }

    std::string result;

    for (int i = 0; i < count; ++i)
    {
        result += text;
    }

    return result;
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

    std::string horizontal = Repeat_Text("─", width - 2);

    // 위쪽
    _Console.Print_At(x,y,"┌" + horizontal + "┐");

    // 가운데 세로선
    for (int row = 1; row < height - 1; ++row)
    {
        _Console.Print_At(x, y + row, "│");
        _Console.Print_At(x + width - 1, y + row, "│");
    }

    // 아래쪽
    _Console.Print_At(x,y + height - 1,"└" + horizontal + "┘");
}

void UI_Manager::Draw_Title_Box()
{
    int width = _Console.Get_Width();

    Draw_Box(0, 0, width, 5);

    _Console.Print_At(
        4,
        2,
        "[ 눈 떠보니 코드 마스터 ]"
    );
}

void UI_Manager::Draw_Player_Box(const Player* player)
{
    int width = _Console.Get_Width();

    Draw_Box(0, 5, width, 7);

    if (player != nullptr)
    {
        _Console.Print_At(
            4,
            7,
            "플레이어 : " + player->Get_Name()
        );

        _Console.Print_At(
            4,
            8,
            "HP       : " + std::to_string(player->Get_Hp())
        );

        _Console.Print_At(
            4,
            9,
            "LEVEL    : " + std::to_string(player->getLevel())
        );
    }
    else
    {
        _Console.Print_At(
            4,
            8,
            "플레이어 정보를 찾을 수 없습니다."
        );
    }
}

void UI_Manager::Draw_Menu_Box()
{
    int width = _Console.Get_Width();

    Draw_Box(0, 12, width, 19);

    _Console.Print_At(10, 15, "[1] 던전 입장");
    _Console.Print_At(10, 17, "[2] 인벤토리");
    _Console.Print_At(10, 19, "[3] 캐릭터 정보");
    _Console.Print_At(10, 21, "[4] 내일배움캠프 재정비소");
    _Console.Print_At(10, 23, "[5] 튜터 선택");
    _Console.Print_At(10, 25, "[0] 게임 종료");
}

void UI_Manager::Draw_Main_Menu(const Player* player)
{
    _Console.Clear();

    Draw_Title_Box();
    Draw_Player_Box(player);
    Draw_Menu_Box();
    Draw_Input_Box();
}

void UI_Manager::Draw_Input_Box()
{
    int width = _Console.Get_Width();
    int height = _Console.Get_Height();

    Draw_Box(0, height - 4, width, 4);

    _Console.Print_At(
        4,
        height - 2,
        "선택 : "
    );

    _Console.Set_Cursor_Position(
        11,
        height - 2
    );
}

void UI_Manager::Draw_Game_Over()
{
    // 이전 화면을 지웁니다.
    _Console.Clear();

    // 바깥 테두리
    Draw_Box(0,0,_Console.Get_Width(),_Console.Get_Height());

    // 종료 문구
    _Console.Print_At(52,18,"GAME OVER");

    _Console.Print_At(47,21,"게임을 종료합니다.");
}