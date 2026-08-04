#include "Craft_Item.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

Craft_Work_Shop::Craft_Work_Shop()
{
}

//=============================================================================
// 1. 선택한 단계의 장비 제작법 출력
//=============================================================================

void Craft_Work_Shop::Print_Recipes_By_Level
(
	int equipment_Level
) const
{
	const vector<All_Recipes>& recipes = recipe_repository.Get_All_Recipes();

	if
		(equipment_Level < 1 || equipment_Level > 5)
	{
		cout << "잘못된 장비 단계다." << endl;
		return;
	}

	const int EQUIPMENT_COUNT_PER_LEVEL = 5;

	int start_Index = (equipment_Level - 1) * EQUIPMENT_COUNT_PER_LEVEL;

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ " << equipment_Level << "단계 장비 제작 목록 ]" << endl;
	cout << "========================================" << endl;

	for
		(
			int i = 0;
			i < EQUIPMENT_COUNT_PER_LEVEL;
			i++
			)
	{
		int recipe_Index = start_Index + i;

		if
			(recipe_Index >= static_cast<int>(recipes.size()))
		{
			break;
		}

		const All_Recipes& recipe = recipes[recipe_Index];

		cout << i + 1 << ". " << recipe.Get_Recipe_Name() << endl;

		map<string, int> ingredients = recipe.Get_Ingredients();

		for
			(const auto& ingredient: ingredients)
		{
			cout << "   - " << ingredient.first << " " << ingredient.second << "개" << endl;
		}

		cout << endl;
	}

	cout << "0. 이전으로" << endl;
	cout << "========================================" << endl;
}

//=============================================================================
// 2. 인벤토리 안의 특정 아이템 개수 조회
//=============================================================================

int Craft_Work_Shop::Get_Item_Count
(Inventory<Item>& inventory, const string& item_Name
) const
{
	for
		(
			int i = 0;
			i < inventory.Get_Size();
			i++
			)
	{
		Item* item =inventory.Get_Item_By_Index(i);

		if (item == nullptr)
		{
			continue;
		}

		if (item->_Item_Name == item_Name)
		{
			return item->_Item_Count;
		}
	}

	return 0;
}

//=============================================================================
// 3. 장비 제작
//=============================================================================

bool Craft_Work_Shop::Craft_Item
(
	Inventory<Item>& item_inventory,
	Inventory_For_Equipments_Only&
	equipment_inventory
)
{
	const vector<All_Recipes>& recipes =
		recipe_repository.Get_All_Recipes();

	if (recipes.empty())
	{
		cout
			<< "등록된 장비 제작법이 없다."
			<< endl;

		return false;
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 쿠키의 장비 제작 목록 ]" << endl;
	cout << "========================================" << endl;
	cout << "1. 1단계 장비" << endl;
	cout << "2. 2단계 장비" << endl;
	cout << "3. 3단계 장비" << endl;
	cout << "4. 4단계 장비" << endl;
	cout << "5. 5단계 장비" << endl;
	cout << "0. 뒤로가기" << endl;
	cout << "========================================" << endl;
	cout << "선택: ";

	int equipment_Level = -1;

	cin >> equipment_Level;

	switch (equipment_Level)
	{
	case 1:
	{
		break;
	}

	case 2:
	{
		break;
	}

	case 3:
	{
		break;
	}

	case 4:
	{
		break;
	}

	case 5:
	{
		break;
	}

	case 0:
	{
		cout << "장비 제작 메뉴에서 나간다." << endl;
		return false;
	}

	default:
	{
		cout << "잘못된 장비 단계를 선택했다." << endl;
		return false;
	}
	}

	Print_Recipes_By_Level
	(
		equipment_Level
	);

	cout << "제작할 장비 번호: ";

	int equipment_Choice = -1;

	cin >> equipment_Choice;

	if (equipment_Choice == 0)
	{
		cout << "대장간 메뉴로 돌아간다." << endl;
		return false;
	}

	if
		(equipment_Choice < 1 || equipment_Choice > 5)
	{
		cout << "잘못된 장비 번호다." << endl;
		return false;
	}

	const int EQUIPMENT_COUNT_PER_LEVEL = 5;

	int selected_Recipe_Index = (equipment_Level - 1) * EQUIPMENT_COUNT_PER_LEVEL + (equipment_Choice - 1);

	if
		(selected_Recipe_Index < 0 || selected_Recipe_Index>= static_cast<int>(recipes.size()))
	{
		cout << "선택한 장비 제작법을 찾지 못했다." << endl;
		return false;
	}

	const All_Recipes& selected_Recipe = recipes[selected_Recipe_Index];
	const string equipment_Name = selected_Recipe.Get_Recipe_Name();
	const Equipment* result_Equipment = equipment_repository.Find_Equipment_By_Name(equipment_Name);

	if (result_Equipment == nullptr)
	{
		cout << equipment_Name << " 장비 데이터를 찾지 못했다." << endl;
		return false;
	}

	map<string, int> ingredients = selected_Recipe.Get_Ingredients();

	bool has_All_Ingredients = true;

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 재료 확인 ]" << endl;
	cout << "========================================" << endl;

	for
		(const auto& ingredient : ingredients)
	{
		int owned_Count = Get_Item_Count(item_inventory,ingredient.first);

		cout << ingredient.first << ": " << owned_Count << " / " << ingredient.second << endl;

		if (owned_Count < ingredient.second)
		{
			has_All_Ingredients = false;
		}
	}

	cout << "========================================" << endl;

	if (!has_All_Ingredients)
	{
		cout << "코드 조각이 부족해 장비를 제작할 수 없다." << endl;

		return false;
	}

	cout << endl;
	cout << equipment_Name << "을(를) 제작하시겠습니까?" << endl;
	cout << "1. 제작" << endl;
	cout << "0. 취소" << endl;
	cout << "선택: ";

	int craft_Choice = -1;

	cin >> craft_Choice;

	if (craft_Choice != 1)
	{
		cout << "장비 제작을 취소했다." << endl;

		return false;
	}

	bool is_Added = equipment_inventory.Add_Equipment(*result_Equipment);

	if (!is_Added)
	{
		cout << "장비 인벤토리에 공간이 없어 " << "제작을 취소했다." << endl;

		return false;
	}

	for
		(const auto& ingredient : ingredients)
	{
		item_inventory.Remove_Item_Count(ingredient.first, ingredient.second);
	}

	cout << endl;
	cout << "========================================" << endl;
	cout << "[ 장비 제작 완료 ]" << endl;
	cout << "========================================" << endl;
	cout << "흩어진 코드 조각이 " << "하나의 장비로 결합됐다." << endl;
	cout << equipment_Name << " 제작 성공!" << endl;

	result_Equipment->Print_Equipment_Info();

	cout << "========================================" << endl;

	return true;
}

//=============================================================================
// 4. 장비 분해
//=============================================================================

bool Craft_Work_Shop::Decomposition_Item(Inventory_For_Equipments_Only& equipment_inventory, Inventory<Item>& item_inventory)
{
	(void)equipment_inventory;
	(void)item_inventory;

	cout << "장비 분해 기능은 아직 준비 중이다." << endl;
	return false;
}

//=============================================================================
// 5. 장비 강화
//=============================================================================

bool Craft_Work_Shop::Enhance_Item
(
	Equipment& equipment
)
{
	(void)equipment;

	cout << "장비 강화 기능은 아직 준비 중이다." << endl;
	return false;
}