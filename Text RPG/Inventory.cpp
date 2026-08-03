#include<algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

#include "Inventory.h"
#include "Player.h"

using namespace std;

template<typename T>//1-1 �⺻ ������
Inventory<T>::Inventory(int max_inventory_size, int max_capacity)
{
    _Max_Inventory_Size = max_inventory_size;
    _Max_Capacity = max_capacity;
    _Current_Quantity_Of_Items = 0;
    _Money = 0;
    {
        _Inventory_Items = new T[_Max_Inventory_Size];
    }
}

template<typename T>//1- 2���� ������
Inventory<T>::Inventory(const Inventory<T>& other)// ���� ��ü�� ���� ���¸� ���� �� ��ü�� �ʿ��� �� ����)
{
    _Max_Inventory_Size = other._Max_Inventory_Size;
    if (other._Current_Quantity_Of_Items > other._Max_Inventory_Size)
    {
        _Current_Quantity_Of_Items = other._Max_Inventory_Size;
    }
    else
    {
        _Current_Quantity_Of_Items =
            min(other._Current_Quantity_Of_Items, other._Max_Inventory_Size);
    }
    _Max_Capacity = other._Max_Capacity;
    _Money = other._Money;
    _Inventory_Items = new T[_Max_Inventory_Size];
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        _Inventory_Items[i] = other._Inventory_Items[i];
    }
}

template<typename T>//2-1 ���� ������ 
Inventory<T>& Inventory<T>::operator=(const Inventory<T>& other)//(�ٸ� Inventory<T> ��ü�� �޾Ƽ�, ���� ��ü�� �����ϰ�, ���� ��ü �ڽ��� ��ȯ)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _Inventory_Items;
    _Max_Inventory_Size = other._Max_Inventory_Size;
    _Max_Capacity = other._Max_Capacity;
    _Money = other._Money;
    _Current_Quantity_Of_Items = min(other._Current_Quantity_Of_Items, other._Max_Inventory_Size);
    _Inventory_Items = new T[_Max_Inventory_Size];
    int Safe_Item_Count = min(_Current_Quantity_Of_Items, _Max_Inventory_Size);
    for (int i = 0; i < Safe_Item_Count; i++)
    {
        _Inventory_Items[i] = other._Inventory_Items[i];
    }
    return *this;
}

template<typename T>//3-1 �κ��丮 �� ���� �Լ�
int Inventory<T>::Get_Total_Weight()const
{
    int Total_Weight = 0;
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        Total_Weight += _Inventory_Items[i]._Item_Weight * _Inventory_Items[i]._Item_Count;
    }
    return Total_Weight;
}

template<typename T>// 3-2 �κ��丮 Index  ��������
T* Inventory<T>::Get_Item_By_Index(int index)
{
    if (index < 0 || index >= _Current_Quantity_Of_Items)
    {
        return nullptr;
    }
    return &_Inventory_Items[index];
}

template<typename T>//3-3 �κ��丮 ������ ��������
int Inventory<T>::Get_Size()const
{
    return _Current_Quantity_Of_Items;
}

template<typename T>// 3-4 �κ��丮 ���� ��������
int Inventory<T>::Get_Capacity() const
{
    return _Max_Capacity;
}

template <typename T>//4-1 �κ��丮 �� ���빰 ���
void Inventory<T>::Print_Inventory() const
{
    cout << "===== �κ��丮 =====" << endl;
    int  Inventory_Order_Index = 1;
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {

        cout << Inventory_Order_Index << ".";
        _Inventory_Items[i].Print_Info();
        Inventory_Order_Index++;
    }
    cout << "���� �� ��: " << Get_Money() << endl;
    cout << " ���� ����  : " <<
        Get_Total_Weight() << "�ִ� ��� ����  : " <<
        _Max_Capacity << " ���� ��� ����  : " <<
        _Max_Capacity - Get_Total_Weight() << endl;
}

template <typename T>//4-2 �κ��丮 �޴� ���
void Inventory<T>::Print_Inventory_Menu()
{
    cout << R"(
    ������ �ұ�?
    1. ��ü �κ��丮 ����
    2. ������ ����
    3. ������ ���� �ٲٱ�
    4. ������ ������
    0. �ǵ��ư���)" << endl;
    int Choose_Inventory_Menu;
    cin >> Choose_Inventory_Menu;
    switch (Choose_Inventory_Menu)
    {
    case 1:
    {
        Print_Inventory();
        break;
    }
    case 2:
    {
        Sort_Inventory();
        break;
    }

    case 3:
    {
        Change_Inventory_Order();
        break;
    }
    case 4:
    {
        Throw_Away_Item();
        break;
    }
    case 0:
    {
        return;
    }
    default:
    {
        break;
    }
    }
}

template<typename T>//5-1 ������ �߰� �� ���� ����
bool Inventory<T>::Add_Or_Increase_Item(const T& new_item)
{
    new_item.Print_Info();
    int New_Item_Weight = new_item._Item_Weight * new_item._Item_Count;
    T* Found_Item = nullptr;  //  ���� �������� ����ų ������ ���� ����
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)//��ȸ �ݺ���
    {
        if (_Inventory_Items[i]._Item_Name == new_item._Item_Name)
        {
            Found_Item = &_Inventory_Items[i];//foundItem�� ���� item�� �ּ� ����
            break;
        }
    }
    //1.���� �˻�
    while (Get_Total_Weight() + New_Item_Weight > _Max_Capacity)
    {
        cout << "�κ��丮�� ���԰� �� �뷮�� �ʰ��ߴ�! ������ ���� ���ΰ�?" << endl;
        cout << "1. ������" << endl;
        cout << "2. ���" << endl;
        int Choose_Item_To_Get_Rid_Of;
        cin >> Choose_Item_To_Get_Rid_Of;
        if (Choose_Item_To_Get_Rid_Of == 1)
        {
            Throw_Away_Item();
            Found_Item = nullptr;
            for (int i = 0; i < _Current_Quantity_Of_Items; i++)
            {
                if (_Inventory_Items[i]._Item_Name == new_item._Item_Name)
                {
                    Found_Item = &_Inventory_Items[i]; //��۸� ������ ����
                    break;
                }
            }
        }
        else if (Choose_Item_To_Get_Rid_Of == 2)
        {
            return false;
        }
        else
        {
            cout << "�߸��� �Է��̴�!" << endl;
        }
    }
    if (Found_Item != nullptr)
    {
        Found_Item->_Item_Count += new_item._Item_Count;
        cout << new_item._Item_Name << "�� ������ " << new_item._Item_Count << "��ŭ �����ߴ�!" << endl;
        return true;
    }
    while (_Current_Quantity_Of_Items >= _Max_Inventory_Size)
    {
        cout << "�κ��丮 ������ ���� á��!" << endl;
        cout << "������ ������ ������ �� ������ ������ 0���� ������ �Ѵ�." << endl;
        cout << "�Ϻθ� ������ ������ �״�� ���� �ִ�. ������ ���� ���ΰ�?" << endl;
        cout << "1. ������" << endl;
        cout << "2. ���" << endl;
        int Choose_Item_To_Get_Rid_Of;
        cin >> Choose_Item_To_Get_Rid_Of;
        if (Choose_Item_To_Get_Rid_Of == 1)
        {
            Throw_Away_Item();
            if (_Current_Quantity_Of_Items >= _Max_Inventory_Size)
            {
                cout << "���� ������ �����ϴ�!" << endl;
            }
        }
        else if (Choose_Item_To_Get_Rid_Of == 2)
        {
            return false;
        }
        else
        {
            cout << "�߸��� �Է��̴�!" << endl;
        }
    }
    _Inventory_Items[_Current_Quantity_Of_Items] = new_item;
    _Current_Quantity_Of_Items++;
    cout << "���ο� ������ : " << new_item._Item_Name << "�� �߰��ƴ�!" << endl;
    return true;
}

template<typename T>//5-2 �̸����� ������ ��� ���� �� ���� ����
bool Inventory<T>::Use_Item_By_Name(const string& item_name)
{
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        if (_Inventory_Items[i]._Item_Name == item_name)
        {
            if (_Inventory_Items[i]._Item_Count > 0)
            {
                _Inventory_Items[i]._Item_Count -= 1;
                if (_Inventory_Items[i]._Item_Count == 0)
                {
                    for (int j = i; j < _Current_Quantity_Of_Items - 1; j++)
                    {
                        _Inventory_Items[j] = _Inventory_Items[j + 1];
                    }
                    _Current_Quantity_Of_Items--;
                }
                return true;
            }
            return false;
        }
    }
    return false;
}

template <typename T>//5-3 ���� �� ������ ���
void Inventory<T>::Use_Item_In_Battle(Player& player, Monster& monster)
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "����� �������� ����!" << endl;
        return;
    }
    Print_Inventory();
    int Choose_Item_To_Use_In_Battle;
    cout << "���� �� ����� �������� �������!" << endl;
    cin >> Choose_Item_To_Use_In_Battle;
    int Vector_Index = Choose_Item_To_Use_In_Battle - 1;
    T* selected_item = Get_Item_By_Index(Vector_Index); //  GetItemByIndex ȣ�� ����� ������ Item ������ ���� ����
    if (selected_item == nullptr)
    {
        cout << "�߸��� ������ ��ȣ��!" << endl;
        return;
    }
    string selected_item_name = selected_item->_Item_Name; // ������ ������ �̸��� ������ string ���� ����
    if (selected_item->_Item_Type_Usable == true)
    {
        selected_item->Item_Effect(player, monster);
        Use_Item_By_Name(selected_item_name);
        return;
    }
    else
    {
        cout << "����� �� ���� �������̴�!" << endl;
        return;
    }
}

template <typename T>//5-4 ���� ������
void Inventory<T>::Throw_Away_Item()
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "���� �������� ����!" << endl;
        return;
    }
    Print_Inventory();
    int Selected_Index;
    cout << "�� �� �������� ���� ���ΰ�?" << endl;
    cin >> Selected_Index;
    while (Selected_Index<1 || Selected_Index>_Current_Quantity_Of_Items)
    {
        cout << "�߸��� �Է��̴�. �ٽ� �Է��ϼ���." << endl;
        cin >> Selected_Index;
    }
    int Vector_Index = Selected_Index - 1;
    int Trash_Count;
    cout << "���� �����۰� ������ �Է��ϼ���.(�� ������ ���� ��� 0���� ��������)" << endl;
    cout << "��Ҹ� ���� ��� ���� ��� �ƹ� Ű�� ��������." << endl;
    cin >> Trash_Count;
    if (cin.fail())
    {
        cout << "������ �����⸦ ����Ѵ�!" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }
    else if (Trash_Count == 0)
    {
        string Remove_Item_Name = _Inventory_Items[Vector_Index]._Item_Name;
        for (int i = Vector_Index; i < _Current_Quantity_Of_Items - 1; i++)
        {
            _Inventory_Items[i] = _Inventory_Items[i + 1];
        }
       _Current_Quantity_Of_Items--;
        cout << Remove_Item_Name << "��(��) ��� ���ȴ�!" << endl;

    }
    else if (Trash_Count < 0)
    {
        cout << "������ �Է��Ѵٰ� �������� �þ�� �ʴ´�! �ٽ� �Է��ϼ���." << endl;
        return;
    }
    else if (Trash_Count > _Inventory_Items[Vector_Index]._Item_Count)
    {
        cout << "���� �ִ� �������� �� ���� �� �������� �ߴ�. Ȯ���ϰ� �ٽ� �Է��ϼ���." << endl;
        return;
    }
    else
    {
        string Remove_Item_Name = _Inventory_Items[Vector_Index]._Item_Name;
        _Inventory_Items[Vector_Index]._Item_Count -=Trash_Count;

        if (_Inventory_Items[Vector_Index]._Item_Count == 0)
        {
            for (int i = Vector_Index; i < _Current_Quantity_Of_Items - 1; i++)
            {
                _Inventory_Items[i] = _Inventory_Items[i + 1];
            }
            _Current_Quantity_Of_Items--;
            cout << Remove_Item_Name << "��(��) ��� ���ȴ�." << endl;
            return;
        }
        else
        {
            cout << Remove_Item_Name << "��(��) " << Trash_Count << "��ŭ ���Ƚ��ϴ�." << endl;
        }
    }
}

template <typename T>//5-5 ������ ������ ����
void Inventory<T>::Remove_Last_Item()
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "������ �������� ����!" << endl;
        return;
    }
    _Current_Quantity_Of_Items--;
    cout << "������ �������� �����ߴ�!" << endl;
}

template <typename T>//5-6 ���� �� ������ ���� ���
void Inventory<T>::Use_Random_Item_In_Battle(Player& player, Monster& monster)
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "����� �������� ����!" << endl;
        return;
    }
    Print_Inventory();
    int Random_Item_use = rand() % _Current_Quantity_Of_Items;
    T* selected_item = Get_Item_By_Index(Random_Item_use); //  GetItemByIndex ȣ�� ����� ������ Item ������ ���� ����
    if (selected_item == nullptr)
    {
        return;
    }
    string selected_item_name = selected_item->_Item_Name; // ������ ������ �̸��� ������ string ���� ����
    if (selected_item->_Item_Type_Usable == true)
    {
        selected_item->Item_Effect(player, monster);
        Use_Item_By_Name(selected_item_name);
        return;
    }
    else
    {
        int Mental_Damage = 100;
        cout << "����� �� ���� �������̴�!" << endl;
        cout << "��Ÿ��� ���Դϴ�!" << endl;
        cout << "���� ���� ����� �ִ��� ���´�!" << endl;
        cout << "�������� ������ �޴´�! �������� " << Mental_Damage << "��ŭ �޴´�!" << endl;
        player.Set_Hp(
                      max(0,
                             player.Get_Hp() - Mental_Damage));
        return;
    }
}

template<typename T>//6-1 ������ ����
void Inventory<T>::Sort_Inventory()
{
     cout << R"(
    � �������� �����ұ��?
    1.�̸���
    2.���Լ�
    3.������
    4.���ݼ�
    0.���
    )" << endl;
    int Sort_Choice;
    cin >> Sort_Choice;
    switch (Sort_Choice)
    {
        case 1:
        {
        sort(_Inventory_Items, _Inventory_Items + _Current_Quantity_Of_Items,
            [](const T& a, const T& b)
            {
                return a._Item_Name < b._Item_Name;
            });
        break;
        }
        case 2:
        {
            sort(_Inventory_Items, _Inventory_Items + _Current_Quantity_Of_Items,
            [](const T& a, const T& b)
            {
                return a._Item_Weight < b._Item_Weight;
            });
        break;
        }
        case 3:
        {
            sort(_Inventory_Items, _Inventory_Items + _Current_Quantity_Of_Items,
            [](const T& a, const T& b)
            {
                return a._Item_Count < b._Item_Count;
            }
        );

        break;
        }
        case 4:
        {
            sort(_Inventory_Items, _Inventory_Items + _Current_Quantity_Of_Items,
            [](const T& a, const T& b)
            {
                return a._Item_Price < b._Item_Price;
            }
        );
        break;
    }

    case 0:
    {
        cout << "������ ����Ѵ�." << endl;
        break;
    }
    default:
    {

        cout << "�߸��� �Է��̴�." << endl;
        break;
    }
    }
}

template<typename T>//6-2 ������ ���� ��� �ٲٱ�
void Inventory<T>::Change_Inventory_Order()
{
    if (_Current_Quantity_Of_Items==0)
           {
               cout << "�κ��丮�� ��� �ִ�." << endl;
               return;
           }
           if (_Current_Quantity_Of_Items < 2)
           {
               cout << "������ �ٲ� �������� �����ϴ�." << endl;
               return;
           }
           Print_Inventory();
           int First_Selected_Index;
           int Second_Selected_Index;
          
           cout << "ù ��°�� �ٲ� ������ ��ȣ�� �Է��ϼ���: ";
           cin >> First_Selected_Index;
         
          
           while (First_Selected_Index<1 || First_Selected_Index > _Current_Quantity_Of_Items)
           {
               cout << "�߸��� �Է��̴�. �ٽ� �Է��ϼ���: ";
               cin >> First_Selected_Index;

           }
           cout << "�� ��°�� �ٲ� ������ ��ȣ�� �Է��ϼ���: ";
           cin >> Second_Selected_Index;
           while (Second_Selected_Index<1 || Second_Selected_Index >_Current_Quantity_Of_Items)
           {
               cout << "�߸��� �Է��̴�. �ٽ� �Է��ϼ���: ";
               cin >> Second_Selected_Index;
           }
           if (First_Selected_Index == Second_Selected_Index)
           {
               cout << "���� ������ ��ȣ�� �����ߴ�. ������ �������� �ʴ´�." << endl;
               return;
           }
           int First_Vector_Index = First_Selected_Index - 1;
           int Second_Vector_Index = Second_Selected_Index - 1;
           swap(_Inventory_Items[First_Vector_Index],_Inventory_Items[Second_Vector_Index]);
           cout << "������ ������ �����ߴ�." << endl;
}

template<typename T>//7.�κ��丮 �뷮 Ȯ��
void Inventory<T>::Increase_Max_Capacity(int new_max_capacity)
{
    if (new_max_capacity <= _Max_Inventory_Size)
    {
        return;
    }
    T* new_items = new T[new_max_capacity];
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        new_items[i] = _Inventory_Items[i];
    }
    delete[] _Inventory_Items;
    _Inventory_Items = new_items;
    _Max_Inventory_Size = new_max_capacity;
    cout << "�κ��丮 ������ " << new_max_capacity << "ĭ���� Ȯ��Ǿ���!" << endl;
}

template<typename T>//8.�κ��丮 �Ҹ���
Inventory<T>::~Inventory()
{
    delete[] _Inventory_Items;
    _Inventory_Items = nullptr;
}

template<typename T>//9-1.�κ��丮 �� money ��ȸ
int Inventory<T>::Get_Money()const
{
    return _Money;
}

template<typename T>//9-2. �κ��丮 �� money ����
void Inventory<T>::Set_Money(int money)
{
    this->_Money = money;
}
template class Inventory<Item>; // ����� �ν��Ͻ�ȭ