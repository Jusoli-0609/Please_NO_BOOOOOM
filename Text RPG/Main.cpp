#include <iostream>
#include "Equipment.h"

using namespace std;

int main()
{
    Currently_Equipped_Equipments Current_Equipment;

    Inventory_For_Equipments_Only Equipment_Inventory;


    // 강신호의 마우스 생성
    Equipment KangShinho_Mouse(
        "강신호의 마우스",
        50,
        10,
        Equipment_Grade::Best,
        Equipment_Type::Mouse,
        R"(
        ______________
       |   강신호     |
       |    Mouse     |
       |______________|
        )",
        "강신호 튜터가 사용하던 마우스",
        3
    );


    // 강화도 +1 설정
    KangShinho_Mouse.Set_Enhance_Level(1);


    cout << "===== 강신호의 마우스 획득 =====" << endl;

    // 인벤토리에 추가
    Equipment_Inventory.Add_Equipment(KangShinho_Mouse);


    cout << endl;
    cout << "===== 장비 착용 =====" << endl;

    // 장착
    Equipment_Inventory.Equip_Equipment_From_Inventory(Current_Equipment);


    cout << endl;
    cout << "===== 현재 장착 장비 =====" << endl;

    Current_Equipment.Print_Currently_Equipped_Equipments();


    cout << endl;
    cout << "===== Player 조회 테스트 =====" << endl;


    Equipment_Stats Stats = Current_Equipment.Get_All_Equipments_Stats();


    cout << "총 공격력 : " << Stats.Attack << endl;
    cout << "총 방어력 : " << Stats.Defence << endl;
    cout << "총 강화도 : +" << Stats.Enhance_Level << endl;
    cout << "총 장비 등급 점수 : " << Stats.Grade_Score << endl;


    return 0;
}