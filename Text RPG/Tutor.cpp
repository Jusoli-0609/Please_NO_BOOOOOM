#include "Tutor.h"
#include "Inventory.h"
#include "Item.h"
#include "Player.h"
#include "Equipment.h"
#include <iostream>

using namespace std;

namespace
{
    Stat_Modifier Create_Tutor_Modifier(
        const string& modifier_id,
        const string& modifier_name,
        int max_hp,
        int max_mp,
        int atk,
        int def,
        int ap,
        int sne,
        int agi)
    {
        Stat_Modifier Tutor_Modifier;

        Tutor_Modifier.id = modifier_id;
        Tutor_Modifier.name = modifier_name;
        Tutor_Modifier.type = Stat_Modifier_Type::Tutor;

        Tutor_Modifier.flat.maxHp = max_hp;
        Tutor_Modifier.flat.maxMp = max_mp;
        Tutor_Modifier.flat.atk = atk;
        Tutor_Modifier.flat.def = def;
        Tutor_Modifier.flat.ap = ap;
        Tutor_Modifier.flat.sne = sne;
        Tutor_Modifier.flat.agi = agi;

        Tutor_Modifier.remainingTurns = -1;

        return Tutor_Modifier;
    }
}

Tutor::Tutor()
    : _Tutor_Name("없음"),
    _Required_Item_Name(""),
    _Tutor_Description("장착 중인 튜터가 없다.")
{
}

Tutor::Tutor(
    const string& tutor_name,
    const string& required_item_name,
    const string& tutor_description,
    const Stat_Modifier& tutor_modifier)
    : _Tutor_Name(tutor_name),
    _Required_Item_Name(required_item_name),
    _Tutor_Description(tutor_description),
    _Tutor_Modifier(tutor_modifier)
{
}

string Tutor::Get_Tutor_Name() const
{
    return _Tutor_Name;
}

string Tutor::Get_Required_Item_Name() const
{
    return _Required_Item_Name;
}

string Tutor::Get_Tutor_Description() const
{
    return _Tutor_Description;
}

const Stat_Modifier& Tutor::Get_Tutor_Modifier() const
{
    return _Tutor_Modifier;
}

bool Tutor::Is_Empty() const
{
    return _Required_Item_Name.empty();
}

void Tutor::Print_Tutor_Info() const
{
    cout << "튜터: " << _Tutor_Name << endl;
    cout << "효과: " << _Tutor_Description << endl;
}

Currently_Equipped_Tutor::Currently_Equipped_Tutor()
    : _Has_Equipped_Tutor(false)
{
}

bool Currently_Equipped_Tutor::Equip_Tutor(
    const Tutor& tutor,
    Player* player)
{
    if (player == nullptr)
    {
        cout << "플레이어 정보가 없다!" << endl;
        return false;
    }

    if (tutor.Is_Empty())
    {
        cout << "선택할 수 없는 튜터다!" << endl;
        return false;
    }

    player->Remove_Modifiers_By_Type(
        Stat_Modifier_Type::Tutor
    );

    _Equipped_Tutor = tutor;
    _Has_Equipped_Tutor = true;

    player->Add_Stat_Modifier(
        _Equipped_Tutor.Get_Tutor_Modifier()
    );

    cout
        << _Equipped_Tutor.Get_Tutor_Name()
        << " 튜터님을 선택했다!"
        << endl;

    return true;
}

bool Currently_Equipped_Tutor::Unequip_Tutor(
    Player* player)
{
    if (player == nullptr)
    {
        cout << "플레이어 정보가 없다!" << endl;
        return false;
    }

    if (_Has_Equipped_Tutor == false)
    {
        cout << "선택 중인 튜터가 없다!" << endl;
        return false;
    }

    player->Remove_Modifiers_By_Type(
        Stat_Modifier_Type::Tutor
    );

    _Equipped_Tutor = Tutor();
    _Has_Equipped_Tutor = false;

    cout << "튜터 선택을 해제했다!" << endl;

    return true;
}

bool Currently_Equipped_Tutor::Has_Equipped_Tutor() const
{
    return _Has_Equipped_Tutor;
}

string Currently_Equipped_Tutor::Get_Equipped_Tutor_Name() const
{
    if (_Has_Equipped_Tutor == false)
    {
        return "없음";
    }

    return _Equipped_Tutor.Get_Tutor_Name();
}

void Currently_Equipped_Tutor::Print_Currently_Equipped_Tutor() const
{
    cout << endl;
    cout << "========================================" << endl;
    cout << "              현재 튜터" << endl;
    cout << "========================================" << endl;

    if (_Has_Equipped_Tutor == false)
    {
        cout << "선택 중인 튜터가 없다!" << endl;
    }
    else
    {
        _Equipped_Tutor.Print_Tutor_Info();
    }

    cout << "========================================" << endl;
}

Tutor Create_Tutor_By_Number(int tutor_number)
{
    switch (tutor_number)
    {
    case 1:
    {
        Stat_Modifier Tutor_Modifier =
            Create_Tutor_Modifier(
                "Tutor_Son_Seung_Hyun",
                "손승현 튜터 효과",
                0, 0, 10, 0, 0, 0, 10
            );

        return Tutor(
            "손승현",
            "손승현 튜터님의 로지텍 마우스",
            "ATK +10 / AGI +10",
            Tutor_Modifier
        );
    }

    case 2:
    {
        Stat_Modifier Tutor_Modifier =
            Create_Tutor_Modifier(
                "Tutor_Park_Eun_Il",
                "박은일 튜터 효과",
                0, 0, 0, 0, 10, 10, 0
            );

        return Tutor(
            "박은일",
            "박은일 튜터님의 갈축 키보드",
            "AP +10 / SNE +10",
            Tutor_Modifier
        );
    }

    case 3:
    {
        Stat_Modifier Tutor_Modifier =
            Create_Tutor_Modifier(
                "Tutor_Kang_Sin_Ho",
                "강신호 튜터 효과",
                20, 0, 0, 10, 0, 0, 0
            );

        return Tutor(
            "강신호",
            "강신호 튜터님의 게이밍 헤드셋",
            "MAX HP +20 / DEF +10",
            Tutor_Modifier
        );
    }

    case 4:
    {
        Stat_Modifier Tutor_Modifier =
            Create_Tutor_Modifier(
                "Tutor_Moon_Seung_Hyun",
                "문승현 튜터 효과",
                0, 20, 0, 0, 0, 10, 0
            );

        return Tutor(
            "문승현",
            "문승현 튜터님의 고양이 버츄얼",
            "MAX MP +20 / SNE +10",
            Tutor_Modifier
        );
    }

    case 5:
    {
        Stat_Modifier Tutor_Modifier =
            Create_Tutor_Modifier(
                "Tutor_Kim_Ha_Neul",
                "김하늘 튜터 효과",
                0, 0, 0, 5, 15, 0, 0
            );

        return Tutor(
            "김하늘",
            "김하늘 튜터님의 도수높은 안경",
            "AP +15 / DEF +5",
            Tutor_Modifier
        );
    }

    default:
    {
        return Tutor();
    }
    }
}

bool Has_Tutor_Item(
    const Inventory_For_Equipments_Only& equipment_inventory,
    const Currently_Equipped_Equipments& equipped_equipments,
    const string& equipment_name)
{
    if (equipment_inventory.Has_Equipment_By_Name(equipment_name))
    {
        return true;
    }

    if (equipped_equipments.Has_Equipment_By_Name(equipment_name))
    {
        return true;
    }

    return false;
}

void Print_Tutor_Menu(
    const Inventory_For_Equipments_Only& equipment_inventory,
    const Currently_Equipped_Equipments& equipped_equipments,
    Currently_Equipped_Tutor& currently_equipped_tutor,
    Player* player)
{
    if (player == nullptr)
    {
        cout << "플레이어 정보가 없다!" << endl;
        return;
    }

    while (true)
    {
        currently_equipped_tutor
            .Print_Currently_Equipped_Tutor();

        cout << endl;
        cout << "========================================" << endl;
        cout << "              튜터 선택" << endl;
        cout << "========================================" << endl;

        for (int Tutor_Number = 1;
            Tutor_Number <= 5;
            Tutor_Number++)
        {
            Tutor Current_Tutor =
                Create_Tutor_By_Number(Tutor_Number);

            bool Has_Item =
                Has_Tutor_Item(
                    equipment_inventory,
                    equipped_equipments,
                    Current_Tutor.Get_Required_Item_Name()
                );

            cout
                << Tutor_Number
                << ". "
                << Current_Tutor.Get_Tutor_Name()
                << " 튜터님 - "
                << Current_Tutor.Get_Tutor_Description()
                << " ["
                << (Has_Item ? "선택 가능" : "미보유")
                << "]"
                << endl;
        }

        cout << "6. 튜터 선택 해제" << endl;
        cout << "0. 되돌아가기" << endl;
        cout << "----------------------------------------" << endl;
        cout << "무엇을 할까?: ";

        int Choose_Tutor_Menu;
        cin >> Choose_Tutor_Menu;

        if (Choose_Tutor_Menu == 0)
        {
            return;
        }

        if (Choose_Tutor_Menu == 6)
        {
            currently_equipped_tutor
                .Unequip_Tutor(player);

            continue;
        }

        if (Choose_Tutor_Menu < 1 ||
            Choose_Tutor_Menu > 5)
        {
            cout << "잘못된 입력이다!" << endl;
            continue;
        }

        Tutor Selected_Tutor =
            Create_Tutor_By_Number(
                Choose_Tutor_Menu
            );

        if (Has_Tutor_Item(
            equipment_inventory,
            equipped_equipments,
            Selected_Tutor.Get_Required_Item_Name()
        ) == false)
        {
            cout
                << Selected_Tutor.Get_Required_Item_Name()
                << "을(를) 보유하고 있지 않다!"
                << endl;

            continue;
        }

        currently_equipped_tutor
            .Equip_Tutor(
                Selected_Tutor,
                player
            );
    }
}