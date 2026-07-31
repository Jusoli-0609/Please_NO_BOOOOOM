#include "AlchemyWorkshop.h"
#include <iostream>

using namespace std;

AlchemyWorkshop::AlchemyWorkshop()
{
    PotionRecipe hpPotion;

    hpPotion.potionName = "HP포션";
    hpPotion.ingredient1Name = "허브";
    hpPotion.ingredient1Count = 1;
    hpPotion.ingredient2Name = "맑은물";
    hpPotion.ingredient2Count = 1;

    recipes.push_back(hpPotion);

    PotionRecipe staminaPotion;

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

void AlchemyWorkshop::PrintAllRecipes() const
{
    for (const PotionRecipe& recipe : recipes)
    {
        recipe.PrintInfo();
    }
}

void AlchemyWorkshop::FindRecipeByPotionName(const string& potionName) const
{
    bool found = false;

    for (const PotionRecipe& recipe : recipes)
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

void AlchemyWorkshop::FindRecipesByIngredientName(const string& ingredientName) const
{
    bool found = false;

    for (const PotionRecipe& recipe : recipes)
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
 
bool AlchemyWorkshop::CraftPotion(const std::string& potionName)
{
    for (const PotionRecipe& recipe : recipes)
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