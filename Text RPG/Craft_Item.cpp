#include "Craft_Item.h"

#include <iostream>

using namespace std;

Craft_Work_Shop::Craft_Work_Shop()
{
    // TODO: recipe_repository 초기화 코드
    // 예: 기본 레시피 등록이 필요하다면 이 위치에 작성
}

void Craft_Work_Shop::Print_All_Recipes() const
{
    // TODO: Recipe_Repository의 전체 레시피 출력 함수 호출 코드

    // 예시 형태:
    // recipe_repository.Print_All_Recipes();
}

bool Craft_Work_Shop::Craft_Item(
    Inventory<Item>& inventory
)
{
    // TODO: 제작할 레시피 선택을 위한 입력 변수 선언

    // TODO: 선택한 레시피 조회 코드

    // TODO: 인벤토리에 재료가 충분한지 확인하는 조건문

    // TODO: 재료 차감 코드

    // TODO: 제작 결과 아이템 추가 코드

    // TODO: 제작 성공 여부 반환값
    return false;
}

bool Craft_Work_Shop::Decomposition_Item(
    Inventory_For_Equipments_Only& equipment_inventory,
    Inventory<Item>& item_inventory
)
{
    // TODO: 분해할 장비 선택을 위한 입력 변수 선언

    // TODO: 장비 인벤토리에서 대상 장비 조회 코드

    // TODO: 분해 가능 여부 확인 조건문

    // TODO: 장비 제거 코드

    // TODO: 분해 결과 아이템 추가 코드

    // TODO: 분해 성공 여부 반환값
    return false;
}

bool Craft_Work_Shop::Enhance_Item(
    Equipment& equipment
)
{
    // TODO: 강화에 필요한 데이터 변수 선언
    // 예: 강화 확률, 비용, 현재 강화 수치 등

    // TODO: 강화 가능 여부 확인 조건문

    // TODO: 강화 성공/실패 판정에 필요한 코드 위치

    // TODO: 성공 시 장비 능력치 변경 코드

    // TODO: 강화 성공 여부 반환값
    return false;
}