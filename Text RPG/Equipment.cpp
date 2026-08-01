// Equipment.cpp
#include "Equipment.h"
#include <iostream>
using namespace std;


Equipment::Equipment()//기본생성자
{
    _Equipment_Name = ? ;
    _Attack_Stat = ? ;
    _Defence_Stat = ? ;
    _Grade = ? ;
    _Enhance_Level = ? ;
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
   
}

void Equipment::Set_Enhance_Level(int enhance_level)
{
  
}

int Equipment::Get_Attack_Stat() const
{
   
}

void Equipment::Set_Attack_Stat(int attack_stat)
{
   
}

int Equipment::Get_Defence_Stat() const
{
}

void Equipment::Set_Defence_Stat(int defence_stat)
{
 
}

void Equipment::Print_Equipment_Info() const
{
    
}

//장비창


Equipment_Inventory::Equipment_Inventory(int max_count)
{

}

Equipment_Inventory::~Equipment_Inventory()
{

}

bool Equipment_Inventory::Equip_Equipment(const Equipment& equipment)
{
}

Equipment* Equipment_Inventory::Get_Equipment_By_Index(int index)
{
   
}

void Equipment_Inventory::Print_Equipment_Inventory() const
{
   
}