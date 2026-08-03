#include "Equipment.h"
#include <iostream>

using namespace std;


int main()
{
    // 강신호의 마우스 생성
    Equipment Kang_Mouse(
        "강신호 튜터의 마우스",
        50,
        10,
        Equipment_Grade::Best,
        Equipment_Type::Mouse,
        R"(
        __________________
       |  강신호 마우스 |
       |________________|
        )",
        "강신호 튜터가 사용하던 전설의 마우스",
        5
    );


    // 현재 장비창 생성
    Currently_Equipped_Equipments Current_Equipment;


    // 마우스 장착
    Current_Equipment.Equip_Equipment(Kang_Mouse);


    cout << R"(


====================================
        현재 장착 장비 스텟 조회
====================================


)";


    // 여기서 Player가 가져가는 방식 테스트
    cout
        << "현재 장착 마우스 공격력 : "
        << Current_Equipment.Get_Mouse().Get_Attack_Stat()
        << endl;


    cout
        << "현재 장착 마우스 강화도 : +"
        << Current_Equipment.Get_Mouse().Get_Enhance_Level()
        << endl;


    cout
        << "현재 장착 마우스 등급 : "
        << Current_Equipment.Get_Mouse().Equipment_Grade_To_String(
            Current_Equipment.Get_Mouse().Get_Grade()
        )
        << endl;


    return 0;
}
