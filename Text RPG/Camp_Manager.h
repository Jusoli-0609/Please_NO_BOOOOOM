#pragma once
#include "Inventory.h"
#include "Equipment.h"
#include "Items_Equipments_Repository.h"

class Camp_Manager
{
public:
    Camp_Manager();

    void Open_Camp_Menu();

private:
    void Open_Pep_Store_Menu();
    void Open_General_Store_Menu();
    void Open_Loot_Shop_Menu();
    void Open_Cookie_Blacksmith_Menu();

    void Give_Basic_Training_Item();

    // TODO: 플레이어 또는 인벤토리 참조 변수 선언
    // TODO: 골드 데이터에 접근하기 위한 멤버 변수 또는 참조 선언
};