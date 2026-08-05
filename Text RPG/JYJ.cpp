#include <iostream>
#include "JYJ.h"
#include "Monster.h"
#include "Battle_UI.h"
#include <Windows.h>
#include "Console_Manager.h"
//대사 groggyAttackName
//JYJ 윤재님꺼 같은경우엔 미리 영빈님이 만들어놨었어서 따로 건들진 않았고 스킬계수쪽만 수정했습니다!
//나머진 똑같이 내용만 바꿔서 적어놨습니다
//특화 스탯이 따로 정해진게 없어서 이 스탯기준으로 그냥 지피티한테 물어봐서 나온걸 주석으로 한번 적어놓겠습니다!보시고 특화스탯 한번 수정해주세요!
//특화 스탯(SNE) 의미:"말빨의 깊이 / 주둥아리술의 연륜"
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

JYJ::JYJ(const std::string& name)
    : Player(name)
{
    job = "풍둔 주둥아리술 마스터";

    skill1Name = "블루투스식 말하기";
    skill2Name = "전방에 힘찬 기지개 발사";
    skill3Name = "숨쉬듯 무례하기";
    groggyAttackName = "그로기 공격 이름";

    //방깎 수치, 버프 스킬로 조정됨
    defenceDecreaseValue = 0.00f;

    Set_Start_Stat(
        999, // HP
        999, // MP
        999,  // ATK
        999, // DEF
        100, // AP
        3,   // SNE
        5,  // AGI
        180, //MAXHP
        90 //MAXMP
    );
}

void JYJ::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }


    if (!Check_Hit(monster))
    {
        Print_Miss_Message();
        return;
    }

    // [기본 공격]: 공격력 90% + 민첩성(AGI) 10% (주둥아리술을 시전하며 가볍게 툭 치는 평타 컨셉)
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
    Print_Bright_Dialogue("평타 대사 입력\n");
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

void JYJ::Skill1(Monster* monster)
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

    // [스킬 1 - 블루투스식 말하기]: 소리가 보이지 않게 날렵하게 파고드는 컨셉 (공격력 100% + 민첩성 AGI 30%)
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
    Print_Bright_Dialogue(name + " : 뭔말알?\n");
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

void JYJ::Skill2(Monster* monster)
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

    // [스킬 2 - 전방에 힘찬 기지개 발사]: 기지개를 켜며 온몸의 생명력을 뿜어내는 컨셉 (공격력 120% + 체력 HP 20%)
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
    Print_Bright_Dialogue("메챠쿠챠 카멜레온!\n");
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

//void JYJ::Skill3(Monster* monster)
//{
//    const int mpCost = 30;
//
//    if (monster == nullptr)
//    {
//        std::cout << "스킬을 사용할 대상이 없습니다.\n";
//        return;
//    }
//
//    if (mp < mpCost)
//    {
//        std::cout << "MP가 부족합니다.\n";
//        return;
//    }
//
//    mp -= mpCost;
//
//    // [스킬 3 - 숨쉬듯 무례하기]: 참을 수 없는 무례함으로 마나를 폭발시키는 주력기 컨셉 (공격력 150% + 마나 MP 30%)
//    int damage = Calculate_Damage(
//        1.5f, 0.0f, 0.0f, // ATK 150%
//        0.3f, 0.0f, 0.0f, // MP 30%
//        monster->getDefence()
//    );
//
//    Apply_Damage(monster, damage);
//
//    std::cout << name << "의 " << skill3Name << "!\n";
//    std::cout << "커피 타오십시오.\n";
//    std::cout << damage << "의 피해를 입혔습니다.\n";
//}

void JYJ::Skill3(Monster* monster)
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

    // 현재 캐릭터의 방어력 감소 수치
    defenceDecreaseValue = 0.2f;

    Stat_Modifier modifier;

    modifier.id = "DEFENCE_DECREASE_BUFF";
    modifier.name = "적 방어력 20% 감소";
    modifier.type = Stat_Modifier_Type::Buff;
    modifier.remainingTurns = 3;

    // 같은 방깎 효과가 이미 있다면 제거 후 재등록
    Remove_Stat_Modifier("DEFENCE_DECREASE_BUFF");
    Add_Stat_Modifier(modifier);

    std::cout << name << "의 " << skill3Name << "!\n";
    Print_Bright_Dialogue(name + " : 커피 타오십시오.\n");
    std::cout << "3턴 동안 적의 방어력을 20% 낮췄다!\n";

    // 버프 적용 결과를 확인할 수 있도록 1초 대기
    Sleep(1000);
}

void JYJ::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [그로기 공격 - 그로기 공격 이름]: 묵직한 방어력으로 상대를 짓누르는 치명타 컨셉 (공격력 180% + 방어력 DEF 40%)
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
    Print_Bright_Dialogue("그로기 공격 대사 입력\n");
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

//방깎 스킬 사용 예시
//// 현재 캐릭터의 방어력 감소 수치
////defenceDecreaseValue = 0.nnf;
//
//Stat_Modifier modifier;
//
//modifier.id = "DEFENCE_DECREASE_BUFF";
//modifier.name = "적 방어력 n% 관통";
//modifier.type = Stat_Modifier_Type::Buff;
//modifier.remainingTurns = 3;
//
//// 같은 방깎 효과가 이미 있다면 제거 후 재등록
//Remove_Stat_Modifier("DEFENCE_DECREASE_BUFF");
//Add_Stat_Modifier(modifier);
//
//std::cout << name << "의 " << skill1Name << "!\n";
//std::cout << name << " : 스킬 대사\n";
//std::cout << "n턴 동안 방어력 관통 n% 효과를 획득했다!.\n";
//

//치명타 버프 예시
//void JYJ::Skill2(Monster* monster)
//{
//    const int mpCost = 20;
//
//    if (mp < mpCost)
//    {
//        std::cout << "MP가 부족합니다.\n";
//        return;
//    }
//
//    mp -= mpCost;
//
//    // 현재 적용할 치명타 확률 증가량
//    criticalBuffValue = 20.0f;
//
//    Stat_Modifier modifier;
//
//    modifier.id = "CRITICAL_CHANCE_BUFF";
//    modifier.name = "치명타 확률 20% 증가";
//    modifier.type = Stat_Modifier_Type::Buff;
//    modifier.remainingTurns = 3;
//
//    Remove_Stat_Modifier("CRITICAL_CHANCE_BUFF");
//    Add_Stat_Modifier(modifier);
//
//    std::cout << name << "의 " << skill2Name << "!\n";
//    std::cout << "3턴 동안 치명타 확률이 20% 증가합니다.\n";
//}
