#pragma once

#include "All_Recipes.h"
#include "Recipe_Repository.h"
#include "Inventory.h"
#include "Equipment.h"

class Craft_Work_Shop
{

private:

    Recipe_Repository recipe_repository;


public:


    Craft_Work_Shop();


    void Print_All_Recipes() const;


    bool Craft_Item(
        Inventory<Item>& inventory
    );


    bool Decomposition_Item(
        Inventory_For_Equipments_Only& equipment_inventory,
        Inventory<Item>& item_inventory
    );


    bool Enhance_Item(
        Equipment& equipment
    );

};