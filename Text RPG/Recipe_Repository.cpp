#include "Recipe_Repository.h"


Recipe_Repository::Recipe_Repository()
{

    // 예시 레시피
    recipes.push_back(
        All_Recipes(
            "강화석",
            {
                {"철 조각", 3},
                {"마력 가루", 2}
            }
        )
    );


    // 나중에 여기에 계속 추가
    /*

    recipes.push_back(
        All_Recipes(
            "아이템 이름",
            {
                {"재료1", 개수},
                {"재료2", 개수}
            }
        )
    );

    */

}


// 전체 레시피 반환
const std::vector<All_Recipes>& Recipe_Repository::Get_All_Recipes() const
{
    return recipes;
}