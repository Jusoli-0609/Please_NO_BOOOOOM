#pragma once
#include "Equipment.h"

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
