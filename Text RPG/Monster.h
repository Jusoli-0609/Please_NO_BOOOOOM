#pragma once
#include "Item.h"
#include <string>
#include <vector>

class Player;

// 1. é�� �з� ��Ʈ
enum class Chapter_Type
{
    VARIABLE_CONDITION_FOREST,
    ARRAY_LOOP_OCEAN,
    FUNCTION_RUINS,
    POINTER_MEMORY_GRAVEYARD,
    OBJECT_STL_FACTORY,
    ALL_CHAPTER_CLEARED
}; 

// 2.���� �з� ��Ʈ
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

    CODE_SNIPPET_WRAITH,

    VARIABLE_CONDITION_TUTOR,
    ARRAY_LOOP_TUTOR,
    FUNCTION_TUTOR,
    POINTER_MEMORY_TUTOR,
    OBJECT_STL_TUTOR,

    KIM_DONG_HYUN_MANAGER,
    MOON_SEUNG_HO_MANAGER
};

// 3.���� ��� �з� ��Ʈ
enum class Monster_Grade
{
    NORMAL,
    ELITE,
    TUTOR,
    FINAL_BOSS
};

// 4. ���� �ɷ�ġ �ε��� ��Ʈ
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
    // 5. ���� ���� �� �ʱ�ȭ ��Ʈ
    Monster(); // 5-1. �⺻ ���� ������
    Monster(Monster_Type monster_Type); // 5-2. ���� Ÿ�� ���� ������
    Monster  // 5-3. �ܺ� ������ �Է� ������
    (
        std::string monster_Name,
        int monster_HP,
        int monster_Power,
        int monster_Defence,
        std::string drop_Item_Name,
        int drop_Item_Price
    );

    void Initialize_Elite_Monster(Chapter_Type chapter_Type); // 5-4. ���� ���� �ʱ�ȭ
    void Initialize_Tutor_Monster(Chapter_Type chapter_Type); // 5-5. Ʃ�� ���� �ʱ�ȭ
	void Initialize_Final_Boss(Monster_Type final_Boss_Type); // 5-6. ���� ���� �ʱ�ȭ
    void Apply_Player_Level_Scaling(int player_Level); // 5-7. �÷��̾� ���� ��� �ɷ�ġ ����

    // 6. ���� �⺻ ���� ��ȸ ��Ʈ
    std::string getName() const; // 6-1. ���� �̸� ��ȸ
    int getHP() const; // 6-2. ���� HP ��ȸ
    int getPower() const; // 6-3. ���� ���ݷ� ��ȸ
    int getDefence() const; // 6-4. ���� ���� ��ȸ
    int getSpeed() const; // 6-5. ���� ���ǵ� ��ȸ
    int getEvasion() const; // 6-6. ���� ȸ���� ��ȸ
    int getAccuracy() const; // 6-7. ���� ���߷� ��
    int getMonsterLevel() const; // 6-8. ���� ���� ��ȸ
    Monster_Type getMonsterType() const; // 6-9. ���� Ÿ�� ��ȸ
    Chapter_Type getChapterType() const; // 6-10. ���� �Ҽ� é�� ��ȸ
    Monster_Grade getMonsterGrade() const; // 6-11. ���� ��� ��ȸ
    std::string getAttackMessage() const; // 6-12. ���� ���� ��� ��ȸ
     
    // 7. ���� ���� ���� ��ȸ ��Ʈ
    int getExpReward() const;  // 7-1. ����ġ ���� ��ȸ
    int getScoreReward() const; // 7-2. ���� ���� ��ȸ
    std::string getDropItemName() const;  // 7-3. ��� ������ ��� �̸� ��ȸ
    int getDropItemPrice() const; // 7-4. ��� ������ ���� �հ� ��ȸ
    int getDropItemCount() const; // 7-5. ��� ������ ���� �հ� ��ȸ
    const std::vector<Item>& getDropItems() const; // 7-6. ��� ������ ��� ��ȸ
    int getGoldReward() const; // 7-7. �Ʒ������ ��ȸ

    // 8. ���� ���� ���� �� ���� ��Ʈ
    void setMonsterGrade(Monster_Grade monster_Grade); // 8-1. ���� ��� ����
    void setHP(int hp); // 8-2. ���� HP ����
    void attack(Player* player)const; // 8-3. ���� ���� ó�� 

    // 9. ���� ��� �� ���� ���� ��Ʈ
    void Print_Attack_Message() const; // 9-1. ���� ���� ��� ���
    void Print_Monster_Info() const; // 9-2. ���� ��ü ���� ���
    void Generate_Drop_Reward(); // 9-3. ��� �����۰� ���� ���
    void Print_Drop_Reward() const; // 9-4. �����ۺ� ���� ���� ��� ����

private:
    // 10. ���� ���� �ʱ�ȭ ��Ʈ
    void Initialize_Monster(Monster_Type monster_Type); // 10-1. �Ϲ� ���� ���� �ʱ�ȭ

    // 11. ���� ���� ��� ��Ʈ 
    int Get_Chapter_Number() const; // 11-1. é�� ��ȣ ��ȯ
    int Generate_Random_Level() const; // 11-2. é�ͺ� ���� ���� ����
    void Apply_Level_Bonus(); // 11-3. ���� ���� ���ʽ� ����

    // 10. ���� ���� ��� ��Ʈ
    std::string Get_Code_Fragment_Name() const; // 12-1. é�ͺ� �ڵ� ���� �̸� ����
    int Calculate_Exp_Reward() const; // 12-2. é�ͺ� �⺻ ����ġ ���
    int Calculate_Level_Exp_Bonus() const; // 12-3. ���� ���� ����ġ ���ʽ� ���
    int Calculate_Score_Reward() const; // 12-4. é�ͺ� ���� ���
    int Calculate_Gold_Reward() const; // 12-5. �Ʒ������ ���� ���

    // 11. ���� �⺻ ������ ��Ʈ
    Monster_Type _monster_Type;
    Chapter_Type _chapter_Type;
    Monster_Grade _monster_Grade;
    int _monster_Level;

    std::string _monster_Name;
    int _stat[MONSTER_STAT_COUNT];

    // 12. ���� ���� �� �⺻ ���� ������ ��Ʈ
    int _evasion;
    int _accuracy;
    int _exp_Reward;
    int _score_Reward;

    std::string _attack_Message;

    // 13. ���� ��� ���� ������ ��Ʈ
    std::string _drop_Item_Name;
    int _drop_Item_Price;
    int _drop_Item_Count;
    int _gold_Reward;

    std::vector<Item> _drop_Items;
};