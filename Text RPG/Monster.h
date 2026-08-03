#pragma once
#include "Item.h"
#include <string>
#include <vector>

class Player;

// 1. 챕터 분류 파트
enum class Chapter_Type
{
    VARIABLE_CONDITION_FOREST,
    ARRAY_LOOP_OCEAN,
    FUNCTION_RUINS,
    POINTER_MEMORY_GRAVEYARD,
    OBJECT_STL_FACTORY,
    ALL_CHAPTER_CLEARED
}; 

// 2.몬스터 분류 파트
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

// 3.몬스터 등급 분류 파트
enum class Monster_Grade
{
    NORMAL,
    ELITE,
    TUTOR,
    FINAL_BOSS
};

// 4. 몬스터 능력치 인덱스 파트
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
    // 5. 몬스터 생성 및 초기화 파트
    Monster(); // 5-1. 기본 몬스터 생성자
    Monster(Monster_Type monster_Type); // 5-2. 몬스터 타입 지정 생성자
    Monster  // 5-3. 외부 데이터 입력 생성자
    (
        std::string monster_Name,
        int monster_HP,
        int monster_Power,
        int monster_Defence,
        std::string drop_Item_Name,
        int drop_Item_Price
    );

    void Initialize_Elite_Monster(Chapter_Type chapter_Type); // 5-4. 정예 몬스터 초기화
    void Initialize_Tutor_Monster(Chapter_Type chapter_Type); // 5-5. 튜터 몬스터 초기화
	void Initialize_Final_Boss(Monster_Type final_Boss_Type); // 5-6. 최종 보스 초기화
    void Apply_Player_Level_Scaling(int player_Level); // 5-7. 플레이어 레벨 비례 능력치 증가

    // 6. 몬스터 기본 정보 조회 파트
    std::string getName() const; // 6-1. 몬스터 이름 조회
    int getHP() const; // 6-2. 몬스터 HP 조회
    int getPower() const; // 6-3. 몬스터 공격력 조회
    int getDefence() const; // 6-4. 몬스터 방어력 조회
    int getSpeed() const; // 6-5. 몬스터 스피드 조회
    int getEvasion() const; // 6-6. 몬스터 회피율 조회
    int getAccuracy() const; // 6-7. 몬스터 명중률 조
    int getMonsterLevel() const; // 6-8. 몬스터 레벨 조회
    Monster_Type getMonsterType() const; // 6-9. 몬스터 타입 조회
    Chapter_Type getChapterType() const; // 6-10. 몬스터 소속 챕터 조회
    Monster_Grade getMonsterGrade() const; // 6-11. 몬스터 등급 조회
    std::string getAttackMessage() const; // 6-12. 몬스터 공격 대사 조회
     
    // 7. 몬스터 보상 정보 조회 파트
    int getExpReward() const;  // 7-1. 경험치 보상 조회
    int getScoreReward() const; // 7-2. 점수 보상 조회
    std::string getDropItemName() const;  // 7-3. 드롭 아이템 요약 이름 조회
    int getDropItemPrice() const; // 7-4. 드롭 아이템 가격 합계 조회
    int getDropItemCount() const; // 7-5. 드롭 아이템 수량 합계 조회
    const std::vector<Item>& getDropItems() const; // 7-6. 드롭 아이템 목록 조회
    int getGoldReward() const; // 7-7. 훈련장려금 조회

    // 8. 몬스터 상태 변경 및 전투 파트
    void setMonsterGrade(Monster_Grade monster_Grade); // 8-1. 몬스터 등급 변경
    void setHP(int hp); // 8-2. 몬스터 HP 변경
    void attack(Player* player)const; // 8-3. 몬스터 공격 처리 

    // 9. 몬스터 출력 및 보상 생성 파트
    void Print_Attack_Message() const; // 9-1. 몬스터 공격 대사 출력
    void Print_Monster_Info() const; // 9-2. 몬스터 전체 정보 출력
    void Generate_Drop_Reward(); // 9-3. 드롭 아이템과 무게 출력
    void Print_Drop_Reward() const; // 9-4. 아이템별 독립 랜덤 드롭 생성

private:
    // 10. 내부 몬스터 초기화 파트
    void Initialize_Monster(Monster_Type monster_Type); // 10-1. 일반 몬스터 정보 초기화

    // 11. 몬스터 레벨 계산 파트 
    int Get_Chapter_Number() const; // 11-1. 챕터 번호 변환
    int Generate_Random_Level() const; // 11-2. 챕터별 랜덤 레벨 생성
    void Apply_Level_Bonus(); // 11-3. 랜덤 레벨 보너스 적용

    // 10. 몬스터 보상 계산 파트
    std::string Get_Code_Fragment_Name() const; // 12-1. 챕터별 코드 조각 이름 결정
    int Calculate_Exp_Reward() const; // 12-2. 챕터별 기본 경험치 계산
    int Calculate_Level_Exp_Bonus() const; // 12-3. 랜덤 레벨 경험치 보너스 계산
    int Calculate_Score_Reward() const; // 12-4. 챕터별 점수 계산
    int Calculate_Gold_Reward() const; // 12-5. 훈련장려금 랜덤 계산

    // 11. 몬스터 기본 데이터 파트
    Monster_Type _monster_Type;
    Chapter_Type _chapter_Type;
    Monster_Grade _monster_Grade;
    int _monster_Level;

    std::string _monster_Name;
    int _stat[MONSTER_STAT_COUNT];

    // 12. 몬스터 전투 및 기본 보상 데이터 파트
    int _evasion;
    int _accuracy;
    int _exp_Reward;
    int _score_Reward;

    std::string _attack_Message;

    // 13. 몬스터 드롭 보상 데이터 파트
    std::string _drop_Item_Name;
    int _drop_Item_Price;
    int _drop_Item_Count;
    int _gold_Reward;

    std::vector<Item> _drop_Items;
};