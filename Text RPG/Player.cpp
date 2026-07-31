#include <iostream>
#include <string>

#include "Player.h"
#include "Level_Up.h"
#include "Player_Stat_Index.h"

using namespace std;

Player::Player(const std::string& name, const int stat[])
    : name(name),
    job("None"),
    hp(stat[P_Hp]),
    mp(stat[P_Mp]),
    atk(stat[P_ATK]),
    ap(stat[P_AP]),
    def(stat[P_DEF]),
    sne(stat[P_SNE]),
    agi(stat[P_AGI]),
    level(1),
    maxexp(100),
    exp(0)
{
}

void Player::Print_Status() const
{
    cout << "===========================================\n";
    cout << name << "의 현재 능력치\n";
    cout << "\nHP:  " << hp;
    cout << "\nMP:  " << mp;
    cout << "\nATK: " << atk;
    cout << "\nAP:  " << ap;
    cout << "\nDEF: " << def;
    cout << "\nSNE: " << sne;
    cout << "\nAGI: " << agi;
    cout << "\nLevel: " << level;
    cout << "\nEXP: " << exp << "/" << maxexp;
    cout << "\n\n===========================================\n";
}

void Player::Gain_Exp(int amount)
{
    exp += amount;

    cout << name << "이(가) " << amount
        << " 경험치를 획득했습니다.\n";

    cout << "현재 경험치: "
        << exp << "/" << maxexp << endl;

    if (exp >= maxexp)
    {
        Level_Up();
    }
}

void Player::Level_Up()
{
    if (exp < maxexp)
    {
        return;
    }

    exp -= maxexp;

    // ============================= 잠시 임시 구현====================

    level++;

    hp += 20;
    mp += 10;
    atk += 5;
    def += 3;

    maxexp = static_cast<int>(maxexp * 1.5);

    cout << name << "이(가) 레벨업!\n";
    cout << "현재 레벨: " << level << endl;

    Print_Status();
}
    //==========================================================================
std::string Player::Get_Name() const
{
    return name;
}

std::string Player::Get_Job() const
{
    return job;
}

int Player::Get_Level() const
{
    return level;
}

int Player::Get_Hp() const
{
    return hp;
}

int Player::Get_Mp() const
{
    return mp;
}

int Player::Get_ATK() const
{
    return atk;
}

int Player::Get_DEF() const
{
    return def;
}

int Player::Get_AP() const
{
    return ap;
}

int Player::Get_SNE() const
{
    return sne;
}

int Player::Get_AGI() const
{
    return agi;
}

int Player::Get_Exp() const
{
    return exp;
}

void Player::Set_Hp(int newHp)
{
    hp = newHp;
}

void Player::Set_Mp(int newMp)
{
    mp = newMp;
}

void Player::Set_ATK(int newATK)
{
    atk = newATK;
}

void Player::Set_DEF(int newDEF)
{
    def = newDEF;
}

void Player::Set_AP(int newAP)
{
    ap = newAP;
}

void Player::Set_SNE(int newSNE)
{
    sne = newSNE;
}

void Player::Set_AGI(int newAGI)
{
    agi = newAGI;
}

void Player::Set_Level(int newLevel)
{
    level = newLevel;
}

void Player::Set_Exp(int newExp)
{
    exp = newExp;
}