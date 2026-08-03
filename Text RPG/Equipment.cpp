#include "Equipment.h"
#include <iostream>
#include <algorithm>
using namespace std;

//�⺻������
Equipment::Equipment()
    : _Equipment_Name("None"),
    _Attack_Stat(0),
    _Defence_Stat(0),
    _Grade(Equipment_Grade::Empty),
    _Enhance_Level(0),
    _Equipment_Type(Equipment_Type::Empty),
    _Equipment__Ascii_Art(""),
    _Equipment_Description(""),
    _Equipment_Weight(0)
{
}

//������ �� ���� ������ ������?
Equipment::Equipment(
    string equipment_name,
    int attack,
    int defence,
    Equipment_Grade grade,
    Equipment_Type type,
    string art,
    string description,
    int weight
)
    : _Equipment_Name(equipment_name),
    _Attack_Stat(attack),
    _Defence_Stat(defence),
    _Grade(grade),
    _Enhance_Level(0),
    _Equipment_Type(type),
    _Equipment__Ascii_Art(art),
    _Equipment_Description(description),
    _Equipment_Weight(weight)
{
}

//��� ����� ���ڿ� �������~~!
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


//��� Ÿ���� ���ڿ� �������~!
string Equipment::Equipment_Type_To_String(Equipment_Type type) const
{
    switch (type)
    {
    case Equipment_Type::Engine:
        return "Unreal Engine";

    case Equipment_Type::Keyboard:
        return "Keyboard";

    case Equipment_Type::Mouse:
        return "Mouse";

    case Equipment_Type::BlueLight_Glasses:
        return "BlueLight Glasses";

    case Equipment_Type::Headset:
        return "Headset";

    default:
        return "Empty";
    }
}

//��ȭ�� ��ȸ
int Equipment::Get_Enhance_Level() const
{
    return _Enhance_Level;
}

//��ȭ�� ����
void Equipment::Set_Enhance_Level(int enhance_level)
{
    _Enhance_Level = enhance_level;
}

//���ݷ� ���� ��ȸ
int Equipment::Get_Attack_Stat() const
{
    return _Attack_Stat;
}

//���ݷ� ���� ����
void Equipment::Set_Attack_Stat(int attack_stat)
{
    _Attack_Stat = attack_stat;
}

//����� ���� ��ȸ
int Equipment::Get_Defence_Stat() const
{
    return _Defence_Stat;
}

//����� ���� ����
void Equipment::Set_Defence_Stat(int defence_stat)
{
    _Defence_Stat = defence_stat;
}

//��� ��� �Լ�
void Equipment::Print_Equipment_Info() const
{
    cout << "��� �̸�: " << _Equipment_Name << endl;
    cout << "��� ����: " << _Equipment_Description << endl;
    cout << "��� Ÿ��: " << Equipment_Type_To_String(_Equipment_Type) << endl;
    cout <<  "��� ����: " << _Equipment_Weight << endl;
    cout << "���ݷ�: " << _Attack_Stat << endl;
    cout << "����: " << _Defence_Stat << endl;
    cout << "���: " << Equipment_Grade_To_String(_Grade) << endl;
    cout << "��ȭ ����: +" << _Enhance_Level << endl;
    cout << _Equipment__Ascii_Art << endl;
}

//����̸� ��ȸ
string Equipment::Get_Equipment_Name()const
{
    return _Equipment_Name;
}

//��� ��� ��ȸ
Equipment_Grade Equipment::Get_Grade()const
{
    return _Grade;
}

//��� ���� ��ȸ
int Equipment::Get_Equipment_Weight()const
{
    return _Equipment_Weight;
}

//��� ���� ����
void Equipment::Set_Equipment_Weight(int weight)
{
    _Equipment_Weight = weight;
}

//��� �̸� ����
void Equipment::Set_Equipment_Name(string name)
{
    _Equipment_Name = name;
}

//��� ���� ��ȸ
string Equipment::Get_Equipment_Description()const
{
    return _Equipment_Description;
}

//��� ���� ����
void Equipment::Set_Equipment_Description(string description)
{
    _Equipment_Description = description;
}

//��� Ÿ�� ��ȸ
Equipment_Type Equipment::Get_Equipment_Type()const
{
    return _Equipment_Type;
}

//��� Ÿ�� ����
void Equipment::Set_Equipment_Type(Equipment_Type type)
{
    _Equipment_Type = type;
}

//-----------------���� ���� ���� ������ ���â------------------------------------


//���â �⺻ ������
Currently_Equipped_Equipments::Currently_Equipped_Equipments()
{
    
}


//��� ����
bool Currently_Equipped_Equipments::Equip_Equipment(const Equipment& equipment)
{
    Equipment_Type type = equipment.Get_Equipment_Type();


    if (Is_Equipment_Equipped(type))
    {
        cout << "�̹� ���� ������ ��� �����ϰ� �ִ�! �����ϰ� �����ض�!" << endl;
        return false;
    }


    switch (type)
    {
    case Equipment_Type::Engine:
        _Unreal_Engine_Version = equipment;
        break;


    case Equipment_Type::Keyboard:
        _Keyboard = equipment;
        break;


    case Equipment_Type::Mouse:
        _Mouse = equipment;
        break;


    case Equipment_Type::BlueLight_Glasses:
        _BlueLight_Glasses = equipment;
        break;


    case Equipment_Type::Headset:
        _Headset = equipment;
        break;


    default:
        cout << "������ �� ���� �������̴�!" << endl;
        return false;
    }


    cout << equipment.Get_Equipment_Name()
        << " ���� �Ϸ�!" << endl;


    return true;
}

bool Currently_Equipped_Equipments::Is_Equipment_Equipped(Equipment_Type type) const
{
    switch (type)
    {
    case Equipment_Type::Engine:
        return _Unreal_Engine_Version.Get_Equipment_Type() != Equipment_Type::Empty;

    case Equipment_Type::Keyboard:
        return _Keyboard.Get_Equipment_Type() != Equipment_Type::Empty;

    case Equipment_Type::Mouse:
        return _Mouse.Get_Equipment_Type() != Equipment_Type::Empty;

    case Equipment_Type::BlueLight_Glasses:
        return _BlueLight_Glasses.Get_Equipment_Type() != Equipment_Type::Empty;

    case Equipment_Type::Headset:
        return _Headset.Get_Equipment_Type() != Equipment_Type::Empty;

    default:
        return false;
    }
}
//���â ���
void Currently_Equipped_Equipments::Print_Currently_Equipped_Equipments() const
{
    cout << "===== ���� ���� ���� ��� =====" << endl;

    cout << "[Engine]" << endl;
    _Unreal_Engine_Version.Print_Equipment_Info(); 

    cout << "[Keyboard]" << endl;
    _Keyboard.Print_Equipment_Info();

    cout << "[Mouse]" << endl;
    _Mouse.Print_Equipment_Info();

    cout << "[BlueLight Glasses]" << endl;
    _BlueLight_Glasses.Print_Equipment_Info();

    cout << "[Headset]" << endl;
    _Headset.Print_Equipment_Info();

    cout << "==============================" << endl;
    return;
}

//����
bool Currently_Equipped_Equipments::Unequip_Equipment_To_Inventory(Inventory_For_Equipments_Only& equipment_inventory
)
{

    cout << R"(
� ��� �����Ͻðڽ��ϱ�?

1. Engine
2. Keyboard
3. Mouse
4. BlueLight Glasses
5. Headset
0. ���
)" << endl;

    int Choose;
    cin >> Choose;

    switch (Choose)
    {
    case 1:
    {
        return Unequip_One_Equipment(
            _Unreal_Engine_Version,
            equipment_inventory,
            "Engine"
        );
    }

    case 2:
    {
        return Unequip_One_Equipment(
            _Keyboard,
            equipment_inventory,
            "Keyboard"
        );
    }

    case 3:
    {
        return Unequip_One_Equipment(
            _Mouse,
            equipment_inventory,
            "Mouse"
        );
    }

    case 4:
    {
        return Unequip_One_Equipment(
            _BlueLight_Glasses,
            equipment_inventory,
            "BlueLight Glasses"
        );
    }

    case 5:
    {
        return Unequip_One_Equipment(
            _Headset,
            equipment_inventory,
            "Headset"
        );
    }

    case 0:
    {
        cout << "����ߴ�." << endl;
        return false;
    }

    default:
    {
        cout << "�߸��� �Է��̴�!" << endl;
        return false;
    }
    }
}

//�ϳ� ����
bool Currently_Equipped_Equipments::Unequip_One_Equipment(Equipment& equipped_item, Inventory_For_Equipments_Only& equipment_inventory, const string& slot_name)
{
    if (equipped_item.Get_Equipment_Type() == Equipment_Type::Empty)
    {
        cout << "������ " << slot_name << "��(��) ����!" << endl;
        return false;
    }

    bool Is_Added = equipment_inventory.Add_Equipment(equipped_item);

    if (Is_Added == false)
    {
        cout << "�κ��丮�� ���� ���� ������ ����ߴ�!" << endl;
        return false;
    }

    equipped_item = Equipment();

    cout << slot_name << " ��� �����ߴ�!" << endl;
    return true;
}


//��� �� ���� ���
Equipment_Stats Currently_Equipped_Equipments::Get_All_Equipments_Stats() const
{
    Equipment_Stats total_stats;

    total_stats.Attack = 0;
    total_stats.Defence = 0;
    total_stats.Enhance_Level = 0;
    total_stats.Grade_Score = 0;


    // Engine
    total_stats.Attack += _Unreal_Engine_Version.Get_Attack_Stat();
    total_stats.Defence += _Unreal_Engine_Version.Get_Defence_Stat();
    total_stats.Enhance_Level += _Unreal_Engine_Version.Get_Enhance_Level();
    total_stats.Grade_Score += static_cast<int>(_Unreal_Engine_Version.Get_Grade());


    // Keyboard
    total_stats.Attack += _Keyboard.Get_Attack_Stat();
    total_stats.Defence += _Keyboard.Get_Defence_Stat();
    total_stats.Enhance_Level += _Keyboard.Get_Enhance_Level();
    total_stats.Grade_Score += static_cast<int>(_Keyboard.Get_Grade());


    // Mouse
    total_stats.Attack += _Mouse.Get_Attack_Stat();
    total_stats.Defence += _Mouse.Get_Defence_Stat();
    total_stats.Enhance_Level += _Mouse.Get_Enhance_Level();
    total_stats.Grade_Score += static_cast<int>(_Mouse.Get_Grade());


    // BlueLight Glasses
    total_stats.Attack += _BlueLight_Glasses.Get_Attack_Stat();
    total_stats.Defence += _BlueLight_Glasses.Get_Defence_Stat();
    total_stats.Enhance_Level += _BlueLight_Glasses.Get_Enhance_Level();
    total_stats.Grade_Score += static_cast<int>(_BlueLight_Glasses.Get_Grade());


    // Headset
    total_stats.Attack += _Headset.Get_Attack_Stat();
    total_stats.Defence += _Headset.Get_Defence_Stat();
    total_stats.Enhance_Level += _Headset.Get_Enhance_Level();
    total_stats.Grade_Score += static_cast<int>(_Headset.Get_Grade());


    return total_stats;
}

//��� �� ��� ����ȭ
int Currently_Equipped_Equipments::Get_All_Equipments_Grade_Score() const
{
    int Total_Grade_Score = 0;


    Total_Grade_Score += static_cast<int>(_Unreal_Engine_Version.Get_Grade());
    Total_Grade_Score += static_cast<int>(_Keyboard.Get_Grade());
    Total_Grade_Score += static_cast<int>(_Mouse.Get_Grade());
    Total_Grade_Score += static_cast<int>(_BlueLight_Glasses.Get_Grade());
    Total_Grade_Score += static_cast<int>(_Headset.Get_Grade());


    return Total_Grade_Score;
}




//-----------------��� ���� �κ��丮------------------------------------


//��� ���� �κ��丮 �⺻ ������
Inventory_For_Equipments_Only::Inventory_For_Equipments_Only()
    : _Equipment_Current_Count(0),
    _Equipment_Max_Count(10),
    _Equipment_Max_Weight(100)
{
}


//��� ���� �κ��丮 �ִ� ���� ���� ������
Inventory_For_Equipments_Only::Inventory_For_Equipments_Only(int max_count,int max_weight)
    : _Equipment_Current_Count(0),
    _Equipment_Max_Count(max_count),
    _Equipment_Max_Weight(max_weight)
{
}


//��� �߰�
bool Inventory_For_Equipments_Only::Add_Equipment(const Equipment& equipment)
{
    // 1. ���� �˻�
    while (Get_Total_Equipment_Weight() + equipment.Get_Equipment_Weight() > _Equipment_Max_Weight)
    {
        cout << "��� �κ��丮�� ���԰� �� �뷮�� �ʰ��ߴ�! ��� ���� ���ΰ�?" << endl;
        cout << "1. ������" << endl;
        cout << "2. ���" << endl;

        int Choose_To_Get_Rid_Of_Equipment;
        cin >> Choose_To_Get_Rid_Of_Equipment;

        if (Choose_To_Get_Rid_Of_Equipment == 1)
        {
            Throw_Away_Equipment();
        }
        else if (Choose_To_Get_Rid_Of_Equipment == 2)
        {
            return false;
        }
        else
        {
            cout << "�߸��� �Է��̴�!" << endl;
        }
    }

    // 2. ���� �˻�
    while (_Equipment_Current_Count >= _Equipment_Max_Count)
    {
        cout << "������ ���� á��!" << endl;
        cout << "��� �������� 1�� �ƴϸ� 2���� ������!" << endl;

        int Choose_To_Get_Rid_Of_Equipment;
        cin >> Choose_To_Get_Rid_Of_Equipment;

        if (Choose_To_Get_Rid_Of_Equipment == 1)
        {
            Throw_Away_Equipment();

            if (_Equipment_Current_Count >= _Equipment_Max_Count)
            {
                cout << "���� ������ �����ϴ�!" << endl;
            }
        }
        else if (Choose_To_Get_Rid_Of_Equipment == 2)
        {
            return false;
        }
        else
        {
            cout << "�߸��� �Է��̴�! �ٽ� �Է��϶�." << endl;
        }
    }

    // 3. ��� �߰�
    _Equipments.push_back(equipment);
    _Equipment_Current_Count++;

    cout << equipment.Get_Equipment_Name() << "��(��) ȹ���ߴ�!" << endl;

    return true;
}


//��� �κ��丮 ���
void Inventory_For_Equipments_Only::Print_Equipment_Inventory() const
{
    if (_Equipment_Current_Count == 0)
    {
        cout << "�� �����!" << endl;
        return;
    }
    cout << endl;
    cout << "========================================" << endl;
    cout << "          ��� ���� �κ��丮" << endl;
    cout << "========================================" << endl;
    cout << "���� ��� �� : " << _Equipment_Current_Count << " / " << _Equipment_Max_Count << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < _Equipment_Current_Count; i++)
    {
        cout << "[" << i + 1 << "�� ���]" << endl;
        cout << "----------------------------------------" << endl;
        _Equipments[i].Print_Equipment_Info();
        cout << endl;
    }
}


//���� ��� ���� ��ȸ
int Inventory_For_Equipments_Only::Get_Equipment_Current_Count() const
{
    return _Equipment_Current_Count;
}


//�ִ� ��� ���� ��ȸ
int Inventory_For_Equipments_Only::Get_Equipment_Max_Count() const
{
    return _Equipment_Max_Count;
}


//�ε����� ��� ��ȸ
Equipment Inventory_For_Equipments_Only::Get_Equipment_By_Index(int index) const
{
    if (index<0 || index>= _Equipment_Current_Count)
    {
        cout << "�߸��� �����̴�!" << endl;
        return Equipment();
    }
    return _Equipments[index];
}


//��� ������
void Inventory_For_Equipments_Only::Throw_Away_Equipment()
{
    if (_Equipment_Current_Count==0)
    {
        cout << "�� �� ���� �� ����!" << endl;
        return;
    }
    Print_Equipment_Inventory();
    cout << "���� ��� ����!" << endl;
    int Choose_What_Equipment_To_Get_Rid_Of;
    cin >> Choose_What_Equipment_To_Get_Rid_Of;
    while  (Choose_What_Equipment_To_Get_Rid_Of < 1 || _Equipment_Current_Count < Choose_What_Equipment_To_Get_Rid_Of)
    {
        cout << "�߸��� �Է��̴�! �ٽ� �Է��϶�." << endl;
        cin >> Choose_What_Equipment_To_Get_Rid_Of;
    }
    int Vector_Index = Choose_What_Equipment_To_Get_Rid_Of-1;
    string Bye_Equipment = _Equipments[Vector_Index].Get_Equipment_Name();
    _Equipments.erase(_Equipments.begin() + Vector_Index);
    _Equipment_Current_Count--;
    cout << Bye_Equipment << "�� �ۺ��ߴ�!" << endl;
}


//��� �κ��丮 �ִ� ���� ĭ ����
void Inventory_For_Equipments_Only::Increase_Equipment_Max_Count(int increase_count)
{
    if (increase_count <= 0)
    {
        cout << "�������� �ùٸ��� �ʴ�!" << endl;
        return;
    }

    _Equipment_Max_Count += increase_count;
    cout << "��� ���� �κ��丮�� " << increase_count << "��ŭ �����ߴ�!" << endl;
}

//��� ����
void Inventory_For_Equipments_Only::Sort_Equipment_Inventory()
{
    cout << R"(
� �������� �����ұ��?
1. �̸���
2. ���ݷ¼�
3. ���¼�
4. ���Լ�
0. ���
)" << endl;

    int Sort_Choice;
    cin >> Sort_Choice;

    switch (Sort_Choice)
    {
    case 1:
    {
        sort(_Equipments.begin(), _Equipments.end(),
            [](const Equipment& a, const Equipment& b)
            {
                return a.Get_Equipment_Name() < b.Get_Equipment_Name();
            });
        break;
    }
    case 2:
    {
        sort(_Equipments.begin(), _Equipments.end(),
            [](const Equipment& a, const Equipment& b)
            {
                return a.Get_Attack_Stat() > b.Get_Attack_Stat();
            });
        break;
    }
    case 3:
    {
        sort(_Equipments.begin(), _Equipments.end(),
            [](const Equipment& a, const Equipment& b)
            {
                return a.Get_Defence_Stat() > b.Get_Defence_Stat();
            });
        break;
    }
    case 4:
    {
        sort(_Equipments.begin(), _Equipments.end(),
            [](const Equipment& a, const Equipment& b)
            {
                return a.Get_Equipment_Weight() > b.Get_Equipment_Weight();
            });
        break;
    }
    case 0:
    {
        cout << "������ ����Ѵ�." << endl;
        break;
    }
    default:
    {
        cout << "�߸��� �Է��̴�." << endl;
        break;
    }
    }
}

//��� ���� �ٲٱ�
void Inventory_For_Equipments_Only::Change_Equipment_Inventory_Order()
{
    if (_Equipments.empty())
    {
        cout << "��� �κ��丮�� ��� �ִ�." << endl;
        return;
    }

    if (_Equipments.size() < 2)
    {
        cout << "������ �ٲ� ��� �����ϴ�." << endl;
        return;
    }

    Print_Equipment_Inventory();

    int First_Selected_Index;
    int Second_Selected_Index;

    cout << "ù ��°�� �ٲ� ��� ��ȣ�� �Է��϶�! : ";
    cin >> First_Selected_Index;

    while (First_Selected_Index < 1 || First_Selected_Index > _Equipment_Current_Count)
    {
        cout << "�߸��� �Է��̴�. �ٽ� �Է��϶�! : ";
        cin >> First_Selected_Index;
    }

    cout << "�� ��°�� �ٲ� ��� ��ȣ�� �Է��϶�! : ";
    cin >> Second_Selected_Index;

    while (Second_Selected_Index < 1 || Second_Selected_Index > _Equipment_Current_Count)
    {
        cout << "�߸��� �Է��̴�. �ٽ� �Է��϶�! : ";
        cin >> Second_Selected_Index;
    }

    if (First_Selected_Index == Second_Selected_Index)
    {
        cout << "���� ��� �����ߴ�. ������ �������� �ʴ´�." << endl;
        return;
    }

    int First_Vector_Index = First_Selected_Index - 1;
    int Second_Vector_Index = Second_Selected_Index - 1;

    swap(_Equipments[First_Vector_Index], _Equipments[Second_Vector_Index]);

    cout << "��� ������ �����ߴ�." << endl;
}

//��� ����
void Inventory_For_Equipments_Only::Equip_Equipment_From_Inventory(Currently_Equipped_Equipments& equipped)
{
    if (_Equipments.empty())
    {
        cout << "������ ��� ����." << endl;
        return;
    }

    Print_Equipment_Inventory();

    int Selected_Index;

    cout << "������ ��� ��ȣ�� �Է��ϼ���: ";
    cin >> Selected_Index;

    while (Selected_Index < 1 || Selected_Index > _Equipment_Current_Count)
    {
        cout << "�߸��� �Է��̴�. �ٽ� �Է��ϼ���: ";
        cin >> Selected_Index;
    }

    int Vector_Index = Selected_Index - 1;

    Equipment Selected_Equipment = _Equipments[Vector_Index];

    if (equipped.Equip_Equipment(Selected_Equipment))
    {
        _Equipments.erase(_Equipments.begin() + Vector_Index);
        _Equipment_Current_Count--;

        cout << Selected_Equipment.Get_Equipment_Name() << "��(��) �����ߴ�!" << endl;
    }
}

//���â ���� �� ����
int Inventory_For_Equipments_Only::Get_Total_Equipment_Weight() const
{
    int Total_Weight = 0;

    for (int i = 0; i < _Equipment_Current_Count; i++)
    {
        Total_Weight += _Equipments[i].Get_Equipment_Weight();
    }

    return Total_Weight;
}