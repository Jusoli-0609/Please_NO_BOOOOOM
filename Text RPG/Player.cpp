#include <iostream>
#include <algorithm>
#include <string>
#include "Player.h"
#include "Equipment.h"
#include "Tutor.h"
#include "Monster.h"
#include "Console_Manager.h"
#include <sstream>
#include <limits>

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
    currentlyEquippedTutor(nullptr),
    statpoints(5)
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

//치명타 계산
bool Player::Check_Critical() const
{
    const float baseCriticalChance = 5.0f;
    const float sneConstant = 2.5f;
    const float agiConstant = 1.0f;

    float criticalChance =
        baseCriticalChance
        + sne * sneConstant
        + agi * agiConstant;

    // 치명타 확률 증가 버프가 있을 때만 추가 수치 적용
    if (Has_Stat_Modifier("CRITICAL_CHANCE_BUFF"))
    {
        criticalChance += criticalBuffValue;
    }

    // 확률 제한
    if (criticalChance < 0.0f)
    {
        criticalChance = 0.0f;
    }
    else if (criticalChance > 70.0f)
    {
        criticalChance = 70.0f;
    }

    int randomValue = rand() % 100 + 1;

    return randomValue <= criticalChance;
}

// 치명타가 발생하면 전달받은 데미지를 1.5배로 변경한다.
void Player::Apply_Critical_Damage(int& damage) const
{
    if (!Check_Critical())
    {
        return;
    }

    damage = static_cast<int>(damage * 1.5f);
    std::cout << "★ 크리티컬! ★\n";
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
    bool isDefenceDecreaseBuffOn =
        Has_Stat_Modifier("DEFENCE_DECREASE_BUFF");

    if (isDefenceDecreaseBuffOn)
    {
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

void Add_statpoints(Player* player, int points)
{
	player->Add_Stat_Points(points);
}

void Player::Print_Status(Console_Manager& console) const
{
    Update_Equipment_Buff();

    const std::string LINE(120, '=');
    const std::string SUB_LINE(120, '-');

    auto Add_Stat = [](
        std::ostringstream& out,
        const std::string& name,
        int base,
        int final)
        {
            int additional = final - base;

            out << name << ": " << final
                << "  (기본 " << base;

            if (additional > 0)
            {
                out << " + 추가 " << additional;
            }
            else if (additional < 0)
            {
                out << " - 감소 " << -additional;
            }
            else
            {
                out << " + 추가 0";
            }

            out << ")";
        };

    int page = 1;

    while (true)
    {
        console.Clear();

        // =====================================================
        // 1페이지: 기본 정보, 능력치, 스킬
        // =====================================================
        if (page == 1)
        {
            std::ostringstream output;

            output
                << LINE << '\n'
                << "                                                   캐릭터 정보\n"
                << "                                                     1 / 3\n"
                << LINE << '\n'

                << "이름: " << name
                << "    직업: " << job
                << "    레벨: " << level
                << "    경험치: " << Get_Exp()
                << " / " << Get_Max_Exp()
                << '\n'

                << "HP: " << hp << " / " << maxhp
                << "    MP: " << mp << " / " << maxmp
                << '\n'

                << SUB_LINE << '\n'
                << "[능력치]\n";

            Add_Stat(
                output,
                "MAX HP",
                baseStat.maxHp,
                maxhp
            );

            output << "    ";

            Add_Stat(
                output,
                "MAX MP",
                baseStat.maxMp,
                maxmp
            );

            output << '\n';

            Add_Stat(
                output,
                "ATK",
                baseStat.atk,
                atk
            );

            output << "    ";

            Add_Stat(
                output,
                "DEF",
                baseStat.def,
                def
            );

            output << "    ";

            Add_Stat(
                output,
                "AP",
                baseStat.ap,
                ap
            );

            output << '\n';

            Add_Stat(
                output,
                "SNE",
                baseStat.sne,
                sne
            );

            output << "    ";

            Add_Stat(
                output,
                "AGI",
                baseStat.agi,
                agi
            );

            output
                << '\n'
                << "남은 분배 가능 스탯포인트: "
                << statpoints
                << '\n'

                << SUB_LINE << '\n'
                << "[스킬]\n"

                << "1. " << skill1Name
                << "    2. " << skill2Name
                << '\n'

                << "3. " << skill3Name
                << "    그로기: " << groggyAttackName
                << '\n'

                << LINE << '\n';

            // 정보는 즉시 출력
            console.Slow_Print(
                output.str(),
                0
            );
        }

        // =====================================================
        // 2페이지: 장착 장비
        // =====================================================
        else if (page == 2)
        {
            std::ostringstream output;

            output
                << LINE << '\n'
                << "                                                캐릭터 추가 정보\n"
                << "                                                     2 / 3\n"
                << LINE << '\n'
                << "[장착 장비]\n";

            console.Slow_Print(
                output.str(),
                0
            );

            if (currentlyEquippedEquipments != nullptr)
            {
                currentlyEquippedEquipments
                    ->Print_Currently_Equipped_Equipments();
            }
            else
            {
                std::cout << "장비 정보 없음\n";
            }

            std::cout
                << LINE << '\n';
        }

        // =====================================================
        // 3페이지: 적용 효과
        // =====================================================
        else if (page == 3)
        {
            std::ostringstream output;

            output
                << LINE << '\n'
                << "튜터 및 적용 효과\n"
                << "3 / 3\n"
                << LINE << '\n'
                << "[튜터]\n";

            console.Slow_Print(output.str(), 0);

            if (currentlyEquippedTutor != nullptr)
            {
                currentlyEquippedTutor
                    ->Print_Currently_Equipped_Tutor();
            }
            else
            {
                std::cout << "튜터 정보 없음\n";
            }

            std::ostringstream effects;

            effects
                << SUB_LINE << '\n'
                << "[적용 효과]\n";

            if (statModifiers.empty())
            {
                effects << "없음\n";
            }
            else
            {
                int effectCount = 0;

                for (const Stat_Modifier& modifier : statModifiers)
                {
                    effects << modifier.name;

                    if (modifier.remainingTurns < 0)
                    {
                        effects << " [영구]";
                    }
                    else
                    {
                        effects
                            << " ["
                            << modifier.remainingTurns
                            << "턴]";
                    }

                    effectCount++;

                    if (effectCount % 2 == 0)
                    {
                        effects << '\n';
                    }
                    else
                    {
                        effects << "    |    ";
                    }
                }

                if (effectCount % 2 != 0)
                {
                    effects << '\n';
                }
            }

            effects << LINE << '\n';

            console.Slow_Print(effects.str(), 0);
            }

        // =====================================================
        // 선택지
        // =====================================================
        std::ostringstream menu;

        if (page > 1)
        {
            menu << "1. 이전 페이지\n";
        }

        if (page < 3)
        {
            menu << "2. 다음 페이지\n";
        }

        if (statpoints > 0)
        {
            menu << "3. 스탯포인트 분배\n";
        }

        menu
            << "0. 돌아가기\n"
            << "선택: ";

        // 선택지만 타이핑 효과
        console.Slow_Print(
            menu.str(),
            20
        );

        int choice;
        std::cin >> choice;

        if (choice == 0)
        {
            return;
        }

        if (choice == 1 && page > 1)
        {
            page--;
        }
        else if (choice == 2 && page < 3)
        {
            page++;
        }
        else if (choice == 3 && statpoints > 0)
        {
            const_cast<Player*>(this)
                ->Distribute_Stat_Points();

            return;
        }
    }
}
// 스탯포인트를 분배하는 함수
void Player::Distribute_Stat_Points()
{
    while (statpoints > 0)
    {
        std::cout << "\n";
        std::cout << "========================================\n";
        std::cout << "           스탯포인트 분배\n";
        std::cout << "========================================\n";
        std::cout << "남은 스탯포인트: " << statpoints << '\n';
        std::cout << "1. MAX HP +5\n";
        std::cout << "2. MAX MP +5\n";
        std::cout << "3. ATK +2\n";
        std::cout << "4. DEF +5\n";
        std::cout << "5. AP +2\n";
        std::cout << "6. SNE +3\n";
        std::cout << "7. AGI +3\n";
        std::cout << "0. 종료\n";
        std::cout << "선택: ";

        int statChoice;
        std::cin >> statChoice;

        if (statChoice == 0)
        {
            return;
        }

        if (statChoice < 1 || statChoice > 7)
        {
            std::cout << "잘못된 선택이다.\n";
            continue;
        }

        std::cout << "분배할 포인트 수: ";

        int amount;
        std::cin >> amount;

        if (amount <= 0 || amount > statpoints)
        {
            std::cout << "잘못된 포인트 수다.\n";
            continue;
        }

        switch (statChoice)
        {
        case 1:
            baseStat.maxHp += 5* amount;
            break;

        case 2:
            baseStat.maxMp += 5* amount;
            break;

        case 3:
            baseStat.atk += 2 * amount;
            break;

        case 4:
            baseStat.def += 5 * amount;
            break;

        case 5:
            baseStat.ap += 2 * amount;
            break;

        case 6:
            baseStat.sne += 3 * amount;
            break;

        case 7:
            baseStat.agi += 3 * amount;
            break;
        }

        statpoints -= amount;

        Recalculate_Stats();

        std::cout << amount << "포인트를 분배했다!\n";
        std::cout << "남은 스탯포인트: "
            << statpoints << '\n';
    }

    std::cout << "모든 스탯포인트를 분배했다.\n";
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

void Player::Add_Stat_Points(int points)
{
	if (points < 0)
	{
		std::cout << "스탯포인트는 음수로 추가할 수 없습니다.\n";
		return;
	}
	statpoints += points;
	std::cout << "  -> " << points << " 스탯포인트를 획득했다! 현재 남은 스탯포인트: "
		<< statpoints << "\n";
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

// 명중 판정, 몬스터의 회피율과 플레이어의 민첩을 고려하여 명중 여부를 결정
bool Player::Check_Hit(const Monster* monster) const
{
    if (monster == nullptr)
    {
        return false;
    }

    const int baseValue = 100;
    const float hitConstant = 2.0f;

    int hitChance = static_cast<int>(
        (
            baseValue
            - monster->getEvasion()
            + agi
            )
        * hitConstant
        );

    // 최소·최대 명중률
    if (hitChance < 30)
    {
        hitChance = 30;
    }
    else if (hitChance > 95)
    {
        hitChance = 95;
    }

    int randomValue = rand() % 100 + 1;

    return randomValue <= hitChance;
}

void Player::Apply_Equipment_Stats(
    const Currently_Equipped_Equipments& equipments
)
{
    Equipment_Stats equipmentStats =
        equipments.Get_All_Equipments_Stats();

    Stat_Modifier modifier;

    modifier.id = "EQUIPMENT_TOTAL_STATS";
    modifier.name = "장착 장비 효과";
    modifier.type = Stat_Modifier_Type::Equipment;
    modifier.remainingTurns = -1;

    modifier.flat.atk = equipmentStats.Attack;
    modifier.flat.def = equipmentStats.Defence;

    Add_Stat_Modifier(modifier);
}

// 장비 효과를 적용하는 함수, 장비의 공격력과 방어력을 받아서 Stat_Modifier를 생성하고 Add_Stat_Modifier()를 호출
void Player::Apply_Equipment_Buff(
    int equipmentAtk,
    int equipmentDef
)
{
    Stat_Modifier modifier;

    modifier.id = "EQUIPMENT_BUFF";
    modifier.name = "장비 효과";
    modifier.type = Stat_Modifier_Type::Equipment;
    modifier.remainingTurns = -1;

    modifier.flat.atk = equipmentAtk;
    modifier.flat.def = equipmentDef;

    Add_Stat_Modifier(modifier);
}

void Player::Update_Equipment_Buff() const
{
    Player* player = const_cast<Player*>(this);

    if (currentlyEquippedEquipments == nullptr)
    {
        player->Remove_Stat_Modifier("EQUIPMENT_BUFF");
        return;
    }

    Equipment_Stats equipmentStats =
        currentlyEquippedEquipments->Get_All_Equipments_Stats();

    Stat_Modifier modifier;

    modifier.id = "EQUIPMENT_BUFF";
    modifier.name = "장비 효과";
    modifier.type = Stat_Modifier_Type::Equipment;
    modifier.remainingTurns = -1;

    modifier.flat.atk = equipmentStats.Attack;
    modifier.flat.def = equipmentStats.Defence;

    player->Add_Stat_Modifier(modifier);
}