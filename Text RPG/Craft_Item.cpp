#include "Craft_Item.h"
#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include "Items_Equipments_Repository.h"
#include "Monster.h"
using namespace std;

Craft_Work_Shop::Craft_Work_Shop()
    : recipe_repository()
{
}

void Craft_Work_Shop::Print_All_Recipes() const
{
    const vector<All_Recipes>& recipes = recipe_repository.Get_All_Recipes();

    cout << "\n===== 전체 레시피 목록 =====\n";

    for (size_t i = 0; i < recipes.size(); i++)
    {
        cout << "\n[" << i + 1 << "번]";
        recipes[i].Print_Info();
    }

    cout << "=================================\n";
}


    bool Craft_Work_Shop::Craft_Item(Inventory<Item>&inventory, Inventory_For_Equipments_Only& equipment_inventory)
    {
        cout << "========== 제작소 ==========" << endl;

        Print_All_Recipes();

        int selected_index = 0;

        cout << "제작할 레시피 번호를 입력하라냥! : ";
        cin >> selected_index;
        const vector<All_Recipes>& recipes = recipe_repository.Get_All_Recipes();
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "잘못된 입력이다냥!" << endl;
            return false;
        }
        if (selected_index < 1 || selected_index > recipes.size())
        {
            cout << "존재하지 않는 레시피 번호다냥!" << endl;
            return false;
        }

  
        const All_Recipes& selected_recipe = recipes[selected_index - 1];
       

        map<string, int> ingredients = selected_recipe.Get_Ingredients();

        string result_item_name = selected_recipe.Get_Recipe_Name();


        // ==============================
        // 1. 재료 보유 수량 확인
        // ==============================

        for (const pair<string, int>& ingredient : ingredients)
        {
            string ingredient_name = ingredient.first;
            int required_count = ingredient.second;

            // TODO: inventory.Get_Item_Count_By_Name 호출 결과 변수 선언
            int current_count = inventory.Get_Item_Count_By_Name(ingredient_name);

            // TODO: 보유 수량 부족 조건문
            if (current_count < required_count)
            {
                cout << "재료가 부족하다냥! "
                    << ingredient_name
                    << " 필요: " << required_count
                    << ", 보유: " << current_count
                    << endl;

                return false;
            }
        }


        // ==============================
        // 2. 재료 차감
        // ==============================

        for (const pair<string, int>& ingredient : ingredients)
        {
            string ingredient_name = ingredient.first;
            int required_count = ingredient.second;

            // TODO: inventory.Remove_Item_Count 호출 결과 변수 선언
            // 함수 형태에 맞게 아래 오른쪽 부분을 채워주세요.
            bool remove_result =  inventory.Remove_Item_Count(ingredient.first,ingredient.second);

            if (remove_result == false)
            {
                cout << "재료 차감에 실패했다냥! "
                    << ingredient_name
                    << endl;

                return false;
            }
        }


        // ==============================
        // 3. 제작 결과 아이템 생성
        // ==============================

        Item crafted_item;

        // TODO: crafted_item 이름 필드 대입
        // crafted_item._Item_Name = result_item_name;

        // TODO: crafted_item 개수 필드 대입
        // crafted_item._Item_Count = 1;

        // TODO: crafted_item 무게 필드 대입
        // crafted_item._Item_Weight = 1;

        // TODO: crafted_item 가격 필드 대입
        // crafted_item._Item_Price = 0;

        // TODO: crafted_item 설명 필드 대입
        // crafted_item._Item_Description = "제작으로 획득한 아이템";

        // TODO: crafted_item 사용 가능 여부 필드 대입
        // crafted_item._Item_Type_Usable = false;

        // TODO: crafted_item 장착 가능 여부 필드 대입
        // crafted_item._Item_Type_Wearable = false;


        // ==============================
        // 4. 인벤토리에 결과 아이템 추가
        // ==============================

        // TODO: inventory.Add_Or_Increase_Item 호출 결과 변수 선언

        // TODO: 인벤토리 추가 실패 조건문

        // TODO: 제작 완료 메시지 출력문

        return true;
    }


    // ==============================
    // 장비 분해
    // ==============================
    bool Craft_Work_Shop::Decomposition_Item(
        Inventory_For_Equipments_Only & equipment_inventory,
        Inventory<Item>&item_inventory
    )
    {
        cout << "========== 장비 분해 ==========" << endl;

        // TODO: 장비 인벤토리 출력 함수 호출
        // equipment_inventory.Print_Equipment_Inventory();

        int selected_index = 0;

        cout << "분해할 장비 번호를 선택하세요: ";
        cin >> selected_index;

        // TODO: 입력 실패 처리 코드
        // TODO: selected_index 범위 검사 조건문

        // TODO: 선택한 장비 포인터 또는 참조 변수 선언
        // 예:
        // Equipment* selected_equipment = equipment_inventory.Get_Equipment_By_Index(selected_index - 1);

        // TODO: selected_equipment가 nullptr인지 검사하는 조건문


        // ==============================
        // 1. 분해 결과 재료 아이템 생성
        // ==============================

        Item material_item;

        // TODO: material_item 이름 필드 대입
        // 예: material_item._Item_Name = "분해 조각";

        // TODO: material_item 개수 필드 대입

        // TODO: material_item 무게 필드 대입

        // TODO: material_item 가격 필드 대입

        // TODO: material_item 설명 필드 대입

        // TODO: material_item 사용 가능 여부 필드 대입

        // TODO: material_item 장착 가능 여부 필드 대입


        // ==============================
        // 2. 재료 아이템 인벤토리에 추가
        // ==============================

        // TODO: item_inventory.Add_Or_Increase_Item 호출 결과 변수 선언

        // TODO: 재료 추가 실패 조건문


        // ==============================
        // 3. 기존 장비 제거
        // ==============================

        // TODO: equipment_inventory에서 선택 장비 제거 함수 호출
        // 예:
        // equipment_inventory.Remove_Equipment_By_Index(selected_index - 1);

        // TODO: 장비 제거 실패 조건문

        // TODO: 분해 완료 메시지 출력문

        return true;
    }


    // ==============================
    // 장비 강화
    // ==============================
    bool Craft_Work_Shop::Enhance_Item(Equipment & equipment)
    {
        cout << "========== 장비 강화 ==========" << endl;

        // TODO: 강화 대상 장비 정보 출력 함수 호출
        // equipment.Print_Info();


        // ==============================
        // 1. 강화 가능 여부 확인
        // ==============================

        // TODO: 장비의 현재 강화 수치 변수 선언

        // TODO: 최대 강화 수치 변수 선언

        // TODO: 현재 강화 수치가 최대치 이상인지 검사하는 조건문


        // ==============================
        // 2. 강화 성공 확률 계산 준비
        // ==============================

        // TODO: 강화 성공 확률 변수 선언

        // TODO: 랜덤 값 변수 선언

        // TODO: 성공 여부 bool 변수 선언


        // ==============================
        // 3. 강화 결과 처리
        // ==============================

        // TODO: 강화 성공 조건문

        {
            // TODO: 장비 강화 수치 증가 코드

            // TODO: 장비 능력치 증가 코드

            // TODO: 강화 성공 메시지 출력문
        }

        // TODO: 강화 실패 조건문

        {
            // TODO: 강화 실패 시 메시지 출력문

            // TODO: 실패 패널티가 있다면 관련 필드 변경 코드
        }

        return true;
    }