#include <iostream>
#include <algorithm>
#include <string>

#include "Player.h"
#include "Equipment.h"
#include "Tutor.h"
// 이름을 전달받아 플레이어를 생성하고 나머지 멤버를 기본값으로 초기화한다.
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
    maxhp(200),
    maxmp(100),
    level(1),
    currentlyEquippedEquipments(nullptr),
    currentlyEquippedTutor(nullptr)
{
}

void Player::Gain_Exp(int amount)
{
    levelUp.GainExp(this, amount);
}

int Player::Get_Exp() const
{
    return levelUp.GetCurrentExp();
}

int Player::Get_Max_Exp() const
{
    return levelUp.GetMaxExp();
}


// 캐릭터 생성 단계에서 최초 능력치를 설정하는 함수.
// Stat_Modifier가 적용되기 전에 한 번만 호출해야 한다.
void Player::Set_Start_Stat(
    int hp,
    int mp,
    int atk,
    int def,
    int ap,
    int sne,
    int agi,
    int maxhp,
    int maxmp
)
{
    this->hp = hp;
    this->mp = mp;

    this->atk = atk;
    this->def = def;
    this->ap = ap;
    this->sne = sne;
    this->agi = agi;

    this->maxhp = maxhp;
    this->maxmp = maxmp;

    baseStat.maxHp = maxhp;
    baseStat.maxMp = maxmp;
    baseStat.atk = atk;
    baseStat.def = def;
    baseStat.ap = ap;
    baseStat.sne = sne;
    baseStat.agi = agi;

    statModifierInitialized = true;
}
// 데미지 계산 공식, 공격력, 방어력, HP, MP, 은신, 민첩 비율을 조합하여 계산
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
    bool isDefenceDecreaseOn =
        Has_Stat_Modifier("DEFENCE_DECREASE_BUFF");

    if (isDefenceDecreaseOn)
    {
        float defenceDecreaseValue =
            Get_Defence_Decrease_Value();

        targetDef = static_cast<int>(
            targetDef * (1.0f - defenceDecreaseValue)
            );
    }

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

// 장비와 튜터의 상태창 출력을 위해 Player 클래스에 참조를 설정
void Player::Set_Status_References(
    const Currently_Equipped_Equipments* equipments,
    const Currently_Equipped_Tutor* tutor)
{
    currentlyEquippedEquipments = equipments;
    currentlyEquippedTutor = tutor;
}

void Player::Print_Status() const
{
    auto Print_Stat = [](const std::string& stat_name,
        int base_stat,
        int final_stat)
        {
            int additional_stat = final_stat - base_stat;

            std::cout
                << stat_name
                << ": "
                << final_stat
                << "  (기본 "
                << base_stat;

            if (additional_stat > 0)
            {
                std::cout << " + 추가 " << additional_stat;
            }
            else if (additional_stat < 0)
            {
                std::cout << " - 감소 " << -additional_stat;
            }
            else
            {
                std::cout << " + 추가 0";
            }

            std::cout << ")";
        };

    std::cout << "\n";
    std::cout << "================================================================================\n";
    std::cout << "                               캐릭터 정보\n";
    std::cout << "================================================================================\n";

    std::cout
        << "이름: " << name
        << "    직업: " << job
        << "    레벨: " << level
        << "    경험치: " << Get_Exp()
        << " / " << Get_Max_Exp()
        << '\n';

    std::cout
        << "HP: " << hp << " / " << maxhp
        << "    MP: " << mp << " / " << maxmp
        << '\n';

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "[능력치]\n";

    Print_Stat("MAX HP", baseStat.maxHp, maxhp);
    std::cout << "    ";
    Print_Stat("MAX MP", baseStat.maxMp, maxmp);
    std::cout << '\n';

    Print_Stat("ATK", baseStat.atk, atk);
    std::cout << "    ";
    Print_Stat("DEF", baseStat.def, def);
    std::cout << "    ";
    Print_Stat("AP", baseStat.ap, ap);
    std::cout << '\n';

    Print_Stat("SNE", baseStat.sne, sne);
    std::cout << "    ";
    Print_Stat("AGI", baseStat.agi, agi);
    std::cout << '\n';

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "[스킬]\n";

    std::cout
        << "1. " << skill1Name
        << "    2. " << skill2Name
        << '\n';

    std::cout
        << "3. " << skill3Name
        << "    그로기: " << groggyAttackName
        << '\n';

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "[장착 장비]\n";

    if (currentlyEquippedEquipments != nullptr)
    {
        currentlyEquippedEquipments
            ->Print_Currently_Equipped_Equipments();
    }
    else
    {
        std::cout << "장비 정보 없음\n";
    }

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "[튜터]\n";

    if (currentlyEquippedTutor != nullptr)
    {
        currentlyEquippedTutor
            ->Print_Currently_Equipped_Tutor();
    }
    else
    {
        std::cout << "튜터 정보 없음\n";
    }

    std::cout << "--------------------------------------------------------------------------------\n";
    std::cout << "[적용 효과]\n";

    if (statModifiers.empty())
    {
        std::cout << "없음\n";
    }
    else
    {
        int effect_count = 0;

        for (const Stat_Modifier& modifier : statModifiers)
        {
            std::cout << modifier.name;

            if (modifier.remainingTurns < 0)
            {
                std::cout << " [영구]";
            }
            else
            {
                std::cout << " [" << modifier.remainingTurns << "턴]";
            }

            effect_count++;

            if (effect_count % 2 == 0)
            {
                std::cout << '\n';
            }
            else
            {
                std::cout << "    |    ";
            }
        }

        if (effect_count % 2 != 0)
        {
            std::cout << '\n';
        }
    }

    std::cout << "================================================================================\n";
}

// 플레이어의 기본 스탯을 baseStat에 저장, 저장이 되었다면 이후에는 호출하지 않음
void Player::Initialize_Base_Stat()
{
    if (statModifierInitialized)
    {
        return;
    }

    baseStat.maxHp = maxhp;
    baseStat.maxMp = maxmp;

    baseStat.atk = atk;
    baseStat.def = def;
    baseStat.ap = ap;
    baseStat.sne = sne;
    baseStat.agi = agi;

    statModifierInitialized = true;
}
// baseStat에 모든 고정 증감값을 더한 뒤,
// 모든 퍼센트 증감값을 합산하여 최종 전투 스탯을 계산한다.
//
// 최종 스탯 = (기본 스탯 + 고정 증감값 합계)
//             * (1.0f + 비율 증감값 합계)
void Player::Recalculate_Stats()
{
    Initialize_Base_Stat();

    Stat_Value totalFlat{};
    Stat_Rate totalRate{};

    for (const Stat_Modifier& modifier : statModifiers)
    {
        totalFlat.maxHp += modifier.flat.maxHp;
        totalFlat.maxMp += modifier.flat.maxMp;

        totalFlat.atk += modifier.flat.atk;
        totalFlat.def += modifier.flat.def;
        totalFlat.ap += modifier.flat.ap;
        totalFlat.sne += modifier.flat.sne;
        totalFlat.agi += modifier.flat.agi;

        totalRate.maxHp += modifier.rate.maxHp;
        totalRate.maxMp += modifier.rate.maxMp;

        totalRate.atk += modifier.rate.atk;
        totalRate.def += modifier.rate.def;
        totalRate.ap += modifier.rate.ap;
        totalRate.sne += modifier.rate.sne;
        totalRate.agi += modifier.rate.agi;
    }

    maxhp = static_cast<int>(
        (baseStat.maxHp + totalFlat.maxHp)
        * (1.0f + totalRate.maxHp)
        );

    maxmp = static_cast<int>(
        (baseStat.maxMp + totalFlat.maxMp)
        * (1.0f + totalRate.maxMp)
        );

    atk = static_cast<int>(
        (baseStat.atk + totalFlat.atk)
        * (1.0f + totalRate.atk)
        );

    def = static_cast<int>(
        (baseStat.def + totalFlat.def)
        * (1.0f + totalRate.def)
        );

    ap = static_cast<int>(
        (baseStat.ap + totalFlat.ap)
        * (1.0f + totalRate.ap)
        );

    sne = static_cast<int>(
        (baseStat.sne + totalFlat.sne)
        * (1.0f + totalRate.sne)
        );

    agi = static_cast<int>(
        (baseStat.agi + totalFlat.agi)
        * (1.0f + totalRate.agi)
        );

    // 최종 스탯의 최소값 제한
    if (maxhp < 1)
    {
        maxhp = 1;
    }

    if (maxmp < 0)
    {
        maxmp = 0;
    }

    if (atk < 0)
    {
        atk = 0;
    }

    if (def < 0)
    {
        def = 0;
    }

    if (ap < 0)
    {
        ap = 0;
    }

    if (sne < 0)
    {
        sne = 0;
    }

    if (agi < 0)
    {
        agi = 0;
    }

    // 최대치가 낮아졌을 때 현재 HP/MP 보정
    if (hp > maxhp)
    {
        hp = maxhp;
    }

    if (mp > maxmp)
    {
        mp = maxmp;
    }
}
// ID로 효과 추가, 동일 ID가 이미 존재하면 갱신, 기본 스탯을 불러온 후 일치하는 id의 버프를
// statModifiers에서 찾아 갱신, 없으면 새로 추가, 이후 Recalculate_Stats() 호출
// 장비나 튜터의 효과도 고유 id를 가짐
void Player::Add_Stat_Modifier(
    const Stat_Modifier& modifier)
{
    Initialize_Base_Stat();

    // 동일 ID 효과가 이미 존재하면 갱신
    for (Stat_Modifier& currentModifier : statModifiers)
    {
        if (currentModifier.id == modifier.id)
        {
            currentModifier = modifier;
            Recalculate_Stats();
            return;
        }
    }

    statModifiers.push_back(modifier);

    Recalculate_Stats();
}
// ID로 효과 제거, 사용법은 Add_Stat_Modifier()와 동일
bool Player::Remove_Stat_Modifier(
    const std::string& id)
{
    for (auto it = statModifiers.begin();
        it != statModifiers.end();
        ++it)
    {
        if (it->id == id)
        {
            statModifiers.erase(it);

            Recalculate_Stats();

            return true;
        }
    }

    return false;
}
// 해당 효과가 적용되어 있는지 확인, 사용하면 id와 일치하는 효과가 statModifiers에 존재하는지 확인
// 존재하면 true, 없으면 false 반환
bool Player::Has_Stat_Modifier(
    const std::string& id) const
{
    for (const Stat_Modifier& modifier : statModifiers)
    {
        if (modifier.id == id)
        {
            return true;
        }
    }

    return false;
}
// 특정 ID의 효과를 찾으면 해당 효과의 주소를 반환한다.
// 반환된 포인터는 statModifiers가 추가, 삭제, 재할당되기 전까지만 유효하다.
// 효과를 찾지 못하면 nullptr을 반환한다.
const Stat_Modifier* Player::Get_Stat_Modifier(
    const std::string& id) const
{
    for (const Stat_Modifier& modifier : statModifiers)
    {
        if (modifier.id == id)
        {
            return &modifier;
        }
    }

    return nullptr;
}
// 턴이 끝났을 때 지속시간 처리, 전투의 한 턴이 끝날 때마다 호출
// 남은 턴 수가 0이 된 효과는 제거, 제거된 경우 Recalculate_Stats() 호출
// 사용법은 player->Process_Stat_Modifier_Turn() 호출
void Player::Process_Stat_Modifier_Turn()
{
    bool isChanged = false;

    for (auto it = statModifiers.begin();
        it != statModifiers.end();)
    {
        // -1은 영구 지속
        if (it->remainingTurns < 0)
        {
            ++it;
            continue;
        }

        if (it->remainingTurns > 0)
        {
            it->remainingTurns--;
        }

        if (it->remainingTurns == 0)
        {
            std::cout
                << it->name
                << " 효과가 종료되었습니다.\n";

            it = statModifiers.erase(it);
            isChanged = true;
            continue;
        }

        ++it;
    }

    if (isChanged)
    {
        Recalculate_Stats();
    }
}
// 모든 기간제 효과 제거, 영구 효과는 유지, 전투 중 버프 초기화 등에 사용
// 제거된 경우 Recalculate_Stats() 호출
void Player::Remove_Temporary_Modifiers()
{
    bool isChanged = false;

    for (auto it = statModifiers.begin();
        it != statModifiers.end();)
    {
        if (it->remainingTurns >= 0)
        {
            it = statModifiers.erase(it);
            isChanged = true;
            continue;
        }

        ++it;
    }

    if (isChanged)
    {
        Recalculate_Stats();
    }
}

// 전달받은 Stat_Modifier_Type과 같은 종류의 효과를 모두 제거한다.
// 예: Tutor 타입을 전달하면 현재 적용된 모든 튜터 효과를 제거한다.
// 하나 이상 제거된 경우 최종 스탯을 다시 계산한다.
void Player::Remove_Modifiers_By_Type(
    Stat_Modifier_Type type)
{
    bool isChanged = false;

    for (auto it = statModifiers.begin();
        it != statModifiers.end();)
    {
        if (it->type == type)
        {
            it = statModifiers.erase(it);
            isChanged = true;
            continue;
        }

        ++it;
    }

    if (isChanged)
    {
        Recalculate_Stats();
    }
}

// 적용 중인 효과 출력, 사용법은 Print_Status()와 동일
void Player::Print_Stat_Modifiers() const
{
    std::cout << "\n========== 적용 중인 효과 ==========\n";

    if (statModifiers.empty())
    {
        std::cout << "적용 중인 효과가 없습니다.\n";
        std::cout << "====================================\n";
        return;
    }

    for (const Stat_Modifier& modifier : statModifiers)
    {
        std::cout << modifier.name;

        if (modifier.remainingTurns < 0)
        {
            std::cout << " [영구]";
        }
        else
        {
            std::cout
                << " ["
                << modifier.remainingTurns
                << "턴]";
        }

        std::cout << '\n';
    }

    std::cout << "====================================\n";
}

// 기본 Getter

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

int Player::GetMaxHP() const
{
    return maxhp;
}

int Player::GetMaxMP() const
{
    return maxmp;
}

// 기존 코드 호환용 Getter

int Player::GetPower() const
{
    return atk;
}

int Player::GetHP() const
{
    return hp;
}

// 기본 Setter
// 주의: 현재 Set은 플레이어의 스탯을 직접 변경함
// 전투 중 스탯 변경 등은 Add_Stat_Modifier()와 Remove_Stat_Modifier()를 사용

void Player::Set_Hp(int value)
{
    if (value < 0)
    {
        hp = 0;
    }
    else if (value > maxhp)
    {
        hp = maxhp;
    }
    else
    {
        hp = value;
    }
}

void Player::Set_Mp(int value)
{
    if (value < 0)
    {
        mp = 0;
    }
    else if (value > maxmp)
    {
        mp = maxmp;
    }
    else
    {
        mp = value;
    }
}
void Player::Set_ATK(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (!statModifierInitialized)
    {
        atk = value;
        return;
    }

    baseStat.atk = value;
    Recalculate_Stats();
}
void Player::Set_DEF(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (!statModifierInitialized)
    {
        def = value;
        return;
    }

    baseStat.def = value;
    Recalculate_Stats();
}

void Player::Set_AP(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (!statModifierInitialized)
    {
        ap = value;
        return;
    }

    baseStat.ap = value;
    Recalculate_Stats();
}

void Player::Set_SNE(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (!statModifierInitialized)
    {
        sne = value;
        return;
    }

    baseStat.sne = value;
    Recalculate_Stats();
}

void Player::Set_AGI(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (!statModifierInitialized)
    {
        agi = value;
        return;
    }

    baseStat.agi = value;
    Recalculate_Stats();
}

void Player::SetMaxHP(int value)
{
    if (value < 1)
    {
        value = 1;
    }

    if (!statModifierInitialized)
    {
        maxhp = value;

        if (hp > maxhp)
        {
            hp = maxhp;
        }

        return;
    }

    baseStat.maxHp = value;
    Recalculate_Stats();
}

void Player::SetMaxMP(int value)
{
    if (value < 0)
    {
        value = 0;
    }

    if (!statModifierInitialized)
    {
        maxmp = value;

        if (mp > maxmp)
        {
            mp = maxmp;
        }

        return;
    }

    baseStat.maxMp = value;
    Recalculate_Stats();
}

void Player::Set_Level(int value)
{
    if (value < 1)
    {
        level = 1;
        return;
    }

    level = value;
}

// 기존 코드 호환용 Setter

void Player::SetHP(int value)
{
    Set_Hp(value);
}

void Player::SetPower(int value)
{
    Set_ATK(value);
}

// 소문자 Getter 호환 함수

std::string Player::getName() const
{
    return Get_Name();
}

std::string Player::getJob() const
{
    return Get_Job();
}

int Player::getLevel() const
{
    return Get_Level();
}

int Player::getHp() const
{
    return Get_Hp();
}

int Player::getHP() const
{
    return Get_Hp();
}

int Player::getMp() const
{
    return Get_Mp();
}

int Player::getMP() const
{
    return Get_Mp();
}

int Player::getPower() const
{
    return Get_ATK();
}

int Player::getAtk() const
{
    return Get_ATK();
}

int Player::getDefence() const
{
    return Get_DEF();
}

int Player::getDef() const
{
    return Get_DEF();
}

int Player::getAp() const
{
    return Get_AP();
}

int Player::getSne() const
{
    return Get_SNE();
}

int Player::getAgi() const
{
    return Get_AGI();
}

// 소문자 Setter 호환 함수

void Player::setHp(int value)
{
    Set_Hp(value);
}

void Player::setHP(int value)
{
    Set_Hp(value);
}

void Player::setMp(int value)
{
    Set_Mp(value);
}

void Player::setMP(int value)
{
    Set_Mp(value);
}

void Player::setPower(int value)
{
    Set_ATK(value);
}

void Player::setAtk(int value)
{
    Set_ATK(value);
}

void Player::setDefence(int value)
{
    Set_DEF(value);
}

void Player::setDef(int value)
{
    Set_DEF(value);
}

void Player::setAp(int value)
{
    Set_AP(value);
}

void Player::setSne(int value)
{
    Set_SNE(value);
}

void Player::setAgi(int value)
{
    Set_AGI(value);
}

void Player::setLevel(int value)
{
    Set_Level(value);
}


//기본 스탯 Getter
int Player::Get_Base_MaxHP() const
{
    return statModifierInitialized
        ? baseStat.maxHp
        : maxhp;
}

int Player::Get_Base_MaxMP() const
{
    return statModifierInitialized
        ? baseStat.maxMp
        : maxmp;
}

int Player::Get_Base_ATK() const
{
    return statModifierInitialized
        ? baseStat.atk
        : atk;
}

int Player::Get_Base_DEF() const
{
    return statModifierInitialized
        ? baseStat.def
        : def;
}

int Player::Get_Base_AP() const
{
    return statModifierInitialized
        ? baseStat.ap
        : ap;
}

int Player::Get_Base_SNE() const
{
    return statModifierInitialized
        ? baseStat.sne
        : sne;
}

int Player::Get_Base_AGI() const
{
    return statModifierInitialized
        ? baseStat.agi
        : agi;
}


// 영구 스탯 변화용 함수. 레벨업이나 영약 등을 사용하였을 때 사용,
// 호출 방법은 player ->Add_Base_MaxHP(10); 이런식으로 호출하면 됨
void Player::Add_Base_MaxHP(int value)
{
    Initialize_Base_Stat();

    baseStat.maxHp += value;

    if (baseStat.maxHp < 1)
    {
        baseStat.maxHp = 1;
    }

    Recalculate_Stats();
}

void Player::Add_Base_MaxMP(int value)
{
    Initialize_Base_Stat();

    baseStat.maxMp += value;

    if (baseStat.maxMp < 0)
    {
        baseStat.maxMp = 0;
    }

    Recalculate_Stats();
}

void Player::Add_Base_ATK(int value)
{
    Initialize_Base_Stat();

    baseStat.atk += value;

    if (baseStat.atk < 0)
    {
        baseStat.atk = 0;
    }

    Recalculate_Stats();
}

void Player::Add_Base_DEF(int value)
{
    Initialize_Base_Stat();

    baseStat.def += value;

    if (baseStat.def < 0)
    {
        baseStat.def = 0;
    }

    Recalculate_Stats();
}

void Player::Add_Base_AP(int value)
{
    Initialize_Base_Stat();

    baseStat.ap += value;

    if (baseStat.ap < 0)
    {
        baseStat.ap = 0;
    }

    Recalculate_Stats();
}

void Player::Add_Base_SNE(int value)
{
    Initialize_Base_Stat();

    baseStat.sne += value;

    if (baseStat.sne < 0)
    {
        baseStat.sne = 0;
    }

    Recalculate_Stats();
}

void Player::Add_Base_AGI(int value)
{
    Initialize_Base_Stat();

    baseStat.agi += value;

    if (baseStat.agi < 0)
    {
        baseStat.agi = 0;
    }

    Recalculate_Stats();
}
// 스킬 이름 Getter
std::string Player::Get_Skill1_Name() const
{
    return skill1Name;
}

std::string Player::Get_Skill2_Name() const
{
    return skill2Name;
}

std::string Player::Get_Skill3_Name() const
{
    return skill3Name;
}

std::string Player::Get_Groggy_Attack_Name() const
{
    return groggyAttackName;
}