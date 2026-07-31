#include "Level_Up.h"
#include "Player.h" // Player 멤버 함수 접근용

using namespace std;

Level_Up::Level_Up()
    : _current_level(1), _current_exp(0), _max_exp(100), _stat_points(0)
{
}

Level_Up::~Level_Up()
{
}

void Level_Up::GainExp(Player* player, int amount)
{
    if (player == nullptr) return;

    if (_current_level >= 10)
    {
        cout << "\n[!] 이미 최고 레벨(Lv.10)에 도달하여 더 이상 경험치를 얻을 수 없습니다.\n";
        return;
    }

    _current_exp += amount;
    cout << "  -> 경험치 +" << amount << " 획득! (현재 경험치: " << _current_exp << " / " << _max_exp << ")\n";

    while (_current_exp >= _max_exp && _current_level < 10)
    {
        ProcessLevelUp(player);
    }
}

void Level_Up::ProcessLevelUp(Player* player)
{
    _current_exp -= _max_exp;
    _current_level++;
    _stat_points += 5;

    cout << "\n====================================\n";
    cout << "   ★ LEVEL UP! (Lv." << _current_level - 1 << " -> Lv." << _current_level << ") ★\n";
    cout << "====================================\n";

    int addedHp = _current_level * 20;
    int addedPower = _current_level * 5;

    player->SetMaxHP(player->GetMaxHP() + addedHp);
    player->SetPower(player->GetPower() + addedPower);

    cout << "  -> 레벨업 보너스: 최대 체력 +" << addedHp << " (최대 HP: " << player->GetMaxHP() << ")\n";
    cout << "  -> 레벨업 보너스: 공격력 +" << addedPower << " (공격력: " << player->GetPower() << ")\n";

    player->SetHP(player->GetMaxHP());
    cout << "  -> 체력이 최대치로 회복되었습니다! (현재 HP: " << player->GetHP() << ")\n";

    _max_exp = static_cast<int>(_max_exp * 1.5);

    if (_current_level >= 10)
    {
        _current_exp = 0;
        cout << "   ★ 축하합니다! 최고 레벨(Lv.10)에 도달했습니다! ★\n";
    }
    cout << "====================================\n\n";
}