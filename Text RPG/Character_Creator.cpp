#include <iostream>
#include <string>

#include "Character_Creator.h"
#include "Player.h"
#include "Job_Selection.h"
using namespace std;

Player* Character_Creator()
{
	const int SIZE = 7;
	int stat[SIZE] = {100, 100, 20, 20, 20, 20, 20};

	string name;

	cout << "캐릭터의 이름을 정해주세요: ";

	cin >> name;

	return Job_Selection();

}