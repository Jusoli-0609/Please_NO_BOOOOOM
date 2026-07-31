#include <iostream>
#include "Player.h"

Player::Player(const std::string& name)
    : name(name),
    job("미선택"),
    hp(200),
    mp(100),
    atk(30),
    def(0),
    ap(100),
    sne(0),
    agi(0),
    level(1),
    maxexp(100),
    exp(0)
{
}

void Player::Set_Start_Stat(
    int hp,
    int mp,
    int atk,
    int def,
    int ap,
    int sne,
    int agi
)
{
    this->hp = hp;
    this->mp = mp;
    this->atk = atk;
    this->def = def;
    this->ap = ap;
    this->sne = sne;
    this->agi = agi;
}

int Player::Calculate_Damage(
    float atkRatio,
    float defRatio,
    float hpRatio,
    float mpRatio,
    float sneRatio,
    float agiRatio,
    int targetDef
) const
{
    if (targetDef < 0)
    {
        targetDef = 0;
    }

    float damage =
        (
            atk * atkRatio
            + def * defRatio
            + hp * hpRatio
            + mp * mpRatio
            + sne * sneRatio
            + agi * agiRatio
            )
        * ap
        / (100.0f + targetDef);

    if (damage < 1.0f)
    {
        damage = 1.0f;
    }

    return static_cast<int>(damage);
}

void Player::Print_Status() const
{
    std::cout << "===========================================\n";
    std::cout << name << "의 현재 능력치\n";
    std::cout << "\nHP:  " << hp;
    std::cout << "\nMP:  " << mp;
    std::cout << "\nATK: " << atk;
    std::cout << "\nAP:  " << ap;
    std::cout << "\nDEF: " << def;
    std::cout << "\nSNE: " << sne;
    std::cout << "\nAGI: " << agi;
    std::cout << "\nLevel: " << level;
    std::cout << "\nEXP: " << exp << "/" << maxexp;
    std::cout << "\n\n===========================================\n";
}

void Player::Gain_Exp(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    exp += amount;

    std::cout << name << "이(가) " << amount
        << " 경험치를 획득했습니다.\n";

    while (exp >= maxexp && maxexp > 0)
    {
        Level_Up();
    }
}

void Player::Level_Up()
{
    if (exp < maxexp || maxexp <= 0)
    {
        return;
    }

    exp -= maxexp;
    ++level;
    maxexp = static_cast<int>(maxexp * 1.5f);

    hp += 20;
    mp += 10;
    atk += 5;
    def += 3;

    std::cout << name << "이(가) 레벨업!\n";
    std::cout << "현재 레벨: " << level << '\n';

    Print_Status();
}

std::string Player::Get_Name() const { return name; }
std::string Player::Get_Job() const { return job; }
int Player::Get_Level() const { return level; }
int Player::Get_Hp() const { return hp; }
int Player::Get_Mp() const { return mp; }
int Player::Get_ATK() const { return atk; }
int Player::Get_DEF() const { return def; }
int Player::Get_AP() const { return ap; }
int Player::Get_SNE() const { return sne; }
int Player::Get_AGI() const { return agi; }
int Player::Get_Exp() const { return exp; }
int Player::Get_MaxExp() const { return maxexp; }

void Player::Set_Hp(int value) { hp = value < 0 ? 0 : value; }
void Player::Set_Mp(int value) { mp = value < 0 ? 0 : value; }
void Player::Set_ATK(int value) { atk = value; }
void Player::Set_DEF(int value) { def = value; }
void Player::Set_AP(int value) { ap = value; }
void Player::Set_SNE(int value) { sne = value; }
void Player::Set_AGI(int value) { agi = value; }
void Player::Set_Level(int value) { level = value < 1 ? 1 : value; }
void Player::Set_Exp(int value) { exp = value < 0 ? 0 : value; }
void Player::Set_MaxExp(int value) { maxexp = value < 1 ? 1 : value; }

std::string Player::getName() const { return Get_Name(); }
std::string Player::getJob() const { return Get_Job(); }
int Player::getLevel() const { return Get_Level(); }
int Player::getHp() const { return Get_Hp(); }
int Player::getHP() const { return Get_Hp(); }
int Player::getMp() const { return Get_Mp(); }
int Player::getMP() const { return Get_Mp(); }
int Player::getPower() const { return Get_ATK(); }
int Player::getAtk() const { return Get_ATK(); }
int Player::getDefence() const { return Get_DEF(); }
int Player::getDef() const { return Get_DEF(); }
int Player::getAp() const { return Get_AP(); }
int Player::getSne() const { return Get_SNE(); }
int Player::getAgi() const { return Get_AGI(); }
int Player::getExp() const { return Get_Exp(); }
int Player::getMaxExp() const { return Get_MaxExp(); }

void Player::setHp(int value) { Set_Hp(value); }
void Player::setHP(int value) { Set_Hp(value); }
void Player::setMp(int value) { Set_Mp(value); }
void Player::setMP(int value) { Set_Mp(value); }
void Player::setPower(int value) { Set_ATK(value); }
void Player::setAtk(int value) { Set_ATK(value); }
void Player::setDefence(int value) { Set_DEF(value); }
void Player::setDef(int value) { Set_DEF(value); }
void Player::setAp(int value) { Set_AP(value); }
void Player::setSne(int value) { Set_SNE(value); }
void Player::setAgi(int value) { Set_AGI(value); }
void Player::setLevel(int value) { Set_Level(value); }
void Player::setExp(int value) { Set_Exp(value); }
void Player::setMaxExp(int value) { Set_MaxExp(value); }
