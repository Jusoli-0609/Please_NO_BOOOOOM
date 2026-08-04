#include "Battle_UI.h"

#include <Windows.h>
#include <iostream>
#include <string>

void Show_Damage_Effect(
    int damage,
    bool isCritical)
{
    HANDLE consoleHandle =
        GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    if (!GetConsoleScreenBufferInfo(
        consoleHandle,
        &consoleInfo))
    {
        return;
    }

    const WORD originalColor =
        consoleInfo.wAttributes;

    const WORD damageColor =
        isCritical
        ? FOREGROUND_RED |
        FOREGROUND_GREEN |
        FOREGROUND_INTENSITY
        : FOREGROUND_RED |
        FOREGROUND_INTENSITY;

    const std::string damageText =
        isCritical
        ? "★ CRITICAL! -" +
        std::to_string(damage) +
        " ★"
        : "-" + std::to_string(damage);

    SetConsoleTextAttribute(
        consoleHandle,
        damageColor
    );

    const int positions[] =
    {
        4,
        8,
        12,
        8,
        4
    };

    for (int position : positions)
    {
        std::cout
            << '\r'
            << std::string(50, ' ')
            << '\r'
            << std::string(position, ' ')
            << damageText;

        std::cout.flush();

        Sleep(90);
    }

    std::cout
        << '\r'
        << std::string(50, ' ')
        << '\r';

    SetConsoleTextAttribute(
        consoleHandle,
        originalColor
    );
}