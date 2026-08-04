#include "Sound_Manager.h"

#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

Sound_Manager::Sound_Manager()
    : currentBGM(BGM_Type::None)
{
}

Sound_Manager& Sound_Manager::Get_Instance()
{
    static Sound_Manager instance;

    return instance;
}

std::wstring Sound_Manager::Get_BGM_Path(
    BGM_Type bgmType) const
{
    switch (bgmType)
    {
    case BGM_Type::Main:
        return L"Sound\\Main.wav";

    case BGM_Type::Battle:
        return L"Sound\\Battle.wav";

    case BGM_Type::Boss:
        return L"Sound\\Boss_BGM.wav";

    default:
        return L"";
    }
}

void Sound_Manager::Play_BGM(BGM_Type bgmType)
{
    // 같은 음악이면 다시 처음부터 재생하지 않음
    if (currentBGM == bgmType)
    {
        return;
    }

    std::wstring path = Get_BGM_Path(bgmType);

    if (path.empty())
    {
        return;
    }

    BOOL result = PlaySoundW(
        path.c_str(),
        nullptr,
        SND_FILENAME |
        SND_ASYNC |
        SND_LOOP |
        SND_NODEFAULT
    );

    if (result == TRUE)
    {
        currentBGM = bgmType;
    }
}

void Sound_Manager::Stop_BGM()
{
    PlaySoundW(nullptr, nullptr, 0);

    currentBGM = BGM_Type::None;
}

BGM_Type Sound_Manager::Get_Current_BGM() const
{
    return currentBGM;
}