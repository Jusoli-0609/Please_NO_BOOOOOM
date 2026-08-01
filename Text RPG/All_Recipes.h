#pragma once
#include <string>

class All_Recipes
{
public:
    std::string _Recipe_Name;
    std::string _First_Ingredient_Name;
    int _First_Ingredient_Count;
    std::string _Second_Ingredient_Name;
    int _Second_Ingredient_Count;

    void PrintInfo() const;
};