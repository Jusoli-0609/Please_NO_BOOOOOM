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
		int _Money;
	public:
		//1.�κ��丮 ���� ��Ʈ
		Inventory(int max_inventory_size, int max_capacity);//1-1 �κ��丮 �⺻ ������
		Inventory(const Inventory<T>& other); //1-2.�κ��丮 ���� ������(���� ����鼭 ���� �� ���� ������)
		//2.�κ��丮 ���� ������ ��Ʈ
		Inventory<T>& operator=(const Inventory<T>& other);//2-1 ���� ������
		//3.�κ��丮 ��ȸ �Լ� ��Ʈ
		int Get_Total_Weight() const;//3-1 �� ���� ��ȸ �Լ�
		T* Get_Item_By_Index(int Index);//3-2 �κ��丮 Index ��������
		int Get_Size() const;//3-3 �κ��丮 ������ ��ȸ
		int Get_Capacity() const;//3-4 ���� ��ȸ
		//4.�κ��丮 ��� ���� �Լ� ��Ʈ
		void Print_Inventory() const;//4-1 �κ��丮 �� ���빰 ���
		void Print_Inventory_Menu();//4-2 �κ��丮 �޴�(������) ���
		//5.�κ��丮 ��� �Լ� ��Ʈ
		bool Add_Or_Increase_Item(const T& new_item);// 5-1 ������ �߰� �� ���� ����
		bool Use_Item_By_Name(const std::string& item_name);// 5-2 5-2 �̸����� ������ ��� ���� �� ���� ����
		void Use_Item_In_Battle(Player& player, Monster& monster);//5-3 ���� �� ������ ���
		void Throw_Away_Item();// 5-4 ������ ������
		void Remove_Last_Item();// 5-5 ������ ������ ����
		void Use_Random_Item_In_Battle(Player& player, Monster& monster);//5-6 ĳ���Ͱ� �ڵ����� ������ ���� ���
		// 6. �κ��丮 ���� / ���� ����
	    void Sort_Inventory();// 6-1 ������ ����
	    void Change_Inventory_Order();//6-2 ������ ���� ��� �ٲٱ�
	    // 7. �κ��丮 �뷮 Ȯ��
		void Increase_Max_Capacity(int new_max_capacity);//7-1 ������ �뷮 �þ��
	    // 8. �κ��丮 �Ҹ���	
		~Inventory();//8.�Ҹ���
		//9. �κ��丮 �� ���
		int Get_Money()const;
		void Set_Money(int money);
	};
