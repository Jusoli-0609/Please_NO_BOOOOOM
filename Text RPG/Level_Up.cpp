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
Level_Up::Level_Up()
    : _current_level(1), _current_exp(0), _max_exp(150), _stat_points(0)
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
    if (player == nullptr || amount <= 0)
    {
        return;
    }

    if (_current_level >= 10)
    {
        return;
    }

    _current_exp += amount;

    std::cout
        << "  -> 경험치 +"
        << amount
        << " 획득! (현재 경험치: "
        << _current_exp
        << " / "
        << _max_exp
        << ")\n";

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
    if (player == nullptr) return;

    Console_Manager console;

    _current_exp -= _max_exp;
    _current_level++;
    player->Set_Level(_current_level);
    _stat_points += 3;

    cout << "╔════════════════════════════════════════════════════╗\n";
    string levelUpMsg = "  ★  LEVEL UP! (Lv." + to_string(_current_level - 1) + " -> Lv." + to_string(_current_level) + ") ★\n";
    console.Slow_Print(levelUpMsg, 50);
    cout << "╚════════════════════════════════════════════════════╝\n";

    _stat_points += 3;

    int addedHp = 10;
    int addedMp = 5;
    int addedPower = 2;

    player->Add_Base_MaxHP(addedHp);
    player->Add_Base_MaxMP(addedMp);
    player->Add_Base_ATK(addedPower);
    player->Add_Stat_Points(3);

    cout << "  -> 레벨업 보너스: 최대 체력 +" << addedHp << " (최대 HP: " << player->GetMaxHP() << ")\n";
    cout << "  -> 레벨업 보너스: 최대 MP +" << addedMp  << " (최대 MP: "  << player->GetMaxMP() << ")\n";
    cout << "  -> 레벨업 보너스: 공격력 +" << addedPower << " (공격력: " << player->GetPower() << ")\n";

    player->SetHP(player->GetMaxHP());
    cout << "  -> 체력이 최대치로 회복되었다! (현재 HP: " << player->GetHP() << ")\n";

    _max_exp = static_cast<int>(_max_exp * 1.5);

    // [수정된 부분] 만렙 축하 문구는 Slow_Print로 출력하되, 입력 대기는 밑으로 넘김!
    if (_current_level >= 10)
    {
        _current_exp = 0;
        console.Slow_Print("  ★  축하합니다! 최고 레벨(Lv.10)에 도달했습니다! ★\n", 50);
    }
    cout << "╠════════════════════════════════════════════════════╣\n";

    int messageIndex = _current_level % 3;
    string job = player->Get_Job();

    if (job == "풍둔 주둥아리술 마스터")
    {
        if (messageIndex == 1) cout << "야호!! 블루투스식 레벨업이다! (Enter를 누르세요)";
        else if (messageIndex == 2) cout << "커피 타오십시오! 주둥아리술 상승! (Enter를 누르세요)";
        else cout << "메챠쿠챠 카멜레온! (Enter를 누르세요)";
    }
    else if (job == "소리교 교주")
    {
        if (messageIndex == 1) cout << "찬양단 동원! 레벨이 올랐다! (Enter를 누르세요)";
        else if (messageIndex == 2) cout << "음침하게 염탐하여 신도들을 홀린다! (Enter를 누르세요)";
        else cout << "그림으로 정신공격! 교주의 힘이 강해진다! (Enter를 누르세요)";
    }
    else if (job == "Grand Theif Academy(도둑)")
    {
        if (messageIndex == 1) cout << "너무 정직한 레벨업인가? (Enter를 누르세요)";
        else if (messageIndex == 2) cout << "...제가 레벨업을 한 건가요? (Enter를 누르세요)";
        else cout << "소리 없이 강해졌다! 낚아채기 준비 완료! (Enter를 누르세요)";
    }
    else if (job == "치코리타(반려식물)")
    {
        if (messageIndex == 1) cout << "크와아오앙! 반려식물이 진화한다! (Enter를 누르세요)";
        else if (messageIndex == 2) cout << "식물인 척하며 레벨을 훔쳤다! (Enter를 누르세요)";
        else cout << "식물의 한계를 뛰어넘었다! (Enter를 누르세요)";
    }
    else if (job == "고양이 집사(동물테이머)")
    {
        if (messageIndex == 1) cout << "오 잠시만요 고양이가 레벨업을 도와줬어요! (Enter를 누르세요)";
        else if (messageIndex == 2) cout << "폭풍 성장을 이뤄냈다! (Enter를 누르세요)";
        else cout << "츄르 바르기 버프 발동! 한층 더 강해졌다! (Enter를 누르세요)";
    }
    else if (job == "도둑대장(전사)")
    {
        if (messageIndex == 1) cout << "허허허..., 제가 레벨업을 했습니다. (Enter를 누르세요)";
        else if (messageIndex == 2) cout << "No Signal... 묵묵하게 레벨업을 받아들인다. (Enter를 누르세요)";
        else cout << "대장의 품격으로 든든하게 성장 완료! (Enter를 누르세요)";
    }
    else
    {
        cout << "계속하려면 Enter를 누르세요...";
    }

    cin.ignore();
    cin.get();
}