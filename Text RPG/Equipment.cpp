// Equipment.cpp
#include "Equipment.h"
#include <iostream>
using namespace std;


Equipment::Equipment()//기본생성자
{
    _Equipment_Name = "None";
    _Attack_Stat = 0 ;
    _Defence_Stat = 0 ;
    _Grade= Equipment_Grade::Empty ;
    _Enhance_Level = 0 ;
}

Equipment::Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade)
{
    _Equipment_Name = equipment_name ;
    _Attack_Stat = attack ;
    _Defence_Stat = defence ;
    _Grade = grade ;
    _Enhance_Level = 0 ;
}

int Equipment::Get_Enhance_Level() const
{
    return _Enhance_Level;;
}

void Equipment::Set_Enhance_Level(int enhance_level)
{
    _Enhance_Level = enhance_level;
}

int Equipment::Get_Attack_Stat() const
{
    return _Attack_Stat;
}

void Equipment::Set_Attack_Stat(int attack_stat)
{
    _Attack_Stat = attack_stat;
}

int Equipment::Get_Defence_Stat() const
{
    return _Defence_Stat;
}

void Equipment::Set_Defence_Stat(int defence_stat)
{
    _Defence_Stat = defence_stat;
}

void Equipment::Print_Equipment_Info() const
{
    return;
}

//장비창


Equipment_Inventory::Equipment_Inventory(int max_count)
{
    return;
}

Equipment_Inventory::~Equipment_Inventory()
{
    return;
}

bool Equipment_Inventory::Equip_Equipment(const Equipment& equipment)
{
    return false;
}

Equipment* Equipment_Inventory::Get_Equipment_By_Index(int index)
{
    return 0;
}

void Equipment_Inventory::Print_Equipment_Inventory() const
{
    return;
}