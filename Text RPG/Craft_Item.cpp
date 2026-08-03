#include "Craft_Item.h"
#include "All_Recipes.h"
#include <iostream>

using namespace std;

Craft_Work_Shop::Craft_Work_Shop()
{
    All_Recipes hpPotion;

    hpPotion._Recipe_Name = "�Ŷ��";
    hpPotion._First_Ingredient_Name = "���";
    hpPotion._First_Ingredient_Count = 1;
    hpPotion._Second_Ingredient_Name = "������";
    hpPotion._Second_Ingredient_Count = 1;

    recipes.push_back(hpPotion);

    All_Recipes staminaPotion;

    staminaPotion._Recipe_Name = "���¹̳�����";
    staminaPotion._First_Ingredient_Name = "���";
    staminaPotion._First_Ingredient_Count = 1;
    staminaPotion._Second_Ingredient_Name = "����";
    staminaPotion._Second_Ingredient_Count = 1;

    recipes.push_back(staminaPotion);

    ingredients["���"] = 3;
    ingredients["������"] = 2;
    ingredients["����"] = 1;
}

void Craft_Work_Shop::Print_All_Recipes() const
{
    for (const All_Recipes& recipe : recipes)
    {
        recipe.PrintInfo();
    }
}

void Craft_Work_Shop::Find_Recipe_By_Potion_Name(const string& _Recipe_Name) const
{
    bool found = false;

    for (const All_Recipes& recipe : recipes)
    {
        if (recipe._Recipe_Name == _Recipe_Name)
        {
            recipe.PrintInfo();
            found = true;
        }
    }

    if (found == false)
    {
        cout << "�ش� ���� �����Ǹ� ã�� �� �����ϴ�." << endl;
    }
}

void Craft_Work_Shop::Find_Recipes_By_Ingredient_Name(const string& ingredientName) const
{
    bool found = false;

    for (const All_Recipes& recipe : recipes)
    {
        if (recipe._First_Ingredient_Name == ingredientName || recipe._Second_Ingredient_Name == ingredientName)
        {
            recipe.PrintInfo();
            found = true;
        }
    }

    if (found == false)
    {
        cout << "�ش� ��ᰡ �� ���� �����Ǹ� ã�� �� �����ϴ�." << endl;
    }
}
 
bool Craft_Work_Shop::Craft_Potion(const std::string& _Recipe_Name)
{
    for (const All_Recipes& recipe : recipes)
    {
        if (recipe._Recipe_Name == _Recipe_Name)
        {
            if (ingredients[recipe._First_Ingredient_Name] < recipe._First_Ingredient_Count ||
                ingredients[recipe._Second_Ingredient_Name] < recipe._Second_Ingredient_Count)
            {
                cout << "��ᰡ �����մϴ�." << endl;
                return false;
            }

            ingredients[recipe._First_Ingredient_Name] -= recipe._First_Ingredient_Count;
            ingredients[recipe._Second_Ingredient_Name] -= recipe._Second_Ingredient_Count;

            cout << _Recipe_Name << " ���� ����!" << endl;
            return true;
        }
    }

    cout << "�ش� ���� �����Ǹ� ã�� �� �����ϴ�." << endl;
    return false;
}