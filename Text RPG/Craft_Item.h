#pragma once

#include "All_Recipes.h"
#include "Recipe_Repository.h"
#include "Items_Equipments_Repository.h"
#include "Inventory.h"
#include "Equipment.h"
#include <string>

class Craft_Work_Shop
{
private:
	Recipe_Repository
		recipe_repository;

	Items_Equipments_Repository
		equipment_repository;

	int Get_Item_Count(Inventory<Item>& inventory, const std::string& item_Name) const;

public:
	Craft_Work_Shop();

	void Print_Recipes_By_Level(int equipment_Level) const;
	bool Craft_Item(Inventory<Item>& item_inventory,Inventory_For_Equipments_Only&equipment_inventory);
	bool Decomposition_Item(Inventory_For_Equipments_Only&equipment_inventory,Inventory<Item>& item_inventory);
	bool Enhance_Item(Inventory_For_Equipments_Only& equipment_inventory, Inventory<Item>& inventory);
};