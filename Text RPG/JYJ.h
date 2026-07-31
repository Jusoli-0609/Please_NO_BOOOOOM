#pragma once
#include "Player.h"

class JYJ : public Player
{
public:
	JYJ(const std::string& name);

	void Attack(Monster* monster) override;

	void Skill1(Monster* monster) override;
	void Skill2(Monster* monster) override;
	void Skill3(Monster* monster) override;

	void Groggy_Attack(Monster* monster) override;
};