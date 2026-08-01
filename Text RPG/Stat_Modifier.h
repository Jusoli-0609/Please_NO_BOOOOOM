#pragma once
#include <string>

// 스탯의 고정 증감값
struct Stat_Value
{
    int maxHp = 0;
    int maxMp = 0;

    int atk = 0;
    int def = 0;
    int ap = 0;
    int sne = 0;
    int agi = 0;
};

// 스탯의 비율 증감값
// 0.10f = 10% 증가
// -0.10f = 10% 감소
struct Stat_Rate
{
    float maxHp = 0.0f;
    float maxMp = 0.0f;

    float atk = 0.0f;
    float def = 0.0f;
    float ap = 0.0f;
    float sne = 0.0f;
    float agi = 0.0f;
};

enum class Stat_Modifier_Type
{
    Equipment,  // 일반 장비
    Tutor,      // 튜터 장착 효과
    Buff,       // 일시적인 버프
    Debuff      // 일시적인 디버프
};

// 플레이어에게 적용되는 효과 하나
struct Stat_Modifier
{
    // 효과를 구별하기 위한 고유 ID
    // 같은 ID가 다시 들어오면 기존 효과를 갱신한다.
    std::string id;

    std::string name;

    Stat_Modifier_Type type = Stat_Modifier_Type::Buff;

    // 고정 증감값
    Stat_Value flat;

    // 퍼센트 증감값
    Stat_Rate rate;

    // -1: 영구 지속
    //  1 이상: 남은 턴
    int remainingTurns = -1;
};