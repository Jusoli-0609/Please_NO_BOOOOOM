#pragma once
#include "Inventory.h"
#include "Equipment.h"
#include "Craft_Item.h"

class Player;

class Camp_Manager
{
public: 
	Camp_Manager
	(
		Player& player,
		Inventory<Item>& inventory,
		Inventory_For_Equipments_Only&
		inventory_for_equipments,
		Currently_Equipped_Equipments&
		currently_equipped_equipments
	);

	void Open_Camp_Menu();

private:
	bool Received_Basic_Items = false;

	void Give_Basic_Training_Item();
	void Open_Pep_Store_Menu();
	void Open_General_Store_Menu();
	void Open_Loot_Shop_Menu();
	void Open_Cookie_Blacksmith_Menu();

	Craft_Work_Shop craft_work_shop;
	Player& player;
	Inventory<Item>& inventory;
	Inventory_For_Equipments_Only& inventory_for_equipments;
	Currently_Equipped_Equipments& currently_equipped_equipments;
};

