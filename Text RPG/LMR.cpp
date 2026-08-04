#include <iostream>
#include "LMR.h"
#include "Monster.h"
#include "Battle_UI.h"
#include <Windows.h>
#include "Console_Manager.h"
//대사 groggyAttackName
//그로기 이름 따로 안적혀있어서 똑같이 특수능력에 있는거 하나 적어놨습니다!그리고 미르님 대사가 2개 밖에 없어서 여쭤보고 추가해야될거같아요!
//나머진 똑같이 내용만 바꿔서 적어놨습니다
//특화 스탯이 따로 정해진게 없어서 이 스탯기준으로 그냥 지피티한테 물어봐서 나온걸 주석으로 한번 적어놓겠습니다!보시고 특화스탯 한번 수정해주세요!
//특화 스탯(SNE) 의미:"식물 특유의 생명력 / 묘한 매력"
namespace
{
    void Apply_Damage(Monster* monster, int damage)
    {
        monster->setHP(monster->getHP() - damage);
    }

    void Print_Typed_Colored(
        const std::string& text,
        WORD color,
        int delayMs = 20)
    {
        HANDLE consoleHandle =
            GetStdHandle(STD_OUTPUT_HANDLE);

        CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
        WORD originalColor =
            FOREGROUND_RED |
            FOREGROUND_GREEN |
            FOREGROUND_BLUE;

        if (GetConsoleScreenBufferInfo(
            consoleHandle,
            &consoleInfo))
        {
            originalColor =
                consoleInfo.wAttributes;
        }

        SetConsoleTextAttribute(
            consoleHandle,
            color
        );

        for (std::size_t i = 0;
             i < text.size();)
        {
            unsigned char firstByte =
                static_cast<unsigned char>(text[i]);

            std::size_t characterSize = 1;

            if ((firstByte & 0xF0) == 0xF0)
            {
                characterSize = 4;
            }
            else if ((firstByte & 0xE0) == 0xE0)
            {
                characterSize = 3;
            }
            else if ((firstByte & 0xC0) == 0xC0)
            {
                characterSize = 2;
            }

            if (i + characterSize > text.size())
            {
                characterSize = 1;
            }

            std::cout.write(
                text.data() + i,
                static_cast<std::streamsize>(
                    characterSize
                )
            );

            std::cout.flush();
            Sleep(delayMs);

            i += characterSize;
        }

        SetConsoleTextAttribute(
            consoleHandle,
            originalColor
        );
    }

    void Print_Bright_Dialogue(
        const std::string& text)
    {
        Print_Typed_Colored(
            text,
            FOREGROUND_GREEN |
            FOREGROUND_BLUE |
            FOREGROUND_INTENSITY,
            20
        );
    }

    void Print_Miss_Message()
    {
        Print_Typed_Colored(
            "공격이 빗나갔습니다!\n",
            FOREGROUND_RED |
            FOREGROUND_BLUE |
            FOREGROUND_INTENSITY,
            20
        );

        Sleep(1000);
    }

    void Print_Damage_Message(int damage, bool isCritical)
    {
        const WORD color = isCritical
            ? FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
            : FOREGROUND_RED | FOREGROUND_INTENSITY;

        if (isCritical)
        {
            Console_Manager::Print_Colored(
                "CRITICAL!\n",
                FOREGROUND_RED |
                FOREGROUND_GREEN |
                FOREGROUND_INTENSITY
            );
        }

        Console_Manager::Print_Colored(
            std::to_string(damage) + "의 피해를 입혔습니다.\n",
            color
        );
    }
}

LMR::LMR(const std::string& name)
    : Player(name)
{
    job = "치코리타(반려식물)";

    skill1Name = "식물인 척하기";
    skill2Name = "울부짖기";
    skill3Name = "몸통박치기";
    groggyAttackName = "아재개그하기";


    Set_Start_Stat(
        200, // HP
        100, // MP
        30,  // ATK
        10,  // DEF
        100, // AP
        5,   // SNE
        10,  // AGI
        200, // MAXHP
        100  // MAXMP
    );
}

void LMR::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [기본 공격]: 공격력 90% + 민첩성(AGI) 10% (식물의 날렵한 평타 컨셉)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        Print_Miss_Message();
        return;
    }

    int damage = Calculate_Damage(
        0.9f, // ATK 90%
        0.0f, // DEF 0%
        0.0f, // HP 0%
        0.0f, // MP 0%
        0.0f, // SNE 0%
        0.1f, // AGI 10%
        monster->getDefence()
    );

    std::cout << name << "의 기본 공격!\n";
    Print_Bright_Dialogue("크와오아앙\n");
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    bool isCritical = Check_Critical();

    Show_Damage_Effect(
        damage,
        isCritical
    );

    if (isCritical)
    {
        damage = static_cast<int>(damage * 1.5f);
    }

    Print_Damage_Message(damage, isCritical);
    Apply_Damage(monster, damage);

    // 피해 결과를 확인할 수 있도록 다음 화면 전환 전 1초 대기
    Sleep(1000);
}

void LMR::Skill1(Monster* monster)
{
    const int mpCost = 10;

    if (monster == nullptr)
    {
        std::cout << "스킬을 사용할 대상이 없습니다.\n";
        return;
    }

    if (mp < mpCost)
    {
        std::cout << "MP가 부족합니다.\n";
        return;
    }

    mp -= mpCost;

    // [스킬 1 - 식물인 척하기]: 순식간에 숨었다가 날렵하게 틈을 파고드는 컨셉 (공격력 100% + 민첩성 AGI 30%)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        Print_Miss_Message();
        return;
    }

    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f, // ATK 100%
        0.0f, 0.0f, 0.3f, // AGI 30%
        monster->getDefence()
    );

    std::cout << name << "의" << skill1Name << "!\n";
    Print_Bright_Dialogue(name + " : 크아아\n");
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    bool isCritical = Check_Critical();

    Show_Damage_Effect(
        damage,
        isCritical
    );

    if (isCritical)
    {
        damage = static_cast<int>(damage * 1.5f);
    }

    Print_Damage_Message(damage, isCritical);
    Apply_Damage(monster, damage);

    // 피해 결과를 확인할 수 있도록 다음 화면 전환 전 1초 대기
    Sleep(1000);
}

void LMR::Skill2(Monster* monster)
{
    const int mpCost = 20;

    if (monster == nullptr)
    {
        std::cout << "스킬을 사용할 대상이 없습니다.\n";
        return;
    }

    if (mp < mpCost)
    {
        std::cout << "MP가 부족합니다.\n";
        return;
    }

    mp -= mpCost;

    // [스킬 2 - 울부짖기]: 반려식물이 뿜어내는 생명력의 울부짖음 컨셉 (공격력 120% + 체력 HP 20%)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        Print_Miss_Message();
        return;
    }

    int damage = Calculate_Damage(
        1.2f, 0.0f, 0.2f, // ATK 120%, HP 20%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    std::cout << name << "의 " << skill2Name << "!\n";
    Print_Bright_Dialogue("어디까지 하셨나요?\n"); // 여기 대사 추가해야됨
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    bool isCritical = Check_Critical();

    Show_Damage_Effect(
        damage,
        isCritical
    );

    if (isCritical)
    {
        damage = static_cast<int>(damage * 1.5f);
    }

    Print_Damage_Message(damage, isCritical);
    Apply_Damage(monster, damage);

    // 피해 결과를 확인할 수 있도록 다음 화면 전환 전 1초 대기
    Sleep(1000);
}

void LMR::Skill3(Monster* monster)
{
    const int mpCost = 30;

    if (monster == nullptr)
    {
        std::cout << "스킬을 사용할 대상이 없습니다.\n";
        return;
    }

    if (mp < mpCost)
    {
        std::cout << "MP가 부족합니다.\n";
        return;
    }

    mp -= mpCost;

    // [스킬 3 - 몸통박치기]: 온 힘과 마나를 집중해 강하게 부딪치는 주력기 컨셉 (공격력 150% + 마나 MP 30%)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        Print_Miss_Message();
        return;
    }

    int damage = Calculate_Damage(
        1.5f, 0.0f, 0.0f, // ATK 150%
        0.3f, 0.0f, 0.0f, // MP 30%
        monster->getDefence()
    );

    std::cout << name << "의 " << skill3Name << "!\n";
    Print_Bright_Dialogue("크크크(웃기)\n"); //여기 대사 추가해야됨
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    bool isCritical = Check_Critical();

    Show_Damage_Effect(
        damage,
        isCritical
    );

    if (isCritical)
    {
        damage = static_cast<int>(damage * 1.5f);
    }

    Print_Damage_Message(damage, isCritical);
    Apply_Damage(monster, damage);

    // 피해 결과를 확인할 수 있도록 다음 화면 전환 전 1초 대기
    Sleep(1000);
}

void LMR::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [그로기 공격 - 아재개그하기]: 묵직한 방어력을 실어 상대의 멘탈을 짓누르는 일격 컨셉 (공격력 180% + 방어력 DEF 40%)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        Print_Miss_Message();
        return;
    }

    int damage = Calculate_Damage(
        1.8f, 0.4f, 0.0f, // ATK 180%, DEF 40%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    std::cout << name << "의 " << groggyAttackName << "!\n";
    Print_Bright_Dialogue("아재개그하기\n");
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    bool isCritical = Check_Critical();

    Show_Damage_Effect(
        damage,
        isCritical
    );

    if (isCritical)
    {
        damage = static_cast<int>(damage * 1.5f);
    }

    Print_Damage_Message(damage, isCritical);
    Apply_Damage(monster, damage);

    // 피해 결과를 확인할 수 있도록 다음 화면 전환 전 1초 대기
    Sleep(1000);
}
