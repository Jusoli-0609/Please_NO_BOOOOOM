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

    int level;
    int maxexp;
    int exp;

public:
    Player(const std::string& name, const int stat[]);

    virtual ~Player() {}

    // 직업마다 구현
    virtual void attack(Monster* monster) = 0;

    //==========================
    // 기존 함수
    //==========================

    void Print_Status() const;

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

    void Set_Hp(int hp);
    void Set_Mp(int mp);
    void Set_ATK(int atk);
    void Set_DEF(int def);
    void Set_AP(int ap);
    void Set_SNE(int sne);
    void Set_AGI(int agi);
    void Set_Level(int level);
    void Set_Exp(int exp);

    void Gain_Exp(int amount);
    void Level_Up();

    //==========================
    // Battle_System 호환 함수
    //==========================

    std::string getName() const
    {
        return Get_Name();
    }

    std::string getJob() const
    {
        return Get_Job();
    }

    int getHp() const
    {
        return Get_Hp();
    }

    int getMp() const
    {
        return Get_Mp();
    }

    int getPower() const
    {
        return Get_ATK();
    }

    int getDefence() const
    {
        return Get_DEF();
    }

    int getLevel() const
    {
        return Get_Level();
    }

    void setHp(int value)
    {
        Set_Hp(value);
    }

    void setMp(int value)
    {
        Set_Mp(value);
    }

    void setPower(int value)
    {
        Set_ATK(value);
    }

    void setDefence(int value)
    {
        Set_DEF(value);
    }

    void printPlayerStatus() const
    {
        Print_Status();
    }
};