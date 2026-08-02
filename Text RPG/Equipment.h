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

public:
    Equipment();//1.기본 생성자
    Equipment(string equipment_name, int attack, int defence, Equipment_Grade grade);//2. 모든 걸 다 받는 생성자(아이템 저장소에서 이걸로 노가다 줄일예정)
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
};

class Equipment_Inventory
{
    private:
        Equipment* _Equipments;//장비창
        int _Current_Count;//현재 장비창에 들어있는 장비 갯수
        int _Max_Count;//장비창 최대 착용 가능 갯수
    public:
        Equipment_Inventory(int max_count);//1.장비창 생성자
        ~Equipment_Inventory();//2.장비창 소멸자
        bool Equip_Equipment(const Equipment& equipment);//3.장비 끼기
        Equipment* Get_Equipment_By_Index(int index);//4.인덱스로 장비 조회
        void Print_Equipment_Inventory() const;//5.장비창 출력
};