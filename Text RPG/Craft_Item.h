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

    void Print_All_Recipes() const;
    void Find_Recipe_By_Potion_Name(const std::string& _Recipe_Name) const;
    void Find_Recipes_By_Ingredient_Name(const std::string& ingredientName) const;
    bool Craft_Potion(const std::string& _Recipe_Name);
};