#include <iostream>
#include "JWH.h"
#include "Monster.h"
//대사 groggyAttackName
//그로기 이름 따로 안적혀있어서 똑같이 특수능력에 있는거 하나 적어놨습니다!
//나머진 똑같이 내용만 바꿔서 적어놨습니다
//특화 스탯이 따로 정해진게 없어서 이 스탯기준으로 그냥 지피티한테 물어봐서 나온걸 주석으로 한번 적어놓겠습니다!보시고 특화스탯 한번 수정해주세요!
//특화 스탯(SNE) 의미:"은밀함 / 도둑질 수치"
namespace
{
    void Apply_Damage(Monster* monster, int damage)
    {
        monster->setHP(monster->getHP() - damage);
    }
}

JWH::JWH(const std::string& name)
    : Player(name)
{
    job = "Grand Theif Academy(도둑)";

    skill1Name = "도적이 되기엔 정직한 양심";
    skill2Name = "낚아채기";
    skill3Name = "소리없이 다니기";
    groggyAttackName = "베어가르기";


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

void JWH::Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [기본 공격]: 공격력 90% + 특화스탯(SNE) 10% 은밀하게 툭 치기 컨셉
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        std::cout << "공격이 빗나갔습니다!\n";
        return;
    }

    int damage = Calculate_Damage(
        0.9f, // ATK 90%
        0.0f, // DEF 0%
        0.0f, // HP 0%
        0.0f, // MP 0%
        0.1f, // SNE 10%
        0.0f, // AGI 0%
        monster->getDefence()
    );

    std::cout << name << "의 기본 공격!\n";
    std::cout << "...제가 그랬나?\n";
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    Apply_Damage(monster, damage);

    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JWH::Skill1(Monster* monster)
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

    // [스킬 1 - 도적이 되기엔 정직한 양심]: 공격력 100% + 민첩성(AGI) 20% (날렵한 움직임)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        std::cout << "공격이 빗나갔습니다!\n";
        return;
    }

    int damage = Calculate_Damage(
        1.0f, 0.0f, 0.0f, // ATK 100%
        0.0f, 0.0f, 0.2f, // AGI 20%
        monster->getDefence()
    );

    std::cout << name << "의" << skill1Name << "!\n";
    std::cout << name << " : " << "해보겠습니다.\n";
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    Apply_Damage(monster, damage);

    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JWH::Skill2(Monster* monster)
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

    // [스킬 2 - 낚아채기]: 공격력 120% + 특화스탯(SNE) 30% (재빠르게 채가는 도둑질 컨셉)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        std::cout << "공격이 빗나갔습니다!\n";
        return;
    }

    int damage = Calculate_Damage(
        1.2f, 0.0f, 0.0f, // ATK 120%
        0.0f, 0.3f, 0.0f, // SNE 30%
        monster->getDefence()
    );

    std::cout << name << "의 " << skill2Name << "!\n";
    std::cout << "어디까지 하셨나요?\n";
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    Apply_Damage(monster, damage);

    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JWH::Skill3(Monster* monster)
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

    // [스킬 3 - 소리없이 다니기]: 공격력 150% + 마나(MP) 비례 30% (은밀함을 극대화하는 주력기)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        std::cout << "공격이 빗나갔습니다!\n";
        return;
    }

    int damage = Calculate_Damage(
        1.5f, 0.0f, 0.0f, // ATK 150%
        0.3f, 0.0f, 0.0f, // MP 30%
        monster->getDefence()
    );

    std::cout << name << "의 " << skill3Name << "!\n";
    std::cout << "크크크(웃기)\n";
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    Apply_Damage(monster, damage);

    std::cout << damage << "의 피해를 입혔습니다.\n";
}

void JWH::Groggy_Attack(Monster* monster)
{
    if (monster == nullptr)
    {
        std::cout << "공격할 대상이 없습니다.\n";
        return;
    }

    // [그로기 공격 - 베어가르기]: 공격력 180% + 민첩성(AGI) 40% (방심한 틈을 타 날렵하게 단숨에 베어버리는 치명타)
    // 명중 판정: 실패하면 데미지를 적용하지 않고 공격 종료
    if (!Check_Hit(monster))
    {
        std::cout << "공격이 빗나갔습니다!\n";
        return;
    }

    int damage = Calculate_Damage(
        1.8f, 0.0f, 0.0f, // ATK 180%
        0.0f, 0.0f, 0.4f, // AGI 40% 
        monster->getDefence()
    );

    std::cout << name << "의 " << groggyAttackName << "!\n";
    std::cout << "베어가르기\n";
    // 명중한 공격에 치명타 판정 적용
    Apply_Critical_Damage(damage);

    Apply_Damage(monster, damage);

    std::cout << damage << "의 피해를 입혔습니다.\n";
}