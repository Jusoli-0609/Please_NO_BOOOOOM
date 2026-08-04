#pragma once
#include <vector>
#include "Stat_Modifier.h"
#include <string>
#include "Level_Up.h"

class Monster;
class Currently_Equipped_Equipments;
class Currently_Equipped_Tutor;

class Player
{
protected:
    std::string name;
    std::string job;
    std::string skill1Name;
    std::string skill2Name;
    std::string skill3Name;
    std::string groggyAttackName;
    Level_Up levelUp;

    int hp;
    int mp;

    int atk;
    int def;
    int ap;
    int sne;
    int agi;

    int maxhp;
    int maxmp;

    float defenceDecreaseValue = 0.0f;
    float criticalBuffValue = 0.0f;
    //명중 판정용
    bool Check_Hit(const Monster* monster) const;

    //크리티컬 판정용
    bool Check_Critical() const;
    // 실제 레벨업 처리는 Level_Up 클래스가 담당하고,
    // Player에는 상태창 표기용 레벨만 저장한다.
    int level;

    // 장비, 튜터, 일시 버프 및 디버프가 적용되기 전의 영구 스탯.
 // 레벨업이나 영약 등 영구 성장 결과는 baseStat에 반영한다.
    Stat_Value baseStat;

    // 현재 플레이어에게 적용 중인 장비, 튜터, 버프, 디버프
    std::vector<Stat_Modifier> statModifiers;

    // 기존 스탯을 baseStat에 저장했는지 확인
    bool statModifierInitialized = false;

    // 현재 Player 스탯을 기본 스탯으로 최초 저장
    void Initialize_Base_Stat();

    // 실제 스탯을 재계산
    void Recalculate_Stats();

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
    const Currently_Equipped_Equipments* currentlyEquippedEquipments;
    const Currently_Equipped_Tutor* currentlyEquippedTutor;

public:
    Player(const std::string& name);
    virtual ~Player() {}

    // 캐릭터별 전투 행동
    virtual void Attack(Monster* monster) = 0;
    virtual void Skill1(Monster* monster) = 0;
    virtual void Skill2(Monster* monster) = 0;
    virtual void Skill3(Monster* monster) = 0;
    virtual void Groggy_Attack(Monster* monster) = 0;

    std::string Get_Skill1_Name() const;
    std::string Get_Skill2_Name() const;
    std::string Get_Skill3_Name() const;
    std::string Get_Groggy_Attack_Name() const;

	// 장비와 튜터의 상태창 출력을 위해 Player 클래스에 참조를 설정
    void Set_Status_References(
        const Currently_Equipped_Equipments* equipments,
        const Currently_Equipped_Tutor* tutor
    );

    void Gain_Exp(int amount);


    // 상태 출력
// 플레이어 정보만 출력하는 기존 호환용 상태창
    void Print_Status() const;



    // 공통 데미지 계산
    int Calculate_Damage(
        float atkRatio,
        float defRatio,
        float hpRatio,
        float mpRatio,
        float sneRatio,
        float agiRatio,
        int targetDef
    ) const;

    // 효과 추가
    void Add_Stat_Modifier(const Stat_Modifier& modifier);

    // ID로 효과 제거
    bool Remove_Stat_Modifier(const std::string& id);

    // 해당 효과가 적용되어 있는지 확인
    bool Has_Stat_Modifier(const std::string& id) const;

    // 효과 정보를 가져오기
    const Stat_Modifier* Get_Stat_Modifier(
        const std::string& id
    ) const;

    // 턴이 끝났을 때 지속시간 처리
    void Process_Stat_Modifier_Turn();

    // 모든 일시 효과 제거
    void Remove_Temporary_Modifiers();

    // 특정 종류의 효과 제거
    void Remove_Modifiers_By_Type(
        Stat_Modifier_Type type
    );

    // 적용 중인 효과 출력
    void Print_Stat_Modifiers() const;

    // 기본 스탯 Getter
    int Get_Base_MaxHP() const;
    int Get_Base_MaxMP() const;

    int Get_Base_ATK() const;
    int Get_Base_DEF() const;
    int Get_Base_AP() const;
    int Get_Base_SNE() const;
    int Get_Base_AGI() const;

    // 영구 스탯 변화용 함수
    // 레벨업이나 영구 성장에서 사용
    void Add_Base_MaxHP(int value);
    void Add_Base_MaxMP(int value);

    void Add_Base_ATK(int value);
    void Add_Base_DEF(int value);
    void Add_Base_AP(int value);
    void Add_Base_SNE(int value);
    void Add_Base_AGI(int value);
    // 기본 Getter
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

    int GetMaxHP() const;
    int GetMaxMP() const;

    // 기존 코드 호환용 Getter
    int GetPower() const;
    int GetHP() const;

    int Get_Exp() const;
    int Get_Max_Exp() const;

    // 기본 Setter
    void Set_Hp(int hp);
    void Set_Mp(int mp);

    void Set_ATK(int atk);
    void Set_DEF(int def);
    void Set_AP(int ap);
    void Set_SNE(int sne);
    void Set_AGI(int agi);

    void Set_Level(int level);

    void SetMaxHP(int maxHp);
    void SetMaxMP(int maxMp);

    // 기존 코드 호환용 Setter
    void SetHP(int hp);
    void SetPower(int atk);

    // Battle_System 및 기존 조원 코드 호환용 Getter
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

    // Battle_System 및 기존 조원 코드 호환용 Setter
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
};

