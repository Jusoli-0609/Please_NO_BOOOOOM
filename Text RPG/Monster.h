#pragma once
#include <string>

class Player;

enum class Chapter_Type
{
    VARIABLE_CONDITION_FOREST,
    ARRAY_LOOP_OCEAN,
    FUNCTION_RUINS,
    POINTER_MEMORY_GRAVEYARD,
    OBJECT_STL_FACTORY,
    ALL_CHAPTER_CLEARED
};

enum class Monster_Type
{
    INT_SLIME,
    BOOL_MUSHROOM,
    IF_GOBLIN,

    ARRAY_JELLYFISH,
    FOR_SHARK,
    WHILE_WHALE,

    PARAMETER_GIANT_FLY,
    RETURN_GARGOYLE,
    FUNCTION_MAGE,

    POINTER_GHOST,
    NULL_BANSHEE,
    MEMORY_REAPER,

    CLASS_MACHINE_DOLL,
    INHERITANCE_CHIMERA,
    VECTOR_DRONE,

    CODE_SNIPPET_WRAITH
};

enum class Monster_Grade
{
    NORMAL,
    ELITE,
    TUTODBR,
    FINAL_BOSS
};

enum Monster_Stat_Index
{
    MONSTER_HP,
    MONSTER_MP,
    MONSTER_POWER,
    MONSTER_DEFENCE,
    MONSTER_SPEED,
    MONSTER_STAT_COUNT
};

class Monster
{
public:
    Monster();
    Monster(Monster_Type monster_Type);

    void Initialize_Elite_Monster
    (Chapter_Type chapter_Type);
    Monster
    (
        std::string monster_Name,
        int monster_HP,
        int monster_Power,
        int monster_Defence,
        std::string drop_Item_Name,
        int drop_Item_Price
    );

    std::string getName() const;

    int getHP() const;
    int getPower() const;
    int getDefence() const;;
    int getSpeed() const;
    int getEvasion() const;
    int getAccuracy() const;
    int getExpReward() const;
    int getScoreReward() const;
    int getMonsterLevel() const;

    std::string getDropItemName() const;
    int getDropItemPrice() const;
    int getDropItemCount() const;
    int getGoldReward() const;

    Monster_Type getMonsterType() const;
    Chapter_Type getChapterType() const;

    Monster_Grade getMonsterGrade() const;

    void setMonsterGrade(Monster_Grade monster_Grade);

    std::string getAttackMessage() const;

    void setHP(int hp);
    void attack(Player* player)const;
    void Print_Monster_Info() const;
    void Print_Attack_Message() const;
    void Generate_Drop_Reward();

private:
    void Initialize_Monster(Monster_Type monster_Type);

    std::string Get_Code_Fragment_Name() const;

    int Get_Chapter_Number() const;
    int Generate_Random_Level() const;

    void Apply_Level_Bonus();

    int Calculate_Exp_Reward() const;
    int Calculate_Level_Exp_Bonus() const;
    int Calculate_Score_Reward() const;
    int Calculate_Gold_Reward() const;

    Monster_Type _monster_Type;
    Chapter_Type _chapter_Type;
    Monster_Grade _monster_Grade;
    int _monster_Level;

    std::string _monster_Name;
    int _stat[MONSTER_STAT_COUNT];
    int _evasion;
    int _accuracy;
    int _exp_Reward;
    int _score_Reward;

    std::string _attack_Message;

    std::string _drop_Item_Name;
    int _drop_Item_Price;
    int _drop_Item_Count;
    int _gold_Reward;
};