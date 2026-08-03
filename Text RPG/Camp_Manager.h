#pragma once
#include "Inventory.h"
#include "Equipment.h"
#include "Items_Equipments_Repository.h"


class Camp_Manager
{
public:
    Camp_Manager(Player& player,
        Inventory<Item>& inventory,
        Inventory_For_Equipments_Only& inventory_for_equipments,
        Currently_Equipped_Equipments& currently_equipped_equipments);
   
    
    void Open_Camp_Menu();

private:
    bool Received_Basic_Items = false;
    void Open_Pep_Store_Menu();
    void Open_General_Store_Menu();
    void Open_Loot_Shop_Menu();
    void Open_Cookie_Blacksmith_Menu();
    void Give_Basic_Training_Item();

    Player& player;
    Inventory<Item>& inventory;
    Inventory_For_Equipments_Only& inventory_for_equipments;
    Currently_Equipped_Equipments& currently_equipped_equipments;

    // TODO: 골드 데이터에 접근하기 위한 멤버 변수 또는 참조 선언
};

