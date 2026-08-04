#pragma once
#include <string>
#include "Stat_Modifier.h"

class Player;
class Currently_Equipped_Equipments;
class Inventory_For_Equipments_Only;


class Tutor
{
private:
    std::string _Tutor_Name;
    std::string _Required_Item_Name;
    std::string _Tutor_Description;
    Stat_Modifier _Tutor_Modifier;

public:
    Tutor();

    Tutor(
        const std::string& tutor_name,
        const std::string& required_item_name,
        const std::string& tutor_description,
        const Stat_Modifier& tutor_modifier
    );

    std::string Get_Tutor_Name() const;
    std::string Get_Required_Item_Name() const;
    std::string Get_Tutor_Description() const;

    const Stat_Modifier& Get_Tutor_Modifier() const;

    bool Is_Empty() const;

    void Print_Tutor_Info() const;
};

class Currently_Equipped_Tutor
{
private:
    Tutor _Equipped_Tutor;
    bool _Has_Equipped_Tutor;

public:
    Currently_Equipped_Tutor();

    bool Equip_Tutor(
        const Tutor& tutor,
        Player* player
    );

    bool Unequip_Tutor(
        Player* player
    );

    bool Has_Equipped_Tutor() const;

    std::string Get_Equipped_Tutor_Name() const;

    void Print_Currently_Equipped_Tutor() const;
};

Tutor Create_Tutor_By_Number(
    int tutor_number
);

bool Has_Tutor_Item(
    const Inventory_For_Equipments_Only& equipment_inventory,
    const Currently_Equipped_Equipments& equipped_equipments,
    const std::string& equipment_name
);

void Print_Tutor_Menu(
    const Inventory_For_Equipments_Only& equipment_inventory,
    const Currently_Equipped_Equipments& equipped_equipments,
    Currently_Equipped_Tutor& currently_equipped_tutor,
    Player* player
);