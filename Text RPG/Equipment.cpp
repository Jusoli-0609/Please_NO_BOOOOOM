#include "Equipment.h"
#include <iostream>
#include <algorithm>
#include "Player.h"
using namespace std;


//플레이어 파트에서 새로 추가한 내용
//장비 장착 부위별 id 생성용
namespace
{
    string Get_Equipment_Modifier_ID(
        Equipment_Type equipment_type)
    {
        switch (equipment_type)
        {
        case Equipment_Type::Engine:
        {
            return "Equipment_Engine";
        }

        case Equipment_Type::Keyboard:
        {
            return "Equipment_Keyboard";
        }

        case Equipment_Type::Mouse:
        {
            return "Equipment_Mouse";
        }

        case Equipment_Type::BlueLight_Glasses:
        {
            return "Equipment_BlueLight_Glasses";
        }

        case Equipment_Type::Headset:
        {
            return "Equipment_Headset";
        }

        default:
        {
            return "";
        }
        }
    }

    Stat_Modifier Create_Equipment_Modifier(
        const Equipment& equipment)
    {
        Stat_Modifier Equipment_Modifier;

        Equipment_Modifier.id =
            Get_Equipment_Modifier_ID(
                equipment.Get_Equipment_Type()
            );

        Equipment_Modifier.name =
            equipment.Get_Equipment_Name();

        Equipment_Modifier.type =
            Stat_Modifier_Type::Equipment;

        Equipment_Modifier.flat.atk =
            equipment.Get_Attack_Stat();

        Equipment_Modifier.flat.def =
            equipment.Get_Defence_Stat();

        Equipment_Modifier.remainingTurns = -1;

        return Equipment_Modifier;
    }
}
//플레이어 파트에서 새로 추가한 내용


//기본생성자
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

//아이템 다 대입 생성자 뭔말알?
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
    cout << "장비 설명: " << _Equipment_Description << endl;
    cout << "장비 타입: " << Equipment_Type_To_String(_Equipment_Type) << endl;
    cout <<  "장비 무게: " << _Equipment_Weight << endl;
    cout << "공격력: " << _Attack_Stat << endl;
    cout << "방어력: " << _Defence_Stat << endl;
    cout << "등급: " << Equipment_Grade_To_String(_Grade) << endl;
    cout << "강화 레벨: +" << _Enhance_Level << endl;
    cout << _Equipment__Ascii_Art << endl;
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
    
}


bool Currently_Equipped_Equipments::Equip_Equipment(
    const Equipment& equipment,
    Player* player)
{
    if (player == nullptr)
    {
        cout << "플레이어 정보가 없습니다!" << endl;
        return false;
    }

    Equipment_Type type = equipment.Get_Equipment_Type();

    if (Is_Equipment_Equipped(type))
    {
        cout << "이미 같은 부위의 장비를 끼고 있다! 해제하고  다시하자!" << endl;
        return false;
    }


    switch (type)
    {
    case Equipment_Type::Engine:
    {
        _Unreal_Engine_Version = equipment;
        break;
    }

    case Equipment_Type::Keyboard:
    {
        _Keyboard = equipment;
        break;
    }

    case Equipment_Type::Mouse:
    {
        _Mouse = equipment;
        break;
    }

    case Equipment_Type::BlueLight_Glasses:
    {
        _BlueLight_Glasses = equipment;
        break;
    }

    case Equipment_Type::Headset:
    {
        _Headset = equipment;
        break;
    }

    default:
    {
        cout << "착용할 수 없는 아이템이다!" << endl;
        return false;
    }
    }

    Stat_Modifier Equipment_Modifier =
        Create_Equipment_Modifier(equipment);

    player->Add_Stat_Modifier(
        Equipment_Modifier
    );


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
//장비창 출력

void Currently_Equipped_Equipments::Print_Currently_Equipped_Equipments() const
{
    cout << "===== 현재 장착 중인 장비 =====" << endl;

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

//각 호출마다 Player 추가
//해제
bool Currently_Equipped_Equipments::Unequip_Equipment_To_Inventory(Inventory_For_Equipments_Only& equipment_inventory, Player* player)
{

    cout << R"(
어떤 장비를 해제하시겠습니까?

1. Engine
2. Keyboard
3. Mouse
4. BlueLight Glasses
5. Headset
0. 취소
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
            "Engine",
            player
        );
    }

    case 2:
    {
        return Unequip_One_Equipment(
            _Keyboard,
            equipment_inventory,
            "Keyboard",
            player
        );
    }

    case 3:
    {
        return Unequip_One_Equipment(
            _Mouse,
            equipment_inventory,
            "Mouse",
            player
        );
    }

    case 4:
    {
        return Unequip_One_Equipment(
            _BlueLight_Glasses,
            equipment_inventory,
            "BlueLight Glasses",
            player
        );
    }

    case 5:
    {
        return Unequip_One_Equipment(
            _Headset,
            equipment_inventory,
            "Headset",
			player
        );
    }

    case 0:
    {
        cout << "취소했다." << endl;
        return false;
    }

    default:
    {
        cout << "잘못된 입력이다!" << endl;
        return false;
    }
    }
}

bool Unequip_One_Equipment(
    Equipment& equipped_item,
    Inventory_For_Equipments_Only& equipment_inventory,
    const string& slot_name,
    Player* player)
{
    if (equipped_item.Get_Equipment_Type() == Equipment_Type::Empty)
    {
        cout << "장착된 " << slot_name << "이(가) 없다!" << endl;
        return false;
    }

    bool Is_Added = equipment_inventory.Add_Equipment(equipped_item);

    if (Is_Added == false)
    {
        cout << "인벤토리에 넣지 못해 해제를 취소했다!" << endl;
        return false;
    }

    equipped_item = Equipment();

    cout << slot_name << " 장비를 해제했다!" << endl;
    return true;
}

bool Currently_Equipped_Equipments::Unequip_One_Equipment(
    Equipment& equipped_item,
    Inventory_For_Equipments_Only& equipment_inventory,
    const string& slot_name,
    Player* player)
{
    if (player == nullptr)
    {
        cout << "플레이어 정보가 없다!" << endl;
        return false;
    }

    if (equipped_item.Get_Equipment_Type() ==
        Equipment_Type::Empty)
    {
        cout
            << "장착 된 "
            << slot_name
            << " 이(가) 없다!"
            << endl;

        return false;
    }

    bool Is_Added =
        equipment_inventory.Add_Equipment(
            equipped_item
        );

    if (Is_Added == false)
    {
        cout
            << "인벤토리에 넣지 못해 해제를 취소했다!"
            << endl;

        return false;
    }

    string Modifier_ID =
        Get_Equipment_Modifier_ID(
            equipped_item.Get_Equipment_Type()
        );

    if (Modifier_ID.empty() == false)
    {
        player->Remove_Stat_Modifier(
            Modifier_ID
        );
    }

    equipped_item = Equipment();

    cout
        << slot_name
        << " 장비를 해제했다!"
        << endl;

    return true;
}



//총 스텟 가져오기
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

//-----------------현재 장착된 아이템 인벤토리------------------------------------








//-----------------장비 전용 인벤토리------------------------------------


//장비 전용 인벤토리 기본 생성자
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


//장비 추가
bool Inventory_For_Equipments_Only::Add_Equipment(const Equipment& equipment)
{
    // 1. ���� �˻�
    while (Get_Total_Equipment_Weight() + equipment.Get_Equipment_Weight() > _Equipment_Max_Weight)
    {
        cout << "슬롯이 가득 찼다!" << endl;
        cout << "장비를 버릴려면 1번 아니면 2번을 눌러라!" << endl;
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
    cout << equipment.Get_Equipment_Name() << "을(를) 획득했다!" << endl;
    return true;
}


//장비 인벤토리 출력
void Inventory_For_Equipments_Only::Print_Equipment_Inventory() const
{
    if (_Equipment_Current_Count == 0)
    {
        cout << "텅 비었다!" << endl;
        return;
    }
    cout << endl;
    cout << "========================================" << endl;
    cout << "          장비 전용 인벤토리" << endl;
    cout << "========================================" << endl;
    cout << "보유 장비 수 : " << _Equipment_Current_Count << " / " << _Equipment_Max_Count << endl;
    cout << "----------------------------------------" << endl;

    for (int i = 0; i < _Equipment_Current_Count; i++)
    {
        cout << "[" << i + 1 << "번 장비]" << endl;
        cout << "----------------------------------------" << endl;
        _Equipments[i].Print_Equipment_Info();
        cout << endl;
    }
}


//현재 장비 개수 조회
int Inventory_For_Equipments_Only::Get_Equipment_Current_Count() const
{
    return _Equipment_Current_Count;
}


//최대 장비 개수 조회
int Inventory_For_Equipments_Only::Get_Equipment_Max_Count() const
{
    return _Equipment_Max_Count;
}


//인덱스로 장비 조회
Equipment Inventory_For_Equipments_Only::Get_Equipment_By_Index(int index) const
{
    if (index<0 || index>= _Equipment_Current_Count)
    {
        cout << "잘못된 선택이다!" << endl;
        return Equipment();
    }
    return _Equipments[index];
}


//장비 버리기
void Inventory_For_Equipments_Only::Throw_Away_Equipment()
{
    if (_Equipment_Current_Count==0)
    {
        cout << "텅 비어서 버릴 게 없다!" << endl;
        return;
    }
    Print_Equipment_Inventory();
    cout << "버릴 장비를 골라라!" << endl;
    int Choose_What_Equipment_To_Get_Rid_Of;
    cin >> Choose_What_Equipment_To_Get_Rid_Of;
    while  (Choose_What_Equipment_To_Get_Rid_Of < 1 || _Equipment_Current_Count < Choose_What_Equipment_To_Get_Rid_Of)
    {
        cout << "잘못된 입력이다! 다시 입력하라." << endl;
        cin >> Choose_What_Equipment_To_Get_Rid_Of;
    }
    int Vector_Index = Choose_What_Equipment_To_Get_Rid_Of-1;
    string Bye_Equipment = _Equipments[Vector_Index].Get_Equipment_Name();
    _Equipments.erase(_Equipments.begin() + Vector_Index);
    _Equipment_Current_Count--;
    cout << Bye_Equipment << "과 작별했다!" << endl;
}


//장비 인벤토리 최대 보관 칸 증가
void Inventory_For_Equipments_Only::Increase_Equipment_Max_Count(int increase_count)
{
    if (increase_count <= 0)
    {
        cout << "증가량이 올바르지 않다!" << endl;
        return;
    }

    _Equipment_Max_Count += increase_count;
    cout << "장비 전용 인벤토리가 " << increase_count << "만큼 증가했다!" << endl;
}

//장비 정렬
void Inventory_For_Equipments_Only::Sort_Equipment_Inventory()
{
    cout << R"(
어떤 기준으로 정렬할까요?
1. 이름순
2. 공격력순
3. 방어력순
4. 무게순
0. 취소
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
        cout << "정렬을 취소한다." << endl;
        break;
    }
    default:
    {
        cout << "잘못된 입력이다." << endl;
        break;
    }
    }
}

//장비 순서 바꾸기
void Inventory_For_Equipments_Only::Change_Equipment_Inventory_Order()
{
    if (_Equipments.empty())
    {
        cout << "장비 인벤토리가 비어 있다." << endl;
        return;
    }

    if (_Equipments.size() < 2)
    {
        cout << "순서를 바꿀 장비가 부족하다." << endl;
        return;
    }

    Print_Equipment_Inventory();

    int First_Selected_Index;
    int Second_Selected_Index;

    cout << "첫 번째로 바꿀 장비 번호를 입력하라! : ";
    cin >> First_Selected_Index;

    while (First_Selected_Index < 1 || First_Selected_Index > _Equipment_Current_Count)
    {
        cout << "잘못된 입력이다. 다시 입력하라! : ";
        cin >> First_Selected_Index;
    }

    cout << "두 번째로 바꿀 장비 번호를 입력하라! : ";
    cin >> Second_Selected_Index;

    while (Second_Selected_Index < 1 || Second_Selected_Index > _Equipment_Current_Count)
    {
        cout << "잘못된 입력이다. 다시 입력하라! : ";
        cin >> Second_Selected_Index;
    }

    if (First_Selected_Index == Second_Selected_Index)
    {
        cout << "같은 장비를 선택했다. 순서를 변경하지 않는다." << endl;
        return;
    }

    int First_Vector_Index = First_Selected_Index - 1;
    int Second_Vector_Index = Second_Selected_Index - 1;

    swap(_Equipments[First_Vector_Index], _Equipments[Second_Vector_Index]);

    cout << "장비 순서를 변경했다." << endl;
}
//인수에 Player 추가
//장비 착용
void Inventory_For_Equipments_Only::Equip_Equipment_From_Inventory(Currently_Equipped_Equipments& equipped, Player* player)
{
    if (_Equipments.empty())
    {
        cout << "장착할 장비가 없다." << endl;
        return;
    }

    Print_Equipment_Inventory();

    int Selected_Index;

    cout << "장착할 장비 번호를 입력하세요: ";
    cin >> Selected_Index;

    while (Selected_Index < 1 || Selected_Index > _Equipment_Current_Count)
    {
        cout << "잘못된 입력이다. 다시 입력하세요: ";
        cin >> Selected_Index;
    }

    int Vector_Index = Selected_Index - 1;

    Equipment Selected_Equipment = _Equipments[Vector_Index];
	//인수에 Player 추가
    if (equipped.Equip_Equipment(Selected_Equipment, player))
    {
        _Equipments.erase(_Equipments.begin() + Vector_Index);
        _Equipment_Current_Count--;

        cout << Selected_Equipment.Get_Equipment_Name() << "을(를) 장착했다!" << endl;
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