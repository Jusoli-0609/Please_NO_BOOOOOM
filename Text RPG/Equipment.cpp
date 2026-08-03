#include "Equipment.h"
#include <iostream>
using namespace std;

//기본생성자
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
        return "CPU";

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


//장비 착용
bool Currently_Equipped_Equipments::Equip_Equipment(const Equipment& equipment)
{
    Equipment_Type type = equipment.Get_Equipment_Type();
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
    return true;
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

//-----------------장비 전용 인벤토리------------------------------------


//장비 전용 인벤토리 기본 생성자
Inventory_For_Equipments_Only::Inventory_For_Equipments_Only()
    : _Current_Count(0),
    _Max_Count(10)
{
}


//장비 전용 인벤토리 최대 개수 설정 생성자
Inventory_For_Equipments_Only::Inventory_For_Equipments_Only(int max_count)
    : _Current_Count(0),
    _Max_Count(max_count)
{
}


//장비 추가
bool Inventory_For_Equipments_Only::Add_Equipment(const Equipment& equipment)
{
    //현재 장비 개수가 최대 장비 개수 이상인지 검사하는 조건문

    //장비 인벤토리가 가득 찼을 때 안내 문구 출력 자리

    //가득 찬 경우 추가 실패 반환 자리

    //_Equipments 벡터에 equipment를 추가하는 코드 자리

    //_Current_Count를 1 증가시키는 코드 자리

    //추가된 장비 이름 출력 자리

    //추가 성공 반환 자리
    return false;
}


//장비 인벤토리 출력
void Inventory_For_Equipments_Only::Print_Inventory() const
{
    //장비 인벤토리가 비어있는지 검사하는 조건문

    //비어있을 때 안내 문구 출력 자리

    //장비 인벤토리 제목 출력 자리

    //_Equipments를 처음부터 끝까지 순회하는 반복문 자리

    //사용자에게 보여줄 번호 출력 자리

    //각 장비의 Print_Equipment_Info 호출 자리
}


//현재 장비 개수 조회
int Inventory_For_Equipments_Only::Get_Current_Count() const
{
    //현재 장비 개수 반환 자리
    return 0;
}


//최대 장비 개수 조회
int Inventory_For_Equipments_Only::Get_Max_Count() const
{
    //최대 장비 개수 반환 자리
    return 0;
}


//인덱스로 장비 조회
Equipment Inventory_For_Equipments_Only::Get_Equipment_By_Index(int index) const
{
    //index가 0보다 작거나 _Current_Count 이상인지 검사하는 조건문

    //잘못된 index일 때 안내 문구 출력 자리

    //잘못된 index일 때 기본 Equipment 반환 자리

    //정상 index일 때 _Equipments[index] 반환 자리
    return Equipment();
}


//장비 버리기
void Inventory_For_Equipments_Only::Throw_Away_Equipment()
{
    //장비 인벤토리가 비어있는지 검사하는 조건문

    //비어있을 때 안내 문구 출력 자리

    //현재 장비 인벤토리 출력 함수 호출 자리

    //버릴 장비 번호를 입력받을 int 변수 선언 자리

    //입력받은 번호가 1보다 작거나 _Current_Count보다 큰지 검사하는 반복문 자리

    //사용자 입력 번호를 vector index로 바꾸는 변수 선언 자리

    //삭제할 장비 이름을 저장하는 string 변수 선언 자리

    //_Equipments에서 선택한 위치의 장비를 제거하는 코드 자리

    //_Current_Count를 1 감소시키는 코드 자리

    //삭제 완료 문구 출력 자리
}


//장비 인벤토리 최대 보관 칸 증가
void Inventory_For_Equipments_Only::Increase_Max_Count(int increase_count)
{
    //increase_count가 0보다 작거나 같은지 검사하는 조건문

    //_Max_Count에 increase_count를 더하는 코드 자리

    //장비 인벤토리 최대 칸 증가 안내 문구 출력 자리
}