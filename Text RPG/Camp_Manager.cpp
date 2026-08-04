#include "Camp_Manager.h"
#include <iostream>
#include "Items_Equipments_Repository.h"
#include "Ascii_Art_Manager.h"
#include <iomanip>

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
        Ascii_Art_Manager art;
        art.Print("Art/Camp_Manager/TommorowLearnCamp.txt");

        cout << "\n===== 내일배움캠프 재정비소 =====\n";
        cout << "1. 내배캠 119 기본 보급 받기\n";
        cout << "2. 펩 스토어\n";
        cout << "3. 문승호 매니저님의 만물 잡화점\n";
        cout << "4. 김동현 매니저님의 전리품 매입소\n";
        cout << "5. 쿠키의 대장간\n";
        cout << "0. 나가기\n";
        cout << "선택: ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (Received_Basic_Items == true)
            {
                cout << "이미 보급을 받았다! 쿠키가 화내며 할퀸다!\n";
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
            cout << "재정비소에서 나간다."  << endl;
            return;
        }

        default:
        {
            cout << "잘못된 선택이다." << endl;
            break;
        }
        }
    }
}




void Camp_Manager::Give_Basic_Training_Item()
{
    
    cout << "\n===== 내배캠 119 =====\n";
    cout << "기본 장비를 지급받았다!\n";
    Level_1_Engine level_1_engine;
    Level_1_Glasses level_1_glasses;
    Level_1_Keyboard level_1_keyboard;
    Level_1_Mouse level_1_mouse;
    Level_1_Headset level_1_headset;
    inventory_for_equipments.Add_Equipment(level_1_engine);
    inventory_for_equipments.Add_Equipment(level_1_glasses);
    inventory_for_equipments.Add_Equipment(level_1_keyboard);
    inventory_for_equipments.Add_Equipment(level_1_mouse);
    inventory_for_equipments.Add_Equipment(level_1_headset);
}

void Camp_Manager::Open_Pep_Store_Menu()
{
    Ascii_Art_Manager art;
    art.Print("Art/Camp_Manager/FepStore.txt");

    while (true)
    {
        cout << "\n===== 펩 스토어 =====\n";
        cout << "1. 장비 구매\n";
        cout << "2. 장비 판매\n";
        cout << "0. 뒤로가기\n";
        cout << "선택 : ";

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (inventory.Get_Money() <= 0)
            {
                cout << "골드가 없다!\n";
                break;
            }
          
            cout << "\n===== 장비 구매 =====\n";

            Items_Equipments_Repository equipmentRepository;

            const vector<Equipment>& equipments =
                equipmentRepository.Get_All_Equipments();

            for (int i = 0; i < equipments.size(); i += 2)
            {
                cout << left
                    << setw(3) << i + 1
                    << setw(22) << equipments[i].Get_Equipment_Name()
                    << setw(8) << (to_string(equipments[i].Get_Equipment_Price() * 2) + " 젬");

                if (i + 1 < equipments.size())
                {
                    cout << "   ";

                    cout << left
                        << setw(3) << i + 2
                        << setw(22) << equipments[i + 1].Get_Equipment_Name()
                        << setw(8) << (to_string(equipments[i + 1].Get_Equipment_Price() * 2) + " 젬");
                }

                cout << '\n';
            }

            cout << "0. 뒤로가기\n";
            cout << "구매할 장비 선택: ";
            int buyChoice;
            cin >> buyChoice;
        
    
            if (buyChoice == 0)
            {
                break;
            }

            if (buyChoice < 0 || equipments.size() < buyChoice)
            {
                cout << "잘못된 선택이다." << endl;
                break;
            }
            Equipment selectedEquipment = equipments[buyChoice - 1];

            int selectedEquipmentPrice = selectedEquipment.Get_Equipment_Price() * 2;

            if (inventory.Get_Money() < selectedEquipmentPrice)
            {
                cout << "골드가 부족하다!" << endl;
                break;
            }

            if (inventory_for_equipments.Add_Equipment(selectedEquipment) == false)//이 줄은 검사만 하는 줄처럼 보이지만, 실제로는 먼저 함수를 실행
            {
                cout << "구매를 취소했다." << endl;
                break;
            }

            inventory.Set_Money(inventory.Get_Money() - selectedEquipmentPrice);
            cout << "장비를 구매했다!" << endl;
            break;
        }

        case 2:
        {
            cout << "착용중인 장비는 팔 수 없으며 오직 장비 전용 인벤토리 안 장비만 팔 수 있습니다." << endl;
            if (inventory_for_equipments.Get_Equipment_Current_Count() <= 0)
            {
                cout << "판매할 장비가 없다." << endl;
                break;
            }
            inventory_for_equipments.Print_Equipment_Inventory();
            cout << "0. 뒤로가기\n";
            cout << "판매할 장비 선택: " << endl;
            int choose_item_to_sell = -1;
            cin >> choose_item_to_sell;
            if (choose_item_to_sell == 0)
            {
                break;
            }
            else if (choose_item_to_sell < 0 || inventory_for_equipments.Get_Equipment_Current_Count()<choose_item_to_sell)
            {
                cout << "잘못된 선택이다." << endl;
                break;
            }
            else
            {
                int equipmentindex = choose_item_to_sell - 1;
                Equipment selectedequipment= inventory_for_equipments.Get_Equipment_By_Index(equipmentindex);
                int sellPrice = selectedequipment.Get_Equipment_Price();
                bool Is_Removed = inventory_for_equipments.Remove_Equipment_By_index(equipmentindex);
                if (Is_Removed == false)
                {
                    cout << "장비 판매에 실패했다." << endl;
                    break;
                }
                inventory.Set_Money(inventory.Get_Money() + sellPrice);
                cout << selectedequipment.Get_Equipment_Name()
                    << "을(를) 판매했다!" << endl;
                cout << sellPrice << " 젬을 얻었다!" << endl;
                break;
            }
            break;
        }

        case 0:
        {
            return;
        }

        default:
        {
            cout << "잘못된 입력입니다.\n";
            break;
        }
        }
    }
}

void Camp_Manager::Open_General_Store_Menu()
{
    Ascii_Art_Manager art;
    art.Print("Art/Camp_Manager/MrMoonStore.txt");
    while (true)
    {
        cout << "\n===== 문승호 매니저님의 만물 잡화점 =====\n";
        cout << "재고 매진으로 인한 밑 두 가지 물건만 판매 중입니다!" << endl;
        cout << "1. 컵라면" << endl;
        cout << "2. 에너지드링크" << endl;
        cout << "0. 뒤로가기\n";
        cout << "구매할 물건 선택: ";

        int chooseToBuy = -1;
        cin >> chooseToBuy;

        if (chooseToBuy == 0)
        {
            return;
        }

        Item selectedItem;

        if (chooseToBuy == 1)
        {
            selectedItem._Item_Name = "컵라면";
            selectedItem._Item_Ascii_Art =
                R"( .------.
 |RAMEN |
 |~~~~~~|
 '------')";
            selectedItem._Item_Price = 1;
            selectedItem._Item_Count = 1;
            selectedItem._Item_Weight = 1;
            selectedItem._Item_Type_Usable = true;
            selectedItem._Item_Type_Wearable = false;
            selectedItem._Item_Description =
                "지친 체력을 채워 주는 컵라면. 사용하면 HP를 50 회복한다.";
        }
        else if (chooseToBuy == 2)
        {
            selectedItem._Item_Name = "에너지드링크";
            selectedItem._Item_Ascii_Art =
                R"( .------.
 |ENRG++|
 |[MP50]|
 '------')";
            selectedItem._Item_Price = 1;
            selectedItem._Item_Count = 1;
            selectedItem._Item_Weight = 1;
            selectedItem._Item_Type_Usable = true;
            selectedItem._Item_Type_Wearable = false;
            selectedItem._Item_Description =
                "집중력을 끌어올리는 에너지드링크. 사용하면 MP를 50 회복한다.";
        }
        else
        {
            cout << "잘못된 선택이다." << endl;
            continue;
        }

        if (inventory.Get_Money() < selectedItem._Item_Price)
        {
            cout << "골드가 부족하다!" << endl;
            continue;
        }

        inventory.Add_Or_Increase_Item(selectedItem);
        inventory.Set_Money(inventory.Get_Money() - selectedItem._Item_Price);

        cout << selectedItem._Item_Name << "을(를) 구매했다!" << endl;
        cout << selectedItem._Item_Price << " 골드를 사용했다." << endl;
    }
}

void Camp_Manager::Open_Loot_Shop_Menu()
{
    Ascii_Art_Manager art;
    art.Print("Art/Camp_Manager/MrKimStore.txt");
    while (true)
    {        
        cout << "\n===== 김동현 매니저님의 전리품 매입소 =====\n";
        cout << "1. 전리품 판매\n";
        cout << "0. 뒤로가기\n";
        cout << "선택: ";

        int choice = -1;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {

            if (inventory.Get__Current_Quantity_Of_Items() <= 0)
            {
                cout << "판매할 아이템이 없다!" << endl;
                break;
            }
            inventory.Print_Inventory();

            cout << "0. 뒤로가기\n";
            cout << "판매할 전리품의 번호와 갯수를 차례대로 누르세요.";

            int sellChoice = -1;
            cin >> sellChoice;

            if (sellChoice == 0)
            {
                break;
            }

            if (sellChoice < 0 || inventory.Get__Current_Quantity_Of_Items() < sellChoice)
            {
                cout << "잘못된 선택이다." << endl;
                break;
            }
            int sellcount = 0;
            cin >> sellcount;
            int sellIndex = sellChoice - 1;
            Item* selectedItem = inventory.Get_Item_By_Index(sellIndex);
            if (selectedItem == nullptr)
            {
                cout << "아이템 정보를 찾을 수 없다." << endl;
                break;
            }
            if (sellcount <= 0)
            {
                cout << "판매 개수가 잘못됐다." << endl;
                break;
            }
            int Total_Money_Earn = selectedItem->_Item_Price * sellcount;


            bool isRemoved = inventory.Remove_Item_By_Index_And_Count(sellIndex, sellcount);

            if (isRemoved == false)
            {
                cout << "전리품 판매에 실패했다." << endl;
                break;
            }

            inventory.Set_Money(inventory.Get_Money() + Total_Money_Earn);
            cout << selectedItem->_Item_Name << "을(를) 판매했다!" << endl;
            cout << Total_Money_Earn << " 골드를 얻었다!" << endl;

            break;
        }

        case 0:
        {
            return;
        }

        default:
        {
            cout << "잘못된 입력이다." << endl;
            break;
        }
        }
    }
}


void Camp_Manager::Open_Cookie_Blacksmith_Menu()
{
  
    Ascii_Art_Manager art;
    art.Print("Art/Camp_Manager/Cookietheblacksmith.txt");
    while (true)
    {

        cout << endl;
        cout << "========================================" << endl;
        cout << "[ 쿠키의 코드 대장간 ]" << endl;
        cout << "========================================" << endl;
        cout << "1. 장비 강화" << endl;
        cout << "2. 코드 조각으로 장비 제작" << endl;
        cout << "3. 장비 분해" << endl;
        cout << "0. 뒤로가기" << endl;
        cout << "선택: ";

        int choice = -1;

        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            craft_work_shop.Enhance_Item(inventory_for_equipments, inventory);
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
            cout << "잘못된 입력이다." << endl;
            break;
        }
        }
    }
}