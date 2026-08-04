#include "Camp_Manager.h"
#include <iostream>
#include "Items_Equipments_Repository.h"

using namespace std;

Camp_Manager::Camp_Manager
(
    Player& player,
    Inventory<Item>& inventory,
    Inventory_For_Equipments_Only& 
    inventory_for_equipments,
    Currently_Equipped_Equipments& 
    currently_equipped_equipments
)
    : player(player),
    inventory(inventory),
    inventory_for_equipments(inventory_for_equipments),
    currently_equipped_equipments(currently_equipped_equipments)
{
}

void Camp_Manager::Open_Camp_Menu()
{
    while (true)
    {
        cout << "\n===== ���Ϲ��ķ�� ������� =====\n";
        cout << "1. ����ķ 119 �⺻ ���� �ޱ�\n";
        cout << "2. �� �����\n";
        cout << "3. ����ȣ �Ŵ������� ���� ��ȭ��\n";
        cout << "4. �赿�� �Ŵ������� ����ǰ ���Լ�\n";
        cout << "5. ��Ű�� ���尣\n";
        cout << "0. ������\n";
        cout << "����: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (Received_Basic_Items == true)
            {
                cout << "�̹� ������ �޾Ҵ�! ��Ű�� ȭ���� ������!\n";
                player.SetHP(player.GetHP() - 1);
                break;
            }
            Give_Basic_Training_Item();
            Received_Basic_Items = true;
            break;
        }

        case 2:
        {
            Open_Pep_Store_Menu();
            break;
        }

        case 3:
        {
            Open_General_Store_Menu();
            break;
        }

        case 4:
        {
            Open_Loot_Shop_Menu();
            break;
        }

        case 5:
        {
            Open_Cookie_Blacksmith_Menu();
            break;
        }

        case 0:
        {
            cout << "������ҿ��� �����ϴ�." << endl;
            return;
        }

        default:
        {
            cout << "�߸��� �����Դϴ�." << endl;
            break;
        }
        }
    }
}

void Camp_Manager::Give_Basic_Training_Item()
{
    cout << "\n===== ����ķ 119 =====\n";
    cout << "�⺻ ����ǰ�� ���޹޾ҽ��ϴ�!\n";
}

void Camp_Manager::Open_Pep_Store_Menu()
{
    while (true)
    {
        cout << "\n===== �� ����� =====\n";
        cout << "1. ��� ����\n";
        cout << "2. ��� �Ǹ�\n";
        cout << "0. �ڷΰ���\n";
        cout << "���� : ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (inventory.Get_Money() <= 0)
            {
                break;
            }
            cout << "�⺻ CPU�� �����߽��ϴ�.\n";
            break;
        }

        case 2:
        {
            // TODO : �Ǹ�
            break;
        }

        case 0:
        {
            return;
        }

        default:
        {
            cout << "�߸��� �Է��Դϴ�.\n";
            break;
        }
        }
    }
}

void Camp_Manager::Open_General_Store_Menu()
{
    cout << "\n===== ����ȣ �Ŵ������� ���� ��ȭ�� =====\n";

    // TODO: �Һ� ������ ���
    // TODO: ���� ó��
}

void Camp_Manager::Open_Loot_Shop_Menu()
{
    cout << "\n===== �赿�� �Ŵ������� ����ǰ ���Լ� =====\n";

    // TODO: ����ǰ �Ǹ�
}

void Camp_Manager::Open_Cookie_Blacksmith_Menu()
{
    while (true)
    {
        cout << endl;
        cout << "========================================" << endl;
        cout << "[ ��Ű�� �ڵ� ���尣 ]" << endl;
        cout << "========================================" << endl;
        cout << "1. ��� ��ȭ" << endl;
        cout << "2. �ڵ� �������� ��� ����" << endl;
        cout << "3. ��� ����" << endl;
        cout << "0. �ڷΰ���" << endl;
        cout << "����: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "����� �� ���ȭ��� ����� �ּ���" << endl;
            break;
        }

        case 2:
        {
            craft_work_shop.Craft_Item(inventory, inventory_for_equipments);
            break;
        }

        case 3:
        {
            craft_work_shop.Decomposition_Item(inventory_for_equipments, inventory);
            break;
        }

        case 0:
        {
            return;
        }

        default:
        {
            cout << "�߸��� �Է��̴�." << endl;
            break;
        }
        }
    }
}