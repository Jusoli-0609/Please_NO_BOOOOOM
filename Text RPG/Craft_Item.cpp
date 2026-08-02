#include "Craft_Item.h"
#include "All_Recipes.h"
#include <iostream>

using namespace std;

Craft_Work_Shop::Craft_Work_Shop()
{
    All_Recipes hpPotion;

    hpPotion.potionName = "HP포션";
    hpPotion.ingredient1Name = "허브";
    hpPotion.ingredient1Count = 1;
    hpPotion.ingredient2Name = "맑은물";
    hpPotion.ingredient2Count = 1;

    recipes.push_back(hpPotion);

    All_Recipes staminaPotion;

    staminaPotion.potionName = "스태미나포션";
    staminaPotion.ingredient1Name = "허브";
    staminaPotion.ingredient1Count = 1;
    staminaPotion.ingredient2Name = "베리";
    staminaPotion.ingredient2Count = 1;

    recipes.push_back(staminaPotion);

    ingredients["허브"] = 3;
    ingredients["맑은물"] = 2;
    ingredients["베리"] = 1;
}

void Craft_Work_Shop::Print_All_Recipes() const
{
    for (const All_Recipes& recipe : recipes)
    {
        recipe.PrintInfo();
    }
}

void Craft_Work_Shop::Find_Recipe_By_Potion_Name(const string& potionName) const
{
    bool found = false;

    for (const All_Recipes& recipe : recipes)
    {
        if (recipe.potionName == potionName)
        {
            recipe.PrintInfo();
            found = true;
        }
    }

    if (found == false)
    {
        cout << "해당 포션 레시피를 찾을 수 없습니다." << endl;
    }
}

void Craft_Work_Shop::Find_Recipes_By_Ingredient_Name(const string& ingredientName) const
{
    bool found = false;

    for (const All_Recipes& recipe : recipes)
    {
        if (recipe.ingredient1Name == ingredientName || recipe.ingredient2Name == ingredientName)
        {
            recipe.PrintInfo();
            found = true;
        }
    }

    if (found == false)
    {
        cout << "해당 재료가 들어간 포션 레시피를 찾을 수 없습니다." << endl;
    }
}
 
bool Craft_Work_Shop::Craft_Potion(const std::string& potionName)
{
    for (const All_Recipes& recipe : recipes)
    {
        if (recipe.potionName == potionName)
        {
            if (ingredients[recipe.ingredient1Name] < recipe.ingredient1Count ||
                ingredients[recipe.ingredient2Name] < recipe.ingredient2Count)
            {
                cout << "재료가 부족합니다." << endl;
                return false;
            }

            ingredients[recipe.ingredient1Name] -= recipe.ingredient1Count;
            ingredients[recipe.ingredient2Name] -= recipe.ingredient2Count;

            cout << potionName << " 제작 성공!" << endl;
            return true;
        }
    }

    cout << "해당 포션 레시피를 찾을 수 없습니다." << endl;
    return false;
}