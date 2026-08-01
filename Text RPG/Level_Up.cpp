#include "Level_Up.h"
#include "Player.h"
#include "Monster.h"
#include "Console_Manager.h" // 팀원이 만든 Console_Manager 헤더 포함
#include <iostream>
#include <string>

using namespace std;

// 생성자: 최초 레벨(1), 경험치(0), 목표 경험치(100), 보너스 스탯(0)으로 초기화
Level_Up::Level_Up()
    : _current_level(1), _current_exp(0), _max_exp(100), _stat_points(0)
{
}

Level_Up::~Level_Up()
{
}

// ==========================================
// 경험치 획득 및 정산 함수
// ==========================================
void Level_Up::GainExp(Player* player, const Monster& monster)
{
    // [안전장치 1] 플레이어 포인터가 비어있으면(nullptr) 에러 방지를 위해 즉시 종료
    if (player == nullptr) return;

    // [요구사항 1] 최대 레벨 10 제한 체크
    if (_current_level >= 10)
    {
        // 비정적 멤버 함수 호출을 위해 Console_Manager 객체 생성
        Console_Manager console;
        console.Slow_Print("\n[!] 이미 최고 레벨(Lv.10)에 도달하여 더 이상 경험치를 얻을 수 없습니다.\n", 50);
        return;
    }

    // [핵심 로직] 몬스터의 자체 경험치 보상 함수(getExpReward)를 직접 호출하여 누적
    _current_exp += monster.getExpReward();

    // 수치 및 단순 정보 로그는 답답하지 않게 일반 cout으로 빠른 출력
    cout << "  -> 경험치 +" << monster.getExpReward() << " 획득! (현재 경험치: "
        << _current_exp << " / " << _max_exp << ")\n";

    // [핵심 로직] 경험치가 차오르면 레벨업 실행
    // while문을 사용하여 한 번에 많은 경험치가 들어와도 연속 레벨업이 정상적으로 처리됨
    while (_current_exp >= _max_exp && _current_level < 10)
    {
        ProcessLevelUp(player);
    }
}

// ==========================================
// 실제 레벨업 보상 적용 함수
// ==========================================
void Level_Up::ProcessLevelUp(Player* player)
{
    // [안전장치 2] 플레이어 객체 유효성 검사
    if (player == nullptr) return;

    // Console_Manager 객체 생성
    Console_Manager console;

    // 1. 소모한 목표 경험치만큼 차감 및 레벨/스탯포인트 상승
    _current_exp -= _max_exp;
    _current_level++;
    _stat_points += 5;

    // 레벨업 축하 타이틀 연출 (팀원 요청: 스토리/연출 텍스트이므로 console.Slow_Print 사용)
    cout << "\n====================================\n";
    string levelUpMsg = "  ★ LEVEL UP! (Lv." + to_string(_current_level - 1) + " -> Lv." + to_string(_current_level) + ") ★\n";
    console.Slow_Print(levelUpMsg, 50);
    cout << "====================================\n";

    // [요구사항 2] 레벨 비례 스탯 보상 공식 계산
    int addedHp = _current_level * 20;     // 체력: Lv x 20 상승
    int addedPower = _current_level * 5;   // 공격력: Lv x 5 상승

    // Player 클래스의 캡슐화된 멤버 함수(SetMaxHP, SetPower)를 사용하여 안전하게 스탯 반영
    player->SetMaxHP(player->GetMaxHP() + addedHp);
    player->SetPower(player->GetPower() + addedPower);

    // 수치 상승 정보 로그는 일반 cout 사용
    cout << "  -> 레벨업 보너스: 최대 체력 +" << addedHp << " (최대 HP: " << player->GetMaxHP() << ")\n";
    cout << "  -> 레벨업 보너스: 공격력 +" << addedPower << " (공격력: " << player->GetPower() << ")\n";

    // [요구사항 3] 체력 풀회복 처리
    player->SetHP(player->GetMaxHP());
    cout << "  -> 체력이 최대치로 회복되었습니다! (현재 HP: " << player->GetHP() << ")\n";

    // [게임성 요소] 다음 레벨업에 필요한 요구 경험치를 1.5배 상향
    _max_exp = static_cast<int>(_max_exp * 1.5);

    // [팀 요구사항 ] 10레벨 만렙 달성 시 축하 문구 (연출 문구이므로 console.Slow_Print 사용)
    if (_current_level >= 10)
    {
        _current_exp = 0;
        console.Slow_Print("  ★ 축하합니다! 최고 레벨(Lv.10)에 도달했습니다! ★\n", 50);
    }
    cout << "====================================\n\n";
}