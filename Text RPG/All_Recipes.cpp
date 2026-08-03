#include "All_Recipes.h"
#include <iostream>


// 기본 생성자
All_Recipes::All_Recipes()
    : _Recipe_Name("None")
{
}


// 레시피 생성자
All_Recipes::All_Recipes(
    std::string recipe_name,
    std::map<std::string, int> ingredients)
    : _Recipe_Name(recipe_name),
    _Ingredients(ingredients)
{
}


// 레시피 이름 반환
std::string All_Recipes::Get_Recipe_Name() const
{
    return _Recipe_Name;
}


// 재료 목록 반환
std::map<std::string, int> All_Recipes::Get_Ingredients() const
{
    return _Ingredients;
}


// 레시피 정보 출력
void All_Recipes::Print_Info() const
{
    std::cout << "\n===== 제작법 =====\n";

    std::cout << "아이템 : "
        << _Recipe_Name
        << "\n";


    std::cout << "필요 재료\n";


    for (const auto& ingredient : _Ingredients)
    {
        std::cout
            << "- "
            << ingredient.first
            << " x "
            << ingredient.second
            << "\n";
    }
}