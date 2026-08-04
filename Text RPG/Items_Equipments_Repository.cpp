#include "Items_Equipments_Repository.h"

#include "Level_1_Mouse.h"
#include "Level_1_Engine.h"
#include "Level_1_Glasses.h"
#include "Level_1_Keyboard.h"
#include "Level_1_Headset.h"

#include "Level_2_Mouse.h"
#include "Level_2_Engine.h"
#include "Level_2_Glasses.h"
#include "Level_2_Keyboard.h"
#include "Level_2_Headset.h"

#include "Level_3_Mouse.h"
#include "Level_3_Engine.h"
#include "Level_3_Glasses.h"
#include "Level_3_Keyboard.h"
#include "Level_3_Headset.h"

#include "Level_4_Mouse.h"
#include "Level_4_Engine.h"
#include "Level_4_Glasses.h"
#include "Level_4_Keyboard.h"
#include "Level_4_Headset.h"

#include "Level_5_Mouse.h"
#include "Level_5_Engine.h"
#include "Level_5_Glasses.h"
#include "Level_5_Keyboard.h"
#include "Level_5_Headset.h"

#include "Tutor_Mouse.h"
#include "Tutor_Engine.h"
#include "Tutor_Glasses.h"
#include "Tutor_Keyboard.h"
#include "Tutor_Headset.h"

using namespace std;

Items_Equipments_Repository::
Items_Equipments_Repository()
{
	Initial_Items();
}

void Items_Equipments_Repository::
Initial_Items()
{
	_equipments.clear();
	_equipments.reserve(30);

	_equipments.push_back(Level_1_Mouse());
	_equipments.push_back(Level_1_Engine());
	_equipments.push_back(Level_1_Glasses());
	_equipments.push_back(Level_1_Keyboard());
	_equipments.push_back(Level_1_Headset());

	_equipments.push_back(Level_2_Mouse());
	_equipments.push_back(Level_2_Engine());
	_equipments.push_back(Level_2_Glasses());
	_equipments.push_back(Level_2_Keyboard());
	_equipments.push_back(Level_2_Headset());

	_equipments.push_back(Level_3_Mouse());
	_equipments.push_back(Level_3_Engine());
	_equipments.push_back(Level_3_Glasses());
	_equipments.push_back(Level_3_Keyboard());
	_equipments.push_back(Level_3_Headset());

	_equipments.push_back(Level_4_Mouse());
	_equipments.push_back(Level_4_Engine());
	_equipments.push_back(Level_4_Glasses());
	_equipments.push_back(Level_4_Keyboard());
	_equipments.push_back(Level_4_Headset());

	_equipments.push_back(Level_5_Mouse());
	_equipments.push_back(Level_5_Engine());
	_equipments.push_back(Level_5_Glasses());
	_equipments.push_back(Level_5_Keyboard());
	_equipments.push_back(Level_5_Headset());

	_equipments.push_back(Tutor_Mouse());
	_equipments.push_back(Tutor_Engine());
	_equipments.push_back(Tutor_Glasses());
	_equipments.push_back(Tutor_Keyboard());
	_equipments.push_back(Tutor_Headset());
}

const vector<Equipment>&
Items_Equipments_Repository::
Get_All_Equipments() const
{
	return _equipments;
}

const Equipment*
Items_Equipments_Repository::
Find_Equipment_By_Name
(
	const string& equipment_Name
) const
{
	for
		(const Equipment& equipment : _equipments)
	{
		if
			(equipment.Get_Equipment_Name() == equipment_Name)
		{
			return &equipment;
		}
	}

	return nullptr;
}
