#include "Character.h"
#include "Inventory.h"
#include "Player.h"
#include "Magician.h"
#include "Warrior.h"
#include "Thief.h"
#include "Archer.h"
#include <string>


using namespace std;

void PrintLine();

void InputHPMP(int stat[])
{
	cout << "HP와 MP를 입력해주세요." << endl
		<< "50이상 100이하만 입력 가능합니다." << endl;
	while (true)
	{
		cout << "HP : ";
		cin >> stat[0];

		cout << "MP : ";
		cin >> stat[1];

		if (stat[0] >= 50 && stat[0] <= 100 &&
			stat[1] >= 50 && stat[1] <= 100)
			break;

		cout << "50~100 사이의 값을 입력해주세요." << endl;
	}
}

void Inputstats(int stat[])
{
	cout << "공격력과 방어력을 입력해주세요." << endl
		<< "50이상 100이하만 입력 가능합니다." << endl;
	while (true)
	{
		cout << "공격력 : ";
		cin >> stat[2];

		cout << "방어력: ";
		cin >> stat[3];

		if (stat[2] >= 50 && stat[2] <= 100 &&
			stat[3] >= 50 && stat[3] <= 100)
			break;

		cout << "50~100 사이의 값을 입력해주세요." << endl;
	}
}	   //HPMP와 나눈 이유 : 그 사이 유효성 검사 실행을 위해

void CreateCharacter(string& name, int stat[])		//캐릭터 생성 함수
{
	cout << "용사의 이름을 입력해주세요: ";
	cin >> name;

	InputHPMP(stat);
	Inputstats(stat);
}

void PrintStatus(string& name, int stat[])		// 능력치 함수
{
	PrintLine();
	cout << name << "의 현재 능력치" << endl;
	PrintLine();
	cout << "HP: " << stat[0] << "		MP: " << stat[1] << endl;
	cout << "공격력: " << stat[2] << "	방어력: " << stat[3] << endl;
	PrintLine();
}

void Upgrade(string& name, int stat[], Inventory<Item>& inventory)
{
	int choice;
	bool isGamestart = false;			//게임 시작 여부

	while (!isGamestart)
	{
		cout << "< 캐릭터 강화 >" << endl
			<< "1. HP UP    2. MP UP    3. 공격력 2배" << endl
			<< "4. 방어력 2배  5. 현재 능력치  0. 게임 시작" << endl;

		PrintLine();

		cout << "번호를 선택해주세요: ";
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			stat[0] += 20;
			// inventory.UseItem(1);
			break;

		case 2:
			stat[1] += 20;
			// inventory.UseItem(2);
			break;

		case 3:
			stat[2] *= 2;
			cout << "* 공격력이 2배 증가했습니다." << endl;
			break;

		case 4:
			stat[3] *= 2;
			cout << "* 방어력이 2배증가했습니다." << endl;
			break;

		case 5:

			PrintStatus(name, stat);
			break;

		case 0:
			cout << "게임을 시작합니다!" << endl;
			isGamestart = true;
			break;
		}
	
	}
}

void ChoiceJob(string& name, int stat[], Player*& player)
{
	int Options;

	cout << name << "님, 직업을 선택해주세요!" << endl;
	cout << "1. 전사   2. 마법사   3. 도적   4. 궁수" << endl;
	cout << "선택: ";
	cin >> Options;

	switch (Options)
	{
	case 1:
		player = new Warrior(name, stat);

		cout << "* 전사로 전직하였습니다. (방어력 +30)" << endl;

		
		// player->attack();
		player->printPlayerStatus();

		break;

	case 2:
	{
		player = new Magician(name, stat);

		cout << "* 마법사로 전직하였습니다. (MP +30)" << endl;

		
		// player->attack();
		player->printPlayerStatus();

		break;
	}

	case 3:
		player = new Thief(name, stat);

		cout << "* 도적으로 전직하였습니다. (공격력 +30)" << endl;

		// player->attack();
		player->printPlayerStatus();

		break;

	case 4:
		player = new Archer(name, stat);

		cout << "* 궁수로 전직하였습니다. (HP +30)" << endl;

		// player->attack();
		player->printPlayerStatus();

		break;
	}
}