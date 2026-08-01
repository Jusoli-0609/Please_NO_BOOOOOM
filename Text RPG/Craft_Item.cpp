#include "Craft_Item.h"
#include "All_Recipes.h"
#include <iostream>

using namespace std;

Craft_Work_Shop::Craft_Work_Shop()
{
    All_Recipes hpPotion;

    hpPotion._Recipe_Name = "컵라면";
    hpPotion._First_Ingredient_Name = "허브";
    hpPotion._First_Ingredient_Count = 1;
    hpPotion._Second_Ingredient_Name = "맑은물";
    hpPotion._Second_Ingredient_Count = 1;

    recipes.push_back(hpPotion);

    All_Recipes staminaPotion;

    staminaPotion._Recipe_Name = "스태미나포션";
    staminaPotion._First_Ingredient_Name = "허브";
    staminaPotion._First_Ingredient_Count = 1;
    staminaPotion._Second_Ingredient_Name = "베리";
    staminaPotion._Second_Ingredient_Count = 1;

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

void Craft_Work_Shop::Find_Recipe_By_Potion_Name(const string& _Recipe_Name) const
{
    bool found = false;

    for (const All_Recipes& recipe : recipes)
    {
        if (recipe._Recipe_Name == _Recipe_Name)
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
        if (recipe._First_Ingredient_Name == ingredientName || recipe._Second_Ingredient_Name == ingredientName)
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
 
bool Craft_Work_Shop::Craft_Potion(const std::string& _Recipe_Name)
{
    for (const All_Recipes& recipe : recipes)
    {
        if (recipe._Recipe_Name == _Recipe_Name)
        {
            if (ingredients[recipe._First_Ingredient_Name] < recipe._First_Ingredient_Count ||
                ingredients[recipe._Second_Ingredient_Name] < recipe._Second_Ingredient_Count)
            {
                cout << "재료가 부족합니다." << endl;
                return false;
            }

            ingredients[recipe._First_Ingredient_Name] -= recipe._First_Ingredient_Count;
            ingredients[recipe._Second_Ingredient_Name] -= recipe._Second_Ingredient_Count;

            cout << _Recipe_Name << " 제작 성공!" << endl;
            return true;
        }
    }

    cout << "해당 포션 레시피를 찾을 수 없습니다." << endl;
    return false;
}