#pragma once

// [핵심] 순환 참조 방지 (전방 선언)
// Level_Up.h와 Monster.h가 서로 include하는 꼬임 에러를 막기 위해
// 자세한 내부 정보 없이 "Monster라는 클래스가 존재한다"는 이름만 미리 알려줍니다.
class Monster;
class Player;

class Level_Up
{
private:
    int _current_level; // 현재 플레이어의 레벨
    int _current_exp;   // 현재 축적된 경험치
    int _max_exp;       // 레벨업에 필요한 목표 경험치
    int _stat_points;   // 레벨업 시 얻는 스탯 포인트

public:
    Level_Up();  // 생성자
    ~Level_Up(); // 소멸자

    // [핵심] 경험치 획득 함수
    // 1. const : 몬스터 담당 팀원의 영역(HP, 스탯 등)을 이 함수 내부에서 절대 수정하지 못하게 잠금 (안전성)
    // 2. & (참조자) : 무거운 Monster 객체를 복사하지 않고 원본 주소로 바로 접근하여 속도 최적화 (성능)
   
	// 기존코드 임시 주석 처리
    // void GainExp(Player* player, const Monster& monster);

    // 레벨업 조건 충족 시 실제 능력치 상승 및 HP 회복을 처리하는 함수
    void ProcessLevelUp(Player* player);


	// 밑의 세 줄은 임시로 추가한 외부 경험치 획득용 함수와 Getter
	void GainExp(Player* player, int amount); // 외부에서 직접 경험치를 추가할 수 있는 함수
	int GetCurrentExp() const { return _current_exp; } // 현재 경험치 반환
	int GetMaxExp() const { return _max_exp; } // 목표 경험치 반환
};