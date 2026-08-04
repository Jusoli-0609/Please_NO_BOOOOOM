#pragma once
#include "Player.h"
// JSR·Î ÀÌ¸§ ¹Ù²ã³ù½À´Ï´Ù!
class JSR : public Player
{
public:
	JSR(const std::string& name);

	void Attack(Monster* monster) override;

	void Skill1(Monster* monster) override;
	void Skill2(Monster* monster) override;
	void Skill3(Monster* monster) override;

	void Groggy_Attack(Monster* monster) override;
};