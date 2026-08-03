#include <iostream>
#include "JYJ.h"
#include "Monster.h"

namespace
{
    void Apply_Damage(Monster* monster, int damage)
    {
        monster->setHP(monster->getHP() - damage);
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


    Set_Start_Stat(
        200, // HP
        100, // MP
        30,  // ATK
        10,  // DEF
        100, // AP
        5,   // SNE
        10,   // AGI
        200, //MAXHP
        100 //MAXMP
    );
}

void JYJ::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

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
    std::cout << "평타 대사 입력\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
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

    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의" << skill1Name << "!\n";
    std::cout << name << " : " << "뭔말알?\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
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

    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill2Name << "!\n";
    std::cout << "메챠쿠챠 카멜레온!\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JYJ::Skill3(Monster* monster)
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

    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill3Name << "!\n";
    std::cout << "커피 타오십시오.\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JYJ::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << groggyAttackName << "!\n";
    std::cout << "그로기 공격 대사 입력\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}
