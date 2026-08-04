#pragma once

#include <string>

enum class BGM_Type
{
    None,
    Main,
    Battle,
    Boss
};

class Sound_Manager
{
private:
    BGM_Type currentBGM;

    Sound_Manager();

    std::wstring Get_BGM_Path(BGM_Type bgmType) const;

public:
    // 복사 방지
    Sound_Manager(const Sound_Manager&) = delete;
    Sound_Manager& operator=(const Sound_Manager&) = delete;

    // 프로그램 전체에서 같은 Sound_Manager 반환
    static Sound_Manager& Get_Instance();

    void Play_BGM(BGM_Type bgmType);
    void Stop_BGM();

    BGM_Type Get_Current_BGM() const;
};