#pragma once
#include "Player.h"
//이것도 이름부분 바꿔놨습니다.
class JWH : public Player
{
public:
	JWH(const std::string& name);

	void Attack(Monster* monster) override;

	void Skill1(Monster* monster) override;
	void Skill2(Monster* monster) override;
	void Skill3(Monster* monster) override;

	void Groggy_Attack(Monster* monster) override;
};