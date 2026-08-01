#pragma once
#include "All_Recipes.h"
#include <vector>
#include <string>
#include <map>

class Craft_Work_Shop
{
private:
    std::vector<All_Recipes> recipes;
    std::map<std::string, int> ingredients;

public:
    Craft_Work_Shop();

    void PrintAllRecipes() const;
    void FindRecipeByPotionName(const std::string& potionName) const;
    void FindRecipesByIngredientName(const std::string& ingredientName) const;
    bool CraftPotion(const std::string& potionName);
};