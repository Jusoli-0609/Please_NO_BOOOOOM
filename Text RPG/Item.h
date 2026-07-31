#pragma once
#include <string>
#include <iostream>

class Player;
class Monster;
class Item
{
public:
    std::string _Item_Name;
    int _Item_Price;
    int _Item_Count;
    int _Item_Weight;
    bool _Item_Type_Usable;
    bool _Item_Type_Wearable;
    bool _Need_Item_Reverse_Effect=false;
    bool _Need_Reverse_Effect_Of_Attack_Potion_Buff = false;
    void Print_Info() const;//1.아이템 정보 내보내기
    bool Item_Effect(Player& player, Monster& monster);//2.아이템 효과 적용
    bool Item_Effect_Reverse(Player& player, Monster& monster);//3.아이템 효과 해제
   
};

