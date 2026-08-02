#pragma once
#include <string>

class Monster;

class Player
{
protected:
    std::string name;
    std::string job;

    int hp;
    int mp;
    int atk;
    int def;
    int ap;
    int sne;
    int agi;
    int maxhp;
    int maxmp;

    int level;
    int maxexp;
    int exp;

    void Set_Start_Stat(
        int hp,
        int mp,
        int atk,
        int def,
        int ap,
        int sne,
        int agi,
        int maxhp,
        int maxmp
    );


public:
    Player(const std::string& name);
    virtual ~Player() {}

    virtual void Attack(Monster* monster) = 0;
    virtual void Skill1(Monster* monster) = 0;
    virtual void Skill2(Monster* monster) = 0;
    virtual void Skill3(Monster* monster) = 0;
    virtual void Groggy_Attack(Monster* monster) = 0;

    void Print_Status() const;

    int Calculate_Damage(
        float atkRatio,
        float defRatio,
        float hpRatio,
        float mpRatio,
        float sneRatio,
        float agiRatio,
        int targetDef
    ) const;


    std::string Get_Name() const;
    std::string Get_Job() const;

    int Get_Level() const;
    int Get_Hp() const;
    int Get_Mp() const;
    int Get_ATK() const;
    int Get_DEF() const;
    int Get_AP() const;
    int Get_SNE() const;
    int Get_AGI() const;
    int Get_Exp() const;
    int Get_MaxExp() const;
    int GetMaxHP() const;
    int GetMaxMP() const;
    int GetPower() const;
    int GetHP() const;

    void SetHP(int hp);
    void SetMaxHP(int maxHp);
    void SetMaxMP(int maxMp);
    void Set_Hp(int hp);
    void Set_Mp(int mp);
    void Set_ATK(int atk);
    void Set_DEF(int def);
    void Set_AP(int ap);
    void Set_SNE(int sne);
    void Set_AGI(int agi);
    void Set_Level(int level);
    void Set_Exp(int exp);
    void Set_MaxExp(int maxexp);
    void SetPower(int atk);
    void Gain_Exp(int amount);
    void Level_Up();

    // Battle_System 및 기존 조원 코드 호환용 함수
    std::string getName() const;
    std::string getJob() const;

    int getLevel() const;
    int getHp() const;
    int getHP() const;
    int getMp() const;
    int getMP() const;
    int getPower() const;
    int getAtk() const;
    int getDefence() const;
    int getDef() const;
    int getAp() const;
    int getSne() const;
    int getAgi() const;
    int getExp() const;
    int getMaxExp() const;

    void setHp(int hp);
    void setHP(int hp);
    void setMp(int mp);
    void setMP(int mp);
    void setPower(int atk);
    void setAtk(int atk);
    void setDefence(int def);
    void setDef(int def);
    void setAp(int ap);
    void setSne(int sne);
    void setAgi(int agi);
    void setLevel(int level);
    void setExp(int exp);
    void setMaxExp(int maxexp);
};
