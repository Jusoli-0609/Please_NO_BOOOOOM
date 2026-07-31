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

template<typename T>//1-1 기본 생성자
Inventory<T>::Inventory(int max_inventory_size, int max_capacity)
{
    _Max_Inventory_Size = max_inventory_size;
    _Max_Capacity = max_capacity;
    _Current_Quantity_Of_Items = 0;
    {
        _Inventory_Items = new T[_Max_Inventory_Size];
    }
}

template<typename T>//1- 2복사 생성자
Inventory<T>::Inventory(const Inventory<T>& other)// 기존 객체와 같은 상태를 가진 새 객체가 필요할 때 쓰임)
{
    _Max_Inventory_Size = other._Max_Inventory_Size;
    _Current_Quantity_Of_Items = other._Current_Quantity_Of_Items;
    _Max_Capacity = other._Max_Capacity;
    _Inventory_Items = new T[_Max_Inventory_Size];
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        _Inventory_Items[i] = other._Inventory_Items[i];
    }
}

template<typename T>//2-1 대입 연산자 
Inventory<T>& Inventory<T>::operator=(const Inventory<T>& other)//(다른 Inventory<T> 객체를 받아서, 현재 객체에 복사하고, 현재 객체 자신을 반환)
{
    if (this == &other)
    {
        return *this;
    }
    delete[] _Inventory_Items;
    _Max_Inventory_Size = other._Max_Inventory_Size;
    _Max_Capacity = other._Max_Capacity;
    _Current_Quantity_Of_Items = other._Current_Quantity_Of_Items;
    _Inventory_Items = new T[_Max_Inventory_Size];
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        _Inventory_Items[i] = other._Inventory_Items[i];
    }
    return *this;
}

template<typename T>//3-1 인벤토리 총 무게 함수
int Inventory<T>::Get_Total_Weight()const
{
    int Total_Weight = 0;
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        Total_Weight += _Inventory_Items[i]._Item_Weight * _Inventory_Items[i]._Item_Count;
    }
    return Total_Weight;
}

template<typename T>// 3-2 인벤토리 Index  가져오기
T* Inventory<T>::Get_Item_By_Index(int index)
{
    if (index < 0 || index >= _Current_Quantity_Of_Items)
    {
        return nullptr;
    }
    return &_Inventory_Items[index];
}

template<typename T>//3-3 인벤토리 사이즈 가져오기
int Inventory<T>::Get_Size()const
{
    return _Current_Quantity_Of_Items;
}

template<typename T>// 3-4 인벤토리 무게 가져오기
int Inventory<T>::Get_Capacity() const
{
    return _Max_Capacity;
}

template <typename T>//4-1 인벤토리 및 내용물 출력
void Inventory<T>::Print_Inventory() const
{
    cout << "===== 인벤토리 =====" << endl;
    int  Inventory_Order_Index = 1;
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)
    {

        cout << Inventory_Order_Index << ".";
        _Inventory_Items[i].Print_Info();
        Inventory_Order_Index++;
    }
    cout << " 현재 무게  : " <<
        Get_Total_Weight() << "최대 허용 무게  : " <<
        _Max_Capacity << " 남은 허용 무게  : " <<
        _Max_Capacity - Get_Total_Weight() << endl;
}

template <typename T>//4-2 인벤토리 메뉴 출력
void Inventory<T>::Print_Inventory_Menu()
{
    cout << R"(
    무엇을 할까?
    1. 전체 인벤토리 보기
    2. 아이템 정렬
    3. 아이템 순서 바꾸기
    4. 아이템 버리기
    0. 되돌아가기)" << endl;
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

template<typename T>//5-1 아이템 추가 및 갯수 증가
bool Inventory<T>::Add_Or_Increase_Item(const T& new_item)
{
    int New_Item_Weight = new_item._Item_Weight * new_item._Item_Count;
    T* Found_Item = nullptr;  //  같은 아이템을 가리킬 포인터 변수 선언
    for (int i = 0; i < _Current_Quantity_Of_Items; i++)//순회 반복문
    {
        if (_Inventory_Items[i]._Item_Name == new_item._Item_Name)
        {
            Found_Item = &_Inventory_Items[i];//foundItem에 현재 item의 주소 저장
            break;
        }
    }
    //1.무게 검사
    while (Get_Total_Weight() + New_Item_Weight > _Max_Capacity)
    {
        cout << "인벤토리의 무게가 총 용량을 초과했다! 물건을 버릴 것인가?" << endl;
        cout << "1. 버리기" << endl;
        cout << "2. 취소" << endl;
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
                    Found_Item = &_Inventory_Items[i]; //댕글링 포인터 방지
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
            cout << "잘못된 입력이다!" << endl;
        }
    }
    if (Found_Item != nullptr)
    {
        Found_Item->_Item_Count += new_item._Item_Count;
        cout << new_item._Item_Name << "의 갯수가 " << new_item._Item_Count << "만큼 증가했다!" << endl;
        return true;
    }
    while (_Current_Quantity_Of_Items >= _Max_Inventory_Size)
    {
        cout << "인벤토리 슬롯이 가득 찼다! 어떤 물건을 버릴 것인가?" << endl;
        cout << "1. 버리기" << endl;
        cout << "2. 취소" << endl;
        int Choose_Item_To_Get_Rid_Of;
        cin >> Choose_Item_To_Get_Rid_Of;
        if (Choose_Item_To_Get_Rid_Of == 1)
        {
            Throw_Away_Item();
        }
        else if (Choose_Item_To_Get_Rid_Of == 2)
        {
            return false;
        }
        else
        {
            cout << "잘못된 입력이다!" << endl;
        }
    }
    _Inventory_Items[_Current_Quantity_Of_Items] = new_item;
    _Current_Quantity_Of_Items++;
    cout << "새로운 아이템 : " << new_item._Item_Name << "가 추가됐다!" << endl;
    return true;
}

template<typename T>//5-2 이름으로 아이템 사용 성공 및 갯수 감소
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

template <typename T>//5-3 전투 중 아이템 사용
void Inventory<T>::Use_Item_In_Battle(Player& player, Monster& monster)
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "사용할 아이템이 없다!" << endl;
        return;
    }
    Print_Inventory();
    int Choose_Item_To_Use_In_Battle;
    cout << "전투 중 사용할 아이템을 고르세요!" << endl;
    cin >> Choose_Item_To_Use_In_Battle;
    int Vector_Index = Choose_Item_To_Use_In_Battle - 1;
    T* selected_item = Get_Item_By_Index(Vector_Index); //  GetItemByIndex 호출 결과를 저장할 Item 포인터 변수 선언
    if (selected_item == nullptr)
    {
        cout << "잘못된 아이템 번호다!" << endl;
        return;
    }
    string selected_item_name = selected_item->_Item_Name; // 선택한 아이템 이름을 저장할 string 변수 선언
    if (selected_item->_Item_Type_Usable == true)
    {
        selected_item->Item_Effect(player, monster);
        Use_Item_By_Name(selected_item_name);
        return;
    }
    else
    {
        cout << "사용할 수 없는 아이템이다!" << endl;
        return;
    }
}

template <typename T>//5-4 물건 버리기
void Inventory<T>::Throw_Away_Item()
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "버릴 아이템이 없다!" << endl;
        return;
    }
    Print_Inventory();
    int Selected_Index;
    cout << "몇 번 아이템을 버릴 것인가?" << endl;
    cin >> Selected_Index;
    while (Selected_Index<1 || Selected_Index>_Current_Quantity_Of_Items)
    {
        cout << "잘못된 입력이다. 다시 입력하세요." << endl;
        cin >> Selected_Index;
    }
    int Vector_Index = Selected_Index - 1;
    int Trash_Count;
    cout << "버릴 아이템과 갯수를 입력하세요.(다 버리길 원할 경우 0번을 누르세요)" << endl;
    cout << "취소를 원할 경우 숫자 대신 아무 키나 누르세요." << endl;
    cin >> Trash_Count;
    if (cin.fail())
    {
        cout << "아이템 버리기를 취소한다!" << endl;
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
        cout << Remove_Item_Name << "을(를) 모두 버렸다!" << endl;

    }
    else if (Trash_Count < 0)
    {
        cout << "음수를 입력한다고 아이템이 늘어나지 않는다! 다시 입력하세요." << endl;
        return;
    }
    else if (Trash_Count > _Inventory_Items[Vector_Index]._Item_Count)
    {
        cout << "갖고 있는 갯수보다 더 많은 걸 버릴려고 했다. 확인하고 다시 입력하세요." << endl;
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
            cout << Remove_Item_Name << "을(를) 모두 버렸다." << endl;
            return;
        }
        else
        {
            cout << Remove_Item_Name << "을(를) " << Trash_Count << "만큼 버렸습니다." << endl;
        }
    }
}

template <typename T>//5-5 마지막 아이템 제거
void Inventory<T>::Remove_Last_Item()
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "제거할 아이템이 없다!" << endl;
        return;
    }
    _Current_Quantity_Of_Items--;
    cout << "마지막 아이템을 제거했다!" << endl;
}

template <typename T>//5-6 전투 중 아이템 랜덤 사용
void Inventory<T>::Use_Random_Item_In_Battle(Player& player, Monster& monster)
{
    if (_Current_Quantity_Of_Items == 0)
    {
        cout << "사용할 아이템이 없다!" << endl;
        return;
    }
    Print_Inventory();
    int Random_Item_use = rand() % _Current_Quantity_Of_Items;
    T* selected_item = Get_Item_By_Index(Random_Item_use); //  GetItemByIndex 호출 결과를 저장할 Item 포인터 변수 선언
    if (selected_item == nullptr)
    {
        return;
    }
    string selected_item_name = selected_item->_Item_Name; // 선택한 아이템 이름을 저장할 string 변수 선언
    if (selected_item->_Item_Type_Usable == true)
    {
        selected_item->Item_Effect(player, monster);
        Use_Item_By_Name(selected_item_name);
        return;
    }
    else
    {
        int Mental_Damage = 100;
        cout << "사용할 수 없는 아이템이다!" << endl;
        cout << "안타까운 일입니다!" << endl;
        cout << "운이 없는 당신을 주님이 비웃는다!" << endl;
        cout << "정신적인 고통을 받는다! 데미지를 " << Mental_Damage << "만큼 받는다!" << endl;
        player.Set_Hp(
                      max(0,
                             player.Get_Hp() - Mental_Damage));
        return;
    }
}

template<typename T>//6-1 아이템 정렬
void Inventory<T>::Sort_Inventory()
{
     cout << R"(
    어떤 기준으로 정렬할까요?
    1.이름순
    2.무게순
    3.개수순
    4.가격순
    0.취소
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
        cout << "정렬을 취소한다." << endl;
        break;
    }
    default:
    {

        cout << "잘못된 입력이다." << endl;
        break;
    }
    }
}

template<typename T>//6-2 아이템 순서 골라 바꾸기
void Inventory<T>::Change_Inventory_Order()
{
    if (_Current_Quantity_Of_Items==0)
           {
               cout << "인벤토리가 비어 있다." << endl;
               return;
           }
           if (_Current_Quantity_Of_Items < 2)
           {
               cout << "순서를 바꿀 아이템이 부족하다." << endl;
               return;
           }
           Print_Inventory();
           int First_Selected_Index;
           int Second_Selected_Index;
          
           cout << "첫 번째로 바꿀 아이템 번호를 입력하세요: ";
           cin >> First_Selected_Index;
         
          
           while (First_Selected_Index<1 || First_Selected_Index > _Current_Quantity_Of_Items)
           {
               cout << "잘못된 입력이다. 다시 입력하세요: ";
               cin >> First_Selected_Index;

           }
           cout << "두 번째로 바꿀 아이템 번호를 입력하세요: ";
           cin >> Second_Selected_Index;
           while (Second_Selected_Index<1 || Second_Selected_Index >_Current_Quantity_Of_Items)
           {
               cout << "잘못된 입력이다. 다시 입력하세요: ";
               cin >> Second_Selected_Index;
           }
           if (First_Selected_Index == Second_Selected_Index)
           {
               cout << "같은 아이템 번호를 선택했다. 순서를 변경하지 않는다." << endl;
               return;
           }
           int First_Vector_Index = First_Selected_Index - 1;
           int Second_Vector_Index = Second_Selected_Index - 1;
           swap(_Inventory_Items[First_Vector_Index],_Inventory_Items[Second_Vector_Index]);
           cout << "아이템 순서를 변경했다." << endl;
}

template<typename T>//7.인벤토리 용량 확장
void Inventory<T>::Increase_Max_Capacity(int new_max_capacity)
{
    if (new_max_capacity <= _Max_Inventory_Size)
    {
        return;
    }
    T* new_items = new T[new_max_capacity];
    for (int = i = 0; i < _Current_Quantity_Of_Items; i++)
    {
        new_items[i] = _Inventory_Items[i];
    }
    delete[] _Inventory_Items;
    _Inventory_Items = new_items;
    _Max_Inventory_Size = new_max_capacity;
    cout << "인벤토리 슬롯이 " << new_max_capacity << "칸으로 확장되었다!" << endl;
}

template<typename T>//8.인벤토리 소멸자
Inventory<T>::~Inventory()
{
    delete[] _Inventory_Items;
    _Inventory_Items = nullptr;
}

template class Inventory<Item>; // 명시적 인스턴스화