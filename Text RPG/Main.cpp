#include "Equipment.h"
#include <iostream>

using namespace std;

int main()
{
    // 1. 강신호의 마우스 획득
    Equipment KangShinho_Mouse(
        "강신호의 마우스",
        50,                         // 공격력
        10,                         // 방어력
        Equipment_Grade::Best,
        Equipment_Type::Mouse,
        R"(
        __________________
       |                  |
       |   KSH MOUSE      |
       |__________________|
        )",
        "강신호 튜터가 사용했던 전설의 마우스",
        3
    );


    // 2. 장비 전용 인벤토리 생성
    Inventory_For_Equipments_Only Equipment_Inventory;


    // 3. 마우스 획득
    Equipment_Inventory.Add_Equipment(KangShinho_Mouse);


    cout << endl;
    cout << "===== 현재 장비 인벤토리 =====" << endl;

    Equipment_Inventory.Print_Equipment_Inventory();


    // 4. 현재 장비창 생성
    Currently_Equipped_Equipments Current_Equipment;


    // 5. 인벤토리에서 장착
    Equipment_Inventory.Equip_Equipment_From_Inventory(Current_Equipment);


    cout << endl;
    cout << "================================" << endl;
    cout << "       현재 장착 장비 확인       " << endl;
    cout << "================================" << endl;


    // 6. 장착 모습 출력
    Current_Equipment.Print_Currently_Equipped_Equipments();


    cout << endl;
    cout << "================================" << endl;
    cout << "     현재 마우스 공격력 조회     " << endl;
    cout << "================================" << endl;


    // 7. Player가 가져가는 것처럼 조회
    cout << Current_Equipment.Get_Mouse().Get_Attack_Stat() << endl;


    return 0;
}