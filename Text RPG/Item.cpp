#include <iostream>
#include <string>
#include <algorithm>

#include "Item.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

//1.������ ��������
void Item::Print_Info() const
{
    cout << "������ �̸�: "
        << _Item_Name << ", ����: "
        << _Item_Description<< ", ����: "
        << _Item_Price << ", ����:"
        << _Item_Count << ", ������ ����: "
        << _Item_Weight << endl;
    Print_Ascii_Art();
}

//2.������ ȿ�� ����
bool Item::Item_Effect(Player& player, Monster& monster)
{
    if (_Item_Name == "�Ŷ��")
    {
        player.Set_Hp(
                      min(player.Get_Hp() + 50, player.GetMaxHP()));

        cout << "ü���� ȸ���� ���� ü���� "
            << player.Get_Hp()
            << "�̴�."
            << endl;

        return true;
    }
    else if (_Item_Name == "�������帵ũ")
    {
        player.Set_Mp(min(player.Get_Mp() + 50, player.GetMaxMP()));

        cout << "������ ȸ���� ���� ������ "
            << player.Get_Mp()
            << "�̴�."
            << endl;

        return true;
    }
    else if (_Item_Name == "�Ͻ����� ���ݷ� ���� ������ ������")
    {
        player.Set_ATK(player.Get_ATK() + 50);
        _Need_Item_Reverse_Effect = true;
       _Need_Reverse_Effect_Of_Attack_Potion_Buff = true;
        return true;
    }
    return false;
}

//3.������ ȿ�� ����
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

void Item::Print_Ascii_Art() const
{
    cout << _Item_Ascii_Art << endl;
}
