	#pragma once
	#include<algorithm>
	#include <map>
	#include <string>
	#include <vector>

	#include "Item.h"
	#include "Player.h"

	template <typename T>
	class Inventory
	{
	private:
		T* _Inventory_Items;
		int _Max_Inventory_Size;
		int _Max_Capacity;
		int _Current_Quantity_Of_Items;
	public:
		//1.인벤토리 생성 파트
		Inventory(int max_inventory_size, int max_capacity);//1-1 인벤토리 기본 생성자
		Inventory(const Inventory<T>& other); //1-2.인벤토리 복사 생성자(새로 만들면서 복사 → 복사 생성자)
		//2.인벤토리 대입 연산자 파트
		Inventory<T>& operator=(const Inventory<T>& other);//2-1 대입 연산자
		//3.인벤토리 조회 함수 파트
		int Get_Total_Weight() const;//3-1 총 무게 조회 함수
		T* Get_Item_By_Index(int Index);//3-2 인벤토리 Index 가져오기
		int Get_Size() const;//3-3 인벤토리 사이즈 조회
		int Get_Capacity() const;//3-4 무게 조회
		//4.인벤토리 출력 관련 함수 파트
		void Print_Inventory() const;//4-1 인벤토리 및 내용물 출력
		void Print_Inventory_Menu();//4-2 인벤토리 메뉴(선택지) 출력
		//5.인벤토리 기능 함수 파트
		bool Add_Or_Increase_Item(const T& new_item);// 5-1 아이템 추가 및 갯수 증가
		bool Use_Item_By_Name(const std::string& item_name);// 5-2 5-2 이름으로 아이템 사용 성공 및 갯수 감소
		void Use_Item_In_Battle(Player& player, Monster& monster);//5-3 전투 중 아이템 사용
		void Throw_Away_Item();// 5-4 아이템 버리기
		void Remove_Last_Item();// 5-5 마지막 아이템 제거
		void Use_Random_Item_In_Battle(Player& player, Monster& monster);//5-6 캐릭터가 자동으로 아이템 랜덤 사용
		// 6. 인벤토리 정렬 / 순서 변경
	    void Sort_Inventory();// 6-1 아이템 정렬
	    void Change_Inventory_Order();//6-2 아이템 순서 골라서 바꾸기
	    // 7. 인벤토리 용량 확장
		void Increase_Max_Capacity(int new_max_capacity);//7-1 아이템 용량 늘어나기
	    // 8. 인벤토리 소멸자	
		~Inventory();//8.소멸자
	};
