#include <iostream>
#include "JYJ.h"
#include "Monster.h"
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
        10,  // AGI
        200, // MAXHP
        100  // MAXMP
    );
}

void JYJ::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
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

    // [스킬 1 - 블루투스식 말하기]: 소리가 보이지 않게 날렵하게 파고드는 컨셉 (공격력 100% + 민첩성 AGI 30%)
    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f, // ATK 100%
        0.0f, 0.0f, 0.3f, // AGI 30%
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

    // [스킬 2 - 전방에 힘찬 기지개 발사]: 기지개를 켜며 온몸의 생명력을 뿜어내는 컨셉 (공격력 120% + 체력 HP 20%)
    int damage = Calculate_Damage(
        1.2f, 0.0f, 0.2f, // ATK 120%, HP 20%
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

    // [스킬 3 - 숨쉬듯 무례하기]: 참을 수 없는 무례함으로 마나를 폭발시키는 주력기 컨셉 (공격력 150% + 마나 MP 30%)
    int damage = Calculate_Damage(
        1.5f, 0.0f, 0.0f, // ATK 150%
        0.3f, 0.0f, 0.0f, // MP 30%
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

    // [그로기 공격 - 그로기 공격 이름]: 묵직한 방어력으로 상대를 짓누르는 치명타 컨셉 (공격력 180% + 방어력 DEF 40%)
    int damage = Calculate_Damage(
        1.8f, 0.4f, 0.0f, // ATK 180%, DEF 40%
        0.0f, 0.0f, 0.0f,
        monster->getDefence()
    );

    Apply_Damage(monster, damage);

    std::cout << name << "의 " << groggyAttackName << "!\n";
    std::cout << "그로기 공격 대사 입력\n";
    std::cout << damage << "의 피해를 입혔습니다.\n";
}