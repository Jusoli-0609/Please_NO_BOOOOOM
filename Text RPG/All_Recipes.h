#pragma once
#include <string>

class All_Recipes
{
public:
    std::string potionName;
    std::string ingredient1Name;
    int ingredient1Count;
    std::string ingredient2Name;
    int ingredient2Count;

    void PrintInfo() const;
};