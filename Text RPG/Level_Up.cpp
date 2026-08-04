#include "Level_Up.h"
#include "Player.h"
#include "Monster.h"
#include "Console_Manager.h" // 팀원이 만든 Console_Manager 헤더 포함
#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 생성자: 최초 레벨 및 경험치 초기화
// ==========================================
// - 게임 시작 시 플레이어의 초기 레벨은 1, 현재 경험치는 0으로 세팅합니다.
// - 첫 레벨업에 필요한 목표 경험치는 100, 기본 스탯 포인트는 0으로 초기화합니다.
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
void Level_Up::GainExp(Player* player, int amount)
{
    // [안전장치 1] 플레이어 주소가 유효하지 않거나(nullptr), 획득하려는 경험치가 0 이하면 즉시 종료 (크래시 방지)
    if (player == nullptr || amount <= 0)
    {
        return;
    }

    // [요구사항 1] 최대 레벨 10 제한 체크 (이미 만렙이면 경험치를 더 이상 얻지 못함)
    if (_current_level >= 10)
    {
        return;
    }

    // 전달받은 경험치 양만큼 현재 경험치 누적
    _current_exp += amount;

    // 획득 현황을 일반 cout으로 빠르게 출력
    std::cout
        << "  -> 경험치 +"
        << amount
        << " 획득! (현재 경험치: "
        << _current_exp
        << " / "
        << _max_exp
        << ")\n";

    // [핵심 로직] while 문을 통한 연속 레벨업 처리
    // - 한 번에 엄청난 양의 경험치를 얻어 목표치(_max_exp)를 초과할 경우,
    //   단순 if문과 달리 while문을 사용하여 레벨이 1씩 안전하게 연속으로 오르도록 처리합니다.
    while (_current_exp >= _max_exp &&
        _current_level < 10)
    {
        ProcessLevelUp(player);
    }
}


// ==========================================
// 실제 레벨업 보상 적용 함수
// ==========================================
void Level_Up::ProcessLevelUp(Player* player)
{
    // [안전장치 2] 레벨업 도중 플레이어 객체 유효성 검사 (널 포인터 역참조 방지)
    if (player == nullptr) return;

    // 타이틀 연출 텍스트 출력을 위한 Console_Manager 객체 생성
    Console_Manager console;

    // 1. 레벨업 실행: 소모한 목표 경험치 차감 및 레벨 1 상승, 스탯 포인트 5 지급
    _current_exp -= _max_exp;
    _current_level++;
    player->Set_Level(_current_level);
    _stat_points += 5;

    // 2. 레벨업 축하 타이틀 연출 (Slow_Print 함수를 이용해 타자기처럼 출력)
    cout << "\n====================================\n";
    string levelUpMsg = "  ★ LEVEL UP! (Lv." + to_string(_current_level - 1) + " -> Lv." + to_string(_current_level) + ") ★\n";
    console.Slow_Print(levelUpMsg, 50);
    cout << "====================================\n";

    // 3. [요구사항 2] 레벨 비례 스탯 보상 공식 계산
    // - 체력: 현재 레벨 × 20 상승 / 공격력: 현재 레벨 × 5 상승
    int addedHp = _current_level * 20;
    int addedPower = _current_level * 5;

    player->Add_Base_MaxHP(addedHp);
    player->Add_Base_ATK(addedPower);

    // 상승된 스탯 수치 로그 출력
    cout << "  -> 레벨업 보너스: 최대 체력 +" << addedHp << " (최대 HP: " << player->GetMaxHP() << ")\n";
    cout << "  -> 레벨업 보너스: 공격력 +" << addedPower << " (공격력: " << player->GetPower() << ")\n";

    // 4. [요구사항 3] 체력 풀회복 처리
    // - 레벨업 보상으로 플레이어의 현재 체력을 늘어난 최대 체력 크기만큼 가득 채워줍니다.
    player->SetHP(player->GetMaxHP());
    cout << "  -> 체력이 최대치로 회복되었습니다! (현재 HP: " << player->GetHP() << ")\n";

    // 5. 게임성 요소: 다음 레벨업에 필요한 요구 경험치를 1.5배 상향하여 난이도 곡선 조절
    _max_exp = static_cast<int>(_max_exp * 1.5);

    // 6. [팀 요구사항] 10레벨 만렙 달성 시 축하 연출 문구 출력
    if (_current_level >= 10)
    {
        _current_exp = 0; // 만렙 도달 시 초과 경험치는 0으로 고정
        console.Slow_Print("  ★ 축하합니다! 최고 레벨(Lv.10)에 도달했습니다! ★\n", 50);
    }
    cout << "====================================\n\n";

    // [추가된 부분] 레벨에 따라 대사가 3가지로 다채롭게 바뀌는 일시정지 처리
    int messageIndex = _current_level % 3;

    if (messageIndex == 1)
    {
        cout << "야호!! 신난다! 다음으로 넘어가자! (Enter를 누르세요)";
    }
    else if (messageIndex == 2)
    {
        cout << "한층 성장한 느낌이다! (Enter를 누르세요)";
    }
    else
    {
        cout << "스파르타!! 이 기세로 달려간다! (Enter를 누르세요)";
    }

    cin.ignore();
    cin.get();
}