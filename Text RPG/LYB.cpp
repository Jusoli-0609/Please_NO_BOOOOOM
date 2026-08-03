#include <iostream>
#include "LYB.h"
#include "Monster.h"
//그로기 이름 따로 안적혀있어서 일단 특수능력중에 음침하게 염탐하기(약점찾기) 를 그로기쪽에 적어놨습니다!
//나머진 똑같이 내용만 바꿔서 적어놨습니다
//특화 스탯이 따로 정해진게 없어서 이 스탯기준으로 그냥 지피티한테 물어봐서 나온걸 주석으로 한번 적어놓겠습니다!보시고 특화스탯 한번 수정해주세요!
//특화 스탯(SNE) 의미: "동물 조련 능력 / 집사만의 교감 수치"
namespace
{
    void Apply_Damage(Monster* monster, int damage)
    {
        monster->setHP(monster->getHP() - damage);
    }
}

LYB::LYB(const std::string& name)
    : Player(name)
{
    job = "고양이 집사(동물테이머)";

    skill1Name = "랜선 물어뜯기(상대 1턴 강제 넘기기)";
    skill2Name = "고양이 애교(버프 : 상대 공격 1회 회피)";
    skill3Name = "츄르 바르기(강공격)";
    groggyAttackName = "자동차 고장(이동 능력 감소시키기)";


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

void LYB::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [기본 공격]: 공격력 90% + 민첩성(AGI) 10% (고양이를 쫓아 날렵하게 움직이는 평타 컨셉)
    int damage = Calculate_Damage(
        0.9f, // ATK 90%
        0.0f, // DEF 0%
        0.0f, // HP 0%
        0.0f, // MP 0%
        0.0f, // SNE 0%
        0.1f, // AGI 10%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 기본 공격!\n";
    std::cout << "오 잠시만요 고양이가...\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void LYB::Skill1(Monster* monster)
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

    // [스킬 1 - 랜선 물어뜯기]: 재빠르게 뛰어들어 방해하는 민첩한 컨셉 (AGI 30% 가미)
    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f, // ATK 100%
        0.0f, 0.0f, 0.3f, // AGI 30%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의" << skill1Name << "!\n";
    std::cout << name << " : " << "메에\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void LYB::Skill2(Monster* monster)
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

    // [스킬 2 - 고양이 애교]: 집사의 고양이한테서 우러나오는 치명적 애교 컨셉 (HP 20% 가미)
    int damage = Calculate_Damage(
        1.2f, 0.0f, 0.2f, // ATK 120%, HP 20%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill2Name << "!\n";
    std::cout << "냐옹이다옹\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void LYB::Skill3(Monster* monster)
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

    // [스킬 3 - 츄르 바르기]: 마나를 집중해 강력한 한 방을 터뜨리는 주력 강공격 (MP 30% 가미)
    int damage = Calculate_Damage(
        1.5f, 0.0f, 0.0f, // ATK 150%
        0.3f, 0.0f, 0.0f, // MP 30%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill3Name << "!\n";
    std::cout << "제가 원인을 찾은 것 같습니다.\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void LYB::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [그로기 공격 - 자동차 고장]: 묵직한 방어력을 실어 상대를 완전히 멈춰 세우는 치명타 (DEF 40% 가미)
    int damage = Calculate_Damage(
        1.8f, 0.4f, 0.0f, // ATK 180%, DEF 40%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << groggyAttackName << "!\n";
    std::cout << "자동차 고장(이동 능력 감소시키기)\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}