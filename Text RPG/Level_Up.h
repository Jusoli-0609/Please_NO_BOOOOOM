#pragma once

// [핵심 디자인 패턴] 전방 선언 (Forward Declaration)
// - 헤더 파일 간의 상호 #include로 인한 컴파일 에러(순환 참조)를 방지하기 위해,
//   상세한 내부 정보 없이 "Monster와 Player라는 클래스가 존재한다"는 이름만 미리 알려줍니다.
class Monster;
class Player;

class Level_Up
{
private:
    int _current_level; // 현재 플레이어의 레벨 (기본값: 1)
    int _current_exp;   // 현재 축적된 경험치 (기본값: 0)
    int _max_exp;       // 레벨업에 필요한 목표 경험치 (기본값: 100)
    int _stat_points;   // 레벨업 시 얻는 스탯 포인트 (기본값: 0)

public:
    Level_Up();  // 생성자: 최초 레벨 및 경험치 초기화
    ~Level_Up(); // 소멸자

    // [핵심 기능 1] 레벨업 보상 및 스탯 상승 처리 함수
    // - 플레이어 포인터를 받아 체력, 공격력, HP 풀회복 등을 일괄 적용합니다.
    void ProcessLevelUp(Player* player);

    // [핵심 기능 2] 경험치 획득 및 정산 함수
    // - 외부에서 경험치 수치(amount)를 받아 누적하고, 조건 만족 시 연속 레벨업을 실행합니다.
    void GainExp(Player* player, int amount);

    // [캡슐화 보호] Getter 함수 (const 키워드를 통해 외부에서 데이터를 함부로 수정하지 못하고 조회만 가능하게 보호)
    int GetCurrentExp() const { return _current_exp; } // 현재 경험치 반환
    int GetMaxExp() const { return _max_exp; }       // 목표 경험치 반환
};