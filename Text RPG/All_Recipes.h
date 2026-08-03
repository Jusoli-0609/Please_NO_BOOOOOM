#pragma once
#include <string>
#include <map>

class All_Recipes
{
private:

    std::string _Recipe_Name;

    // 재료 이름 : 필요 개수
    std::map<std::string, int> _Ingredients;


public:

    All_Recipes();

    All_Recipes(
        std::string recipe_name,
        std::map<std::string, int> ingredients
    );


    std::string Get_Recipe_Name() const;

    std::map<std::string, int> Get_Ingredients() const;


    void Print_Info() const;

};