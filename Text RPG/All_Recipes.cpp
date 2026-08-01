#include "All_Recipes.h"
#include <iostream>

using namespace std;

void All_Recipes::PrintInfo() const
{
    cout << _Recipe_Name << ": "
        << _First_Ingredient_Name << " x" << _First_Ingredient_Count << ", "
        << _Second_Ingredient_Name << " x" << _Second_Ingredient_Count
        << endl;
}