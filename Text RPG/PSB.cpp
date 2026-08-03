#include <iostream>
#include "PSB.h"
#include "Monster.h"
//그로기 이름 따로 안적혀있어서 일단 특수능력중에 음침하게 염탐하기(약점찾기) 를 그로기쪽에 적어놨습니다!
//나머진 똑같이 내용만 바꿔서 적어놨습니다
//특화 스탯이 따로 정해진게 없어서 이 스탯기준으로 그냥 지피티한테 물어봐서 나온걸 주석으로 한번 적어놓겠습니다!보시고 특화스탯 한번 수정해주세요!
//특화 스탯(SNE) 의미:"대장으로서의 은밀한 카리스마 / 여유"
namespace
{
    void Apply_Damage(Monster* monster, int damage)
    {
        monster->setHP(monster->getHP() - damage);
    }
}

PSB::PSB(const std::string& name)
    : Player(name)
{
    job = "도둑대장(전사)";

    skill1Name = "허탈하게 웃기";
    skill2Name = "ㄷㄷ";
    skill3Name = "겸허히 받아들이기";
    groggyAttackName = "No Signal(명상, HP회복)";


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

void PSB::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [기본 공격]: 순수 공격력 100% (도둑대장의 기조를 보여주는 가장 담백한 평타)
    int damage = Calculate_Damage(
        1.0f, // ATK 100%
        0.0f, // DEF 0%
        0.0f, // HP 0%
        0.0f, // MP 0%
        0.0f, // SNE 0%
        0.0f, // AGI 0%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 기본 공격!\n";
    std::cout << "허허허...\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void PSB::Skill1(Monster* monster)
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

    // [스킬 1 - 허탈하게 웃기]: 방심한 틈을 타 날렵하게 치고 빠지는 컨셉 (공격력 90% + 민첩성 AGI 30%)
    int damage = Calculate_Damage(
        0.9f, 0.0f, 0.0f, // ATK 90%
        0.0f, 0.0f, 0.3f, // AGI 30% (날렵함 강조)
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의" << skill1Name << "!\n";
    std::cout << name << " : " << "제가 하죠?\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void PSB::Skill2(Monster* monster)
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

    // [스킬 2 - ㄷㄷ]: 압박감을 주기 위해 자신의 생명력을 은근히 짜내는 전사의 기개 컨셉 (공격력 100% + 체력 HP 20%)
    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.2f, // ATK 100%, HP 20% (체력이 높을수록 압박감이 심해짐)
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill2Name << "!\n";
    std::cout << "예에...\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void PSB::Skill3(Monster* monster)
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

    // [스킬 3 - 겸허히 받아들이기]: 마나를 깊게 끌어모아 무게감 있는 진중한 일격을 날리는 주력기 컨셉 (공격력 120% + 마나 MP 40%)
    int damage = Calculate_Damage(
        1.2f, 0.0f, 0.0f, // ATK 120%
        0.4f, 0.0f, 0.0f, // MP 40% (마나통이 클수록 묵직한 일격)
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill3Name << "!\n";
    std::cout << "커피 타오십시오.\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void PSB::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [그로기 공격 - No Signal]: 정신을 놓은 상대에게 단단한 방어의 격차를 짓누르는 치명상 컨셉 (공격력 150% + 방어력 DEF 50%)
    int damage = Calculate_Damage(
        1.5f, 0.5f, 0.0f, // ATK 150%, DEF 50% (방어력이 높을수록 찍어누르는 힘 증가)
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << groggyAttackName << "!\n";
    std::cout << "No Signal(명상, HP회복)\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}