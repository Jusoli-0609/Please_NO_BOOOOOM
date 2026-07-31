#pragma once
#include "PotionRecipe.h"
#include <vector>
#include <string>
#include <map>

class AlchemyWorkshop
{
private:
    std::vector<PotionRecipe> recipes;
    std::map<std::string, int> ingredients;

public:
    AlchemyWorkshop();

    void PrintAllRecipes() const;
    void FindRecipeByPotionName(const std::string& potionName) const;
    void FindRecipesByIngredientName(const std::string& ingredientName) const;
    bool CraftPotion(const std::string& potionName);
};