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

    std::string line(static_cast<std::size_t>(length),character);
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

void UI_Manager::Draw_Titled_Box(
    int x,
    int y,
    int width,
    int height,
    const std::string& title
)
{
    Draw_Box(x, y, width, height);

    _Console.Print_At(
        x + 2,
        y,
        "[ " + title + " ]"
    );
}

void UI_Manager::Draw_Title_Box()
{
    const int x = 1;
    const int y = 1;
    const int width = _Console.Get_Width() - 3;
    const int height = 5;

    Draw_Titled_Box(
        x,
        y,
        width,
        height,
        "눈 떠보니 코드 마스터"
    );
}

void UI_Manager::Draw_Player_Box(const Player* player)
{
    const int x = 1;
    const int y = 7;
    const int width = _Console.Get_Width() - 3;
    const int height = 5;

    Draw_Titled_Box(
        x,
        y,
        width,
        height,
        "PLAYER STATUS"
    );

    if (player == nullptr)
    {
        _Console.Print_At(
            x + 4,
            y + 2,
            "플레이어 정보를 찾을 수 없습니다."
        );

        return;
    }

    _Console.Print_At(
        x + 4,
        y + 2,
        "NAME  " + player->Get_Name()
    );

    _Console.Print_At(
        x + 35,
        y + 2,
        "LEVEL  " + std::to_string(player->getLevel())
    );

    _Console.Print_At(
        x + 60,
        y + 2,
        "HP  " + std::to_string(player->Get_Hp())
    );
}
void UI_Manager::Draw_Menu_Box()
{
    const int x = 1;
    const int y = 15;
    const int width = _Console.Get_Width() - 3;
    const int height = 20;

    Draw_Titled_Box(
        x,
        y,
        width,
        height,
        "MAIN MENU"
    );

    const int menuX = x + 9;

    _Console.Print_At(menuX, y + 4, "> [1] 던전 입장");
    _Console.Print_At(menuX, y + 5, "  [2] 인벤토리");
    _Console.Print_At(menuX, y + 6, "  [3] 캐릭터 정보");
    _Console.Print_At(menuX, y + 7, "  [4] 내일배움캠프 재정비소");
    _Console.Print_At(menuX, y + 8, "  [5] 튜터 선택");
    _Console.Print_At(menuX, y + 9, "  [0] 게임 종료");

    // 메뉴와 입력란 사이의 구분선
    Draw_Separator(
        x,
        y + 11,
        width
    );

    const int inputY = y + 12;

    _Console.Print_At(
        x + 4,
        inputY,
        "선택 : "
    );

    _Console.Set_Cursor_Position(
        x + 11,
        inputY
    );
}

void UI_Manager::Draw_Main_Menu(const Player* player)
{
    _Console.Clear();

    Draw_Title_Box();
    Draw_Player_Box(player);
    Draw_Menu_Box();
}

void UI_Manager::Draw_Game_Over()
{
    // 이전 화면을 지웁니다.
    _Console.Clear();

    // 바깥 테두리
    Draw_Box(
        1,
        1,
        _Console.Get_Width() - 3,
        _Console.Get_Height() - 3
    );

    // 종료 문구
    _Console.Print_At(52,18,"GAME OVER");

    _Console.Print_At(47,21,"게임을 종료합니다.");
}

void UI_Manager::Draw_Separator(
    int x,
    int y,
    int width
)
{
    if (width < 2)
    {
        return;
    }

    const std::string line =
        Repeat_Text("─", width - 2);

    _Console.Print_At(
        x,
        y,
        "├" + line + "┤"
    );
}