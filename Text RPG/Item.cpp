#include <iostream>
#include <string>
#include <algorithm>

#include "Item.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

//1.아이템 내보내기
void Item::Print_Info() const
{
    cout << "아이템 이름: "
        << _Item_Name << ", 가격: "
        << _Item_Price << ", 갯수:"
        << _Item_Count << ", 갯수당 무게: "
        << _Item_Weight << endl;
}

//2.아이템 효과 적용
bool Item::Item_Effect(Player& player, Monster& monster)
{
    if (_Item_Name == "HP 포션")
    {
        player.Set_Hp(
                      min(player.Get_Hp() + 50, player.Get_Max_Hp()));

        cout << "체력을 회복해 현재 체력은 "
            << player.Get_Hp()
            << "이다."
            << endl;

        return true;
    }
    else if (_Item_Name == "MP 포션")
    {
        player.Set_Mp(min(player.Get_Mp() + 50, player.Get_Max_Mp()));

        cout << "마나를 회복해 현재 마나는 "
            << player.Get_Mp()
            << "이다."
            << endl;

        return true;
    }
    else if (_Item_Name == "일시적인 공격력 버프 아이템 예시임")
    {
        player.Set_ATK(player.Get_ATK() + 50);
        _Need_Item_Reverse_Effect = true;
       _Need_Reverse_Effect_Of_Attack_Potion_Buff = true;
        return true;
    }
    return false;
}

//3.아이템 효과 해제
bool Item::Item_Effect_Reverse(Player& player, Monster& monster)
{
    if (_Need_Item_Reverse_Effect == true)
    {
       if(_Need_Reverse_Effect_Of_Attack_Potion_Buff==true)
            {player.Set_ATK(player.Get_ATK() - 50);
             _Need_Item_Reverse_Effect = false;
            _Need_Reverse_Effect_Of_Attack_Potion_Buff = false;
            return true;
       }
       return false;
    }
    return false;
}
