#pragma once

#include "All_Recipes.h"
#include <vector>


class Recipe_Repository
{

private:

    std::vector<All_Recipes> recipes;


public:

    Recipe_Repository();


    // 전체 레시피 반환 (복사 방지)
    const std::vector<All_Recipes>& Get_All_Recipes() const;


};