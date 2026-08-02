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
    _Equipment_Type = Equipment_Type::Empty;
}

//아이템 다 대입 생성자 뭔말알?
Equipment::Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade, Equipment_Type type, string art)
{
    _Equipment_Name = equipment_name ;
    _Attack_Stat = attack ;
    _Defence_Stat = defence ;
    _Grade = grade ;
    _Enhance_Level = 0 ;
    _Equipment_Type = type;
    _Equipment__Ascii_Art = art;
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

//장비 타입을 문자열 출력으로~!
string Equipment::Equipment_Type_To_String(Equipment_Type type) const
{
    switch (type)
    {
    case Equipment_Type::CPU:
        return "CPU";

    case Equipment_Type::GPU:
        return "GPU";

    case Equipment_Type::Keyboard:
        return "Keyboard";

    case Equipment_Type::Mouse:
        return "Mouse";

    case Equipment_Type::BlueLight_Glasses:
        return "BlueLight Glasses";

    case Equipment_Type::Headset:
        return "Headset";

    case Equipment_Type::Virtual_Character:
        return "Virtual Character";

    default:
        return "Empty";
}

//강화도 조회
int Equipment::Get_Enhance_Level() const
{
    return _Enhance_Level;
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
    cout << "장비 타입: " << Equipment_Type_To_String(_Equipment_Type) << endl;
    cout << "공격력: " << _Attack_Stat << endl;
    cout << "방어력: " << _Defence_Stat << endl;
    cout << "등급: " << Equipment_Grade_To_String(_Grade) << endl;
    cout << "강화 레벨: +" << _Enhance_Level << endl;
}

//장비이름 조회
string Equipment::Get_Equipment_Name()const
{
    return _Equipment_Name;
}

//장비 등급 조회
Equipment_Grade Equipment::Get_Grade()const
{
    return _Grade;
}

//장비 무게 조회
int Equipment::Get_Equipment_Weight()const
{
    return _Equipment_Weight;
}

//장비 무게 설정
void Equipment::Set_Equipment_Weight(int weight)
{
    _Equipment_Weight = weight;
}

//장비 이름 설정
void Equipment::Set_Equipment_Name(string name)
{
    _Equipment_Name = name;
}

//장비 설명 조회
string Equipment::Get_Equipment_Description()const
{
    return _Equipment_Description;
}

//장비 설명 설정
void Equipment::Set_Equipment_Description(string description)
{
    _Equipment_Description = description;
}

//장비 타입 조회
Equipment_Type Equipment::Get_Equipment_Type()const
{
    return _Equipment_Type;
}

//장비 타입 설정
void Equipment::Set_Equipment_Type(Equipment_Type type)
{
    _Equipment_Type = type;
}

//-----------------현재 장착 중인 아이템 장비창------------------------------------


//장비창 기본 생성자
Currently_Equipped_Equipments::Currently_Equipped_Equipments()
{
    _Max_Count = max_count;
    _Current_Count = 0;
    _Equipments = new Equipment[max_count];
}

//장비창 소멸자
Currently_Equipped_Equipments::~Currently_Equipped_Equipments()
{
    delete[] _Equipments;
}

//장비 착용
bool Currently_Equipped_Equipments::Equip_Equipment(const Equipment& equipment)
{
    if (_Current_Count >= _Max_Count)
    {
        cout << "더 착용할 공간이 없다! 펩 스토어로 출발~!" << endl;
        return false;
    }
    _Equipments[_Current_Count] = equipment;
    _Current_Count++;
    return true;
}

//장비 이름 인덱스로 조회하기
Equipment* Currently_Equipped_Equipments::Get_Equipment_By_Index(int index)
{
    if (index < 0 || index >= _Current_Count)
    {
        return nullptr;
    }
    return &_Equipments[index];
}

//장비창 출력
void Currently_Equipped_Equipments::Print_Currently_Equipped_Equipments() const
{
    return;
}