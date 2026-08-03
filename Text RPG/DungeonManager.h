#pragma once
#include "Inventory.h"
#include "Monster.h"
#include "Player.h"
#include <string>
#include <map>

// 1. 정예 몬스터 문제 데이터 파트
struct Elite_Question
{
	std::string question;
	std::string choices[4];
	int correct_Answer = 1;
};

// 2. 튜터 문제 및 대사 데이터 파트
struct Tutor_Dialogue
{
	std::string appearance_Message;
	std::string correct_Message;
	std::string wrong_Message;
	std::string exit_Message;
};

struct Tutor_Question
{
	std::string description;
	std::string code;
	std::string correct_Answer;
};

// 3. 몬스터 처치 기록 데이터 파트
struct Monster_Kill_Record
{
	std::string monster_Name;

	Monster_Grade monster_Grade =Monster_Grade::NORMAL;

	int kill_Count = 0;
	int earned_Score = 0;
};

// 4. 던전 공통 상수 파트
constexpr int MONSTERS_PER_CHAPTER = 3;
constexpr int TUTOR_QUESTION_COUNT = 3;
constexpr int TUTOR_CLEAR_CORRECT_COUNT = 2;

class Dungeon_Manager
{
public:
	// 5. 던전 생성 및 메뉴 실행 파트
	Dungeon_Manager(); // 5-1. 던전 매니저 생성자
	void Open_Dungeon(Player* player, Inventory<Item>& inventory); // 5-2. 던전 메뉴 열기

	// 6. 던전 상태 조회 및 기록 출력 파트
	bool Check_All_Chapter_Cleared() const; // 6-1. 전체 챕터 클리어 여부 조회
	int Get_Current_Chapter_Score() const; // 6-2. 현재 챕터 점수 조회
	void Print_Current_Chapter_Kill_Log() const; // 6-3. 현재 챕터 처치 기록 출력
	int Monster_Kill_Count=0; // 6-4. 전체 몬스터 처치 수 호환 변수

private:
	// 7. 현재 챕터 실행 파트
	void Print_Current_Chapter() const; // 7-1. 현재 입장 가능한 챕터 출력
	void Run_Current_Chapter(Player* player, Inventory<Item>& inventory); // 7-2. 현재 챕터 이벤트 진행
	std::string Get_Chapter_Name(Chapter_Type chapter_Type) const; // 7-3. 챕터 이름 변환

	// 8. 일반 몬스터 선택 파트
	void Get_Current_Chapter_Monsters(Monster_Type monster_Types[]) const; // 8-1. 현재 챕터 일반 몬스터 목록 구성
	Monster_Type Get_Random_Normal_Monster() const; // 8-2. 일반 몬스터 랜덤 선택

	// 9. 정예 몬스터 문제 파트
	bool Check_Elite_Monster_Appearance() const; // 9-1. 정예 몬스터 등장 확률 판정
	Elite_Question Get_Elite_Question(Chapter_Type chapter_Type) const; // 9-2. 챕터별 정예 문제 랜덤 선택
	bool Run_Elite_Question(const Elite_Question& elite_Question); // 9-3. 정예 문제 출력 및 정답 판정
	bool Run_Elite_Quiz(Monster& elite_Monster); // 9-4. 정예 몬스터 퀴즈 전체 진행

	// 10. 튜터 문제 및 대사 파트
	void Get_Tutor_Questions(Chapter_Type chapter_Type, Tutor_Question tutor_Questions[]) const; // 10-1. 챕터별 튜터 문제 구성
	Tutor_Dialogue Get_Tutor_Dialogue(Chapter_Type chapter_Type) const; // 10-2. 챕터별 튜터 대사 구성
	bool Run_Tutor_Code_Challenge(const Monster& tutor_Monster); // 10-3. 튜터 코드 문제 3개 진행
	void Run_Tutor_Challenge(Player* player, Inventory<Item>& inventory); // 10-4. 튜터 도전 및 클리어 처리

	// 11. 처치 기록 및 일반 보상 파트
	void Record_Monster_Kill(const Monster& monster); // 11-1. 몬스터 처치 및 클리어 기록 저장
	void Give_Drop_Items_To_Inventory(const Monster& monster, Inventory<Item>& inventory); // 11-2. 드롭 아이템 인벤토리 지급

	// 12. 챕터 점수 및 이동 파트
	void Add_Chapter_Score(int score_Reward); // 12-1. 현재 챕터 점수 추가
	int Get_Required_Tutor_Score() const; // 12-2. 챕터별 튜터 도전 요구 점수 계산
	bool Check_Tutor_Challenge_Available() const; // 12-3. 튜터 도전 가능 여부 확인
	void Clear_Current_Chapter(); // 12-4. 현재 챕터 클리어 처리
	void Move_Next_Chapter(); // 12-5. 다음 챕터 이동

	// 13. 튜터 고유 아이템 및 최종보스방 조건 파트
	Item Create_Tutor_Clear_Item(Chapter_Type chapter_Type) const; // 13-1. 챕터별 튜터 고유 아이템 생성
	bool Has_Item_In_Inventory(Inventory<Item>& inventory, const std::string& item_Name) const; // 13-2. 인벤토리 아이템 보유 여부 확인
	bool Give_Tutor_Clear_Item(Chapter_Type chapter_Type,Inventory<Item>& inventory); // 13-3. 튜터 고유 아이템 확정 지급
	bool Check_Final_Boss_Room_Available(Inventory<Item>& inventory) const; // 13-4. 최종보스방 개방 조건 확인
	void Print_Tutor_Item_Status(Inventory<Item>& inventory) const; // 13-5. 튜터 고유 아이템 수집 현황 출력

	
	// 14. 던전 진행 상태 데이터 파트
	Chapter_Type _current_Chapter;
	bool _is_All_Chapter_Cleared;
	int _current_Chapter_Score;

	// 15. 챕터별 몬스터 처치 기록 데이터 파트
	std::map
	<
		Chapter_Type,
		std::map
		<
		    Monster_Type,
		    Monster_Kill_Record
		>
	> _monster_Kill_Log;
};