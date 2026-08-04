#include <iostream>
#include "JSR.h"
#include "Monster.h"
//대사 groggyAttackName
//그로기 이름 따로 안적혀있어서 일단 특수능력중에 음침하게 염탐하기(약점찾기) 를 그로기쪽에 적어놨습니다!
//나머진 똑같이 내용만 바꿔서 적어놨습니다
//특화 스탯이 따로 정해진게 없어서 이 스탯기준으로 그냥 지피티한테 물어봐서 나온걸 주석으로 한번 적어놓겠습니다!보시고 특화스탯 한번 수정해주세요!
//특화 스탯(SNE) 의미: "교주로서의 음침함 / 신도들을 홀리는 기운"
namespace
{
    void Apply_Damage(Monster* monster, int damage)
    {
        monster->setHP(monster->getHP() - damage);
    }
}

JSR::JSR(const std::string& name)
    : Player(name)
{
    job = "소리교 교주";

    skill1Name = "찬양단 동원(주사위 굴리기)";
    skill2Name = "그림으로 정신공격하기";
    skill3Name = "복음 전파하기";
    groggyAttackName = "음침하게 염탐하기(약점 찾기)";


    Set_Start_Stat(
        200, // HP
        100, // MP
        30,  // ATK
        10,  // DEF
        100, // AP
        5,   // SNE
        10,  // AGI
        200, //MAXHP
        100 //MAXMP
    );
}

void JSR::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }
    // 공격력 90으로 낮추고 컨셉에 맞게 음침함(SNE) 10% 설정했습니다.
    int damage = Calculate_Damage(
        0.9f, // ATK 90%
        0.0f, // DEF 0%
        0.0f, // HP 0%
        0.0f, // MP 0%
        0.1f, // SNE 10%
        0.0f, // AGI 0%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 기본 공격!\n";
    std::cout << "안타까운 일입니다.\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JSR::Skill1(Monster* monster)
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
    // 스킬 1 찬양단 동원: 공격력 100% + 민첩성(AGI) 20% (찬양단이 날렵하게 움직이는 컨셉)
    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f, // ATK 100%
        0.0f, 0.0f, 0.2f, // AGI 20%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의" << skill1Name << "!\n";
    std::cout << name << " : " << "제가 말입니까?\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JSR::Skill2(Monster* monster)
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
    // 스킬 2 그림으로 정신공격하기: 공격력 120% + 체력(HP) 20% (정신공격으로 자신의 생명력을 실어보내는 컨셉)
    int damage = Calculate_Damage(
        1.2f, 0.0f, 0.2f, // ATK 120%, HP 20%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill2Name << "!\n";
    std::cout << "(꺽꺽꺽) 웃기\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JSR::Skill3(Monster* monster)
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
    // 스킬 3 - 복음 전파하기: 공격력 150% + 마나(MP) 30% (폭발적인 마나로 복음을 쏟아내는 주력기)
    int damage = Calculate_Damage(
        1.5f, 0.0f, 0.0f, // ATK 150%
        0.3f, 0.0f, 0.0f, // MP 30%
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << skill3Name << "!\n";
    std::cout << "저는 진실만 말합니다.\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JSR::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }
    // 그로기 공격 음침하게 염탐하기: 공격력 180% + 방어력(DEF) 40% (상대의 약점을 파고들어 묵직하게 짓누르는 치명타)
    int damage = Calculate_Damage(
        1.8f, 0.4f, 0.0f, // ATK 180%, DEF 40%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << groggyAttackName << "!\n";
    std::cout << "음침하게 염탐하기(약점 찾기)\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}