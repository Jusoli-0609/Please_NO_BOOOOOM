#include "Recipe_Repository.h"
#include "Monster.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

namespace
{
	map<string, int> Get_Ingredients_By_Level
	(
		int equipment_Level
	)
	{
		switch (equipment_Level)
		{
		case 1:
		{
			return
			{
				{ "하급 코드 조각", 3 }
			};
		}

		case 2:
		{
			return
			{
				{ "하급 코드 조각", 6 }
			};
		}

		case 3:
		{
			return
			{
				{ "중급 코드 조각", 3 }
			};
		}

		case 4:
		{
			return
			{
				{ "중급 코드 조각", 6 }
			};
		}

		case 5:
		{
			return
			{
				{ "상급 코드 조각", 5 }
			};
		}

		default:
		{
			return {};
		}
		}
	}
}

Recipe_Repository::Recipe_Repository()
{
	const vector<string> equipment_Types =
	{
		"마우스",
		"언리얼 엔진",
		"안경",
		"키보드",
		"헤드셋"
	};

	for
		(
			int equipment_Level = 1;
			equipment_Level <= 5;
			equipment_Level++
			)
	{
		for
			(const string& equipment_Type : equipment_Types)
		{
			string equipment_Name = to_string(equipment_Level) + equipment_Type;

			recipes.push_back
			(All_Recipes(equipment_Name, Get_Ingredients_By_Level(equipment_Level)));
		}
	}
}

const vector<All_Recipes>&
Recipe_Repository::
Get_All_Recipes() const
{
	return recipes;
}