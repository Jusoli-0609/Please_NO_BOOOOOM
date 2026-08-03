#include "Craft_Item.h"
#include <iostream>

using namespace std;



Craft_Work_Shop::Craft_Work_Shop()
{

}



// 모든 레시피 출력
void Craft_Work_Shop::Print_All_Recipes() const
{

    vector<All_Recipes> recipes =
        recipe_repository.Get_All_Recipes();


    cout << "\n===== 제작 가능한 레시피 =====\n";


    for (int i = 0; i < recipes.size(); i++)
    {
        cout << "\n[" << i + 1 << "번]\n";

        recipes[i].Print_Info();
    }

}



// 아이템 제작
bool Craft_Work_Shop::Craft_Item(
    Inventory<Item>& inventory
)
{

    vector<All_Recipes> recipes =
        recipe_repository.Get_All_Recipes();


    if (recipes.empty())
    {
        cout << "등록된 레시피가 없다!" << endl;
        return false;
    }



    Print_All_Recipes();


    int choice;

    cout << "제작할 아이템 번호 : ";
    cin >> choice;



    if (choice < 1 || choice > recipes.size())
    {
        cout << "잘못된 선택이다!" << endl;
        return false;
    }



    All_Recipes selected_recipe =
        recipes[choice - 1];



    // 재료 보유 확인

    for (auto ingredient :
        selected_recipe.Get_Ingredients())
    {

        bool found = false;


        for (int i = 0; i < inventory.Get_Size(); i++)
        {

            Item* item =
                inventory.Get_Item_By_Index(i);


            if (item->_Item_Name ==
                ingredient.first)
            {

                if (item->_Item_Count >= ingredient.second)
                {
                    found = true;
                }

            }

        }



        if (found == false)
        {
            cout
                << ingredient.first
                << "이(가) 부족하다!"
                << endl;

            return false;
        }

    }



    // 재료 제거

    for (auto ingredient :
        selected_recipe.Get_Ingredients())
    {

        inventory.Remove_Item_Count(
            ingredient.first,
            ingredient.second
        );

    }



    // 결과 아이템 생성

    Item result;


    result._Item_Name =
        selected_recipe.Get_Recipe_Name();


    result._Item_Count = 1;


    result._Item_Description =
        "제작된 아이템";



    inventory.Add_Or_Increase_Item(result);



    cout
        << result._Item_Name
        << " 제작 성공!"
        << endl;



    return true;

}