// Equipment.h
#pragma once
#include <string>
#include <vector>

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
{   Engine,     
    Keyboard,         
    Mouse,            
    BlueLight_Glasses, 
    Headset,           
    Empty
};
struct Equipment_Stats
{
    int Attack;
    int Defence;
    int Enhance_Level;
    int Grade_Score;
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
    Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade, Equipment_Type type, string art, string description, int weight);//2. 모든 걸 다 받는 생성자(아이템 저장소에서 이걸로 노가다 줄일예정)
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
    void Set_Equipment_Type(Equipment_Type type);//18. 장비 타입 설정
    string Equipment_Type_To_String(Equipment_Type type) const;//19.장비 타입 문자열로
};

//현재 장비창
class Inventory_For_Equipments_Only;
class Currently_Equipped_Equipments
{
    private:
        Equipment _Unreal_Engine_Version;
        Equipment _Keyboard;
        Equipment _Mouse;
        Equipment _BlueLight_Glasses;
        Equipment _Headset;
        //장비들

        bool Unequip_One_Equipment(Equipment& equipped_item, Inventory_For_Equipments_Only& equipment_inventory, const string& slot_name);

    public:
        Currently_Equipped_Equipments();//1.현재 끼고 있는 장비  생성자
        bool Equip_Equipment(const Equipment& equipment);//2.장비 끼기
        void Print_Currently_Equipped_Equipments() const;//3.현재 장비 중인 장비창 조회
        bool Unequip_Equipment_To_Inventory(Inventory_For_Equipments_Only& equipment_inventory );//4.장비 해제 
        int Get_All_Equipments_Grade_Score() const;//5.전체 등급 점수
        Equipment_Stats Get_All_Equipments_Stats() const;//6.전체 장비 스텟 가져오기
        bool Is_Equipment_Equipped(Equipment_Type type) const;// 7.장착 여부 확인

};

class Inventory_For_Equipments_Only
{
    private:
        vector<Equipment> _Equipments; //장비 아이템들을 저장하는 전용 보관함
        int _Equipment_Current_Count;//현재 장비창에 들어있는 장비 갯수
        int _Equipment_Max_Count;//장비창 최대 착용 가능 갯수
        int _Equipment_Max_Weight;//장비창 총 무게
    public:
        Inventory_For_Equipments_Only(); //1. 장비 전용 인벤토리 기본 생성자
        Inventory_For_Equipments_Only(int max_count, int max_weight); //2. 최대 장비 보관 개수를 직접 정하는 생성자
        bool Add_Equipment(const Equipment& equipment); //3. 장비를 인벤토리에 추가하는 함수
        void Print_Equipment_Inventory() const; //4. 현재 장비 인벤토리에 들어있는 장비 목록 출력
        int Get_Equipment_Current_Count() const; //5. 현재 보관 중인 장비 개수 조회
        int Get_Equipment_Max_Count() const; //6. 최대 보관 가능한 장비 개수 조회
        Equipment Get_Equipment_By_Index(int index) const; //7. 인덱스 번호로 특정 장비 조회
        void Throw_Away_Equipment(); //8. 장비 인벤토리에서 선택한 장비 버리기
        void Increase_Equipment_Max_Count(int increase_count); //9. 장비 인벤토리 최대 보관 칸 증가
        void Sort_Equipment_Inventory();//10.정렬 
        void Change_Equipment_Inventory_Order();//11.순서 변경
        void Equip_Equipment_From_Inventory(Currently_Equipped_Equipments& equipped);//12.장비 착용시키기
        int Get_Total_Equipment_Weight() const;//총무게
};