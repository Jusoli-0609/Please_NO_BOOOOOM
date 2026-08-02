// Equipment.h
#pragma once
#include <string>
using namespace std;

enum class Equipment_Grade
{
    Empty,
    Worst,
    Low,
    Middle,
    High,
    Best
};

enum class Equipment_Type
{
    CPU,            
    GPU,             
    Keyboard,         
    Mouse,            
    BlueLight_Glasses, 
    Headset,           
    Virtual_Character,  // 문승현 튜터 고양이 버츄얼(굳이인 거 같은데 미르님 선택에 맡기겠습니다)
    Empty
};

//장비 자세한 설명
class Equipment
{
private:
    string _Equipment_Name;//장비 이름
    int _Attack_Stat;//장비 공격값
    int _Defence_Stat;//장비 기본 방어값
    Equipment_Grade _Grade;//장비 등급
    int _Enhance_Level;//장비 강화 레벨
    int _Equipment_Weight;//장비 무게
    string _Equipment_Description;
    Equipment_Type _Equipment_Type;
    string _Equipment__Ascii_Art;

public:
    Equipment();//1.기본 생성자
    Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade,Equipment_Type type,string _Equipment__Ascii_Art);//2. 모든 걸 다 받는 생성자(아이템 저장소에서 이걸로 노가다 줄일예정)
    int Get_Enhance_Level() const;//3.강화 레벨 조회
    void Set_Enhance_Level(int enhance_level);//4.강화 레벨 설정
    int Get_Attack_Stat() const;//5.장비 공격 스텟 조회
    void Set_Attack_Stat(int attack_stat);//6.장비 공격 스텟 설정
    int Get_Defence_Stat() const;//7. 장비 방어력 스텟 조회
    void Set_Defence_Stat(int defence_stat);//8. 방어력 스텟 설정
    void Print_Equipment_Info() const;//9.장비 정보 출력
    string Get_Equipment_Name() const;//10.장비 이름 조회
    Equipment_Grade Get_Grade() const;//11. 장비 등급 조회
    string Equipment_Grade_To_String(Equipment_Grade grade) const;//12.장비 등급 문자열 출력으로
    int Get_Equipment_Weight() const;//12. 장비 무게 조회
    void Set_Equipment_Weight(int weight);//13. 장비 무게 설정
    string Get_Equipment_Description() const;//14.장비 설명 조회
    void Set_Equipment_Description(string description);//15.장비 설명 설정
    void Set_Equipment_Name(string name);//16.장비 이름 설정
    Equipment_Type Get_Equipment_Type() const;// 17. 장비 타입 조회
    void Set_Equipment_Type(Equipment_Type type);//
    string Equipment_Type_To_String(Equipment_Type type) const;
};

//현재 장비창
class Currently_Equipped_Equipments
{
    private:
        Equipment _Unreal_Engine_Version;
        Equipment _Keyboard;
        Equipment _Mouse;
        Equipment _BlueLight_Glasses;
        Equipment _Headset;
        //장비들
    public:
        Currently_Equipped_Equipments();//1.현재 끼고 있는 장비  생성자
        ~Currently_Equipped_Equipments();//2.장비창 소멸자
        bool Equip_Equipment(const Equipment& equipment);//3.장비 끼기
        void Print_Currently_Equipped_Equipments() const;//4.현재 장비 중인 장비창 조회
};

class Inventory_For_Equipments_Only
{
private:
    int _Current_Count;//현재 장비창에 들어있는 장비 갯수
    int _Max_Count;//장비창 최대 착용 가능 갯수
};