#include "Equipment.h"
#include <iostream>
using namespace std;

//기본생성자
Equipment::Equipment()
{
    _Equipment_Name = "None";
    _Attack_Stat = 0 ;
    _Defence_Stat = 0 ;
    _Grade= Equipment_Grade::Empty ;
    _Enhance_Level = 0 ;
}

//아이템 다 대입 생성자 뭔말알?
Equipment::Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade)
{
    _Equipment_Name = equipment_name ;
    _Attack_Stat = attack ;
    _Defence_Stat = defence ;
    _Grade = grade ;
    _Enhance_Level = 0 ;
}

//장비 등급을 문자열 출력으로~~!
string Equipment:: Equipment_Grade_To_String(Equipment_Grade grade) const
{
    switch (grade)
    {
    case Equipment_Grade::Empty:
    {
        return "Empty";
    }
    case Equipment_Grade::Worst:
    {
        return "Worst";
    }
    case Equipment_Grade::Low:
    {
        return "Low";
    }
    case Equipment_Grade::Middle:
    {
        return "Middle";
    }
    case Equipment_Grade::High:
    {
        return "High";
    }
    case Equipment_Grade::Best:
    {
        return "Best";
    }
    default:
    {
        return "Unknown";
    }
    }
}

//강화도 조회
int Equipment::Get_Enhance_Level() const
{
    return _Enhance_Level;;
}

//강화도 설정
void Equipment::Set_Enhance_Level(int enhance_level)
{
    _Enhance_Level = enhance_level;
}

//공격력 스텟 조회
int Equipment::Get_Attack_Stat() const
{
    return _Attack_Stat;
}

//공격력 스텟 설정
void Equipment::Set_Attack_Stat(int attack_stat)
{
    _Attack_Stat = attack_stat;
}

//수비력 스텟 조회
int Equipment::Get_Defence_Stat() const
{
    return _Defence_Stat;
}

//수비력 스텟 설정
void Equipment::Set_Defence_Stat(int defence_stat)
{
    _Defence_Stat = defence_stat;
}

//장비 출력 함수
void Equipment::Print_Equipment_Info() const
{
    cout << "장비 이름: " << _Equipment_Name << endl;
    cout << "공격력: " << _Attack_Stat << endl;
    cout << "방어력: " << _Defence_Stat << endl;
    cout << "등급: " << Equipment_Grade_To_String(_Grade) << endl;
    cout << "강화 레벨: +" << _Enhance_Level << endl;
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