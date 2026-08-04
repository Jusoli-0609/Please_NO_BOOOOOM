#pragma once
#include "Player.h"
// JSR로 이름 바꿔놨습니다!
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