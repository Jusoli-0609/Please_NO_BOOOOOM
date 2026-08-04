#pragma once
#include "Equipment.h"
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
#include <string>
#include <vector>

class Items_Equipments_Repository
{
private:
	std::vector<Equipment> _equipments;

public:
	Items_Equipments_Repository();

	void Initial_Items();

	const std::vector<Equipment>&
		Get_All_Equipments() const;

	const Equipment* Find_Equipment_By_Name
	(
		const std::string& equipment_Name
	) const;
};
