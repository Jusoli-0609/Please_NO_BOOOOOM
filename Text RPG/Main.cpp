#include "DungeonManager.h"
#include "Inventory.h"
#include "Item.h"
#include "JYJ.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits>

using namespace std;

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));

	JYJ player("테스트 플레이어");

	Inventory<Item> inventory(30, 100);

	Dungeon_Manager dungeon_Manager;

	while (true)
	{
		cout << endl;
		cout << "========================================" << endl;
		cout << "[ 던전 기능 테스트 메뉴 ]" << endl;
		cout << "========================================" << endl;
		cout << "1. 던전 메뉴 열기" << endl;
		cout << "2. 플레이어 상태 확인" << endl;
		cout << "3. 인벤토리 확인" << endl;
		cout << "4. 테스트용 HP/MP 회복" << endl;
		cout << "5. 최종보스 데이터 테스트" << endl;
		cout << "0. 테스트 종료" << endl;
		cout << "선택: ";

		int test_Choice = -1;

		cin >> test_Choice;

		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			cout << "숫자를 입력해주세요." << endl;

			continue;
		}

		switch (test_Choice)
		{
		case 1:
		{
			dungeon_Manager.Open_Dungeon(&player, inventory);

			break;
		}

		case 2:
		{
			player.Print_Status();

			break;
		}

		case 3:
		{
			inventory.Print_Inventory();

			break;
		}

		case 4:
		{
			player.Set_Hp(player.GetMaxHP());
			player.Set_Mp(player.GetMaxMP());

			cout << "HP와 MP를 모두 회복했습니다." << endl;

			break;
		}

		case 0:
		{
			cout << "테스트를 종료합니다." << endl;

			return 0;
		}

		default:
		{
			cout << "잘못된 선택입니다." << endl;

			break;
		}
		}
	}
}