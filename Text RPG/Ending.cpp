#include "Ending.h"

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void Ending::Wait() const
{
    this_thread::sleep_for(chrono::milliseconds(1800));
}

void Ending::Print_Ending() const
{
    system("cls");

    cout << "=====================================================\n";
    cout << "                 FINAL CLEAR!!\n";
    cout << "=====================================================\n\n";

    Wait();

    Print_Story();

    Wait();

    Print_Funny_Ending();

    Wait();

    Print_Credit();
}

void Ending::Print_Story() const
{
    cout << "코드 던전의 마지막 보스를 쓰러뜨렸다...\n\n";
    Wait();

    cout << "캠프를 뒤덮고 있던 버그와 오류들이 하나둘 사라지기 시작했다.\n";
    Wait();

    cout << "무너져 있던 코드가 정리되고,\n";
    Wait();

    cout << "끝없이 이어지던 컴파일 에러도 더 이상 나타나지 않았다.\n\n";
    Wait();

    cout << "잠시 후...\n\n";
    Wait();

    cout << "눈앞의 풍경이 서서히 변하기 시작했다.\n";
    Wait();

    cout << "코드 던전은 사라지고,\n";
    Wait();

    cout << "원래의 내일배움캠프로 돌아오게 되었다.\n\n";
    Wait();

    cout << "\"처음에는 코드가 너무 낯설고...\"\n";
    Wait();

    cout << "\"컴파일 에러 하나에도 막막했었다.\"\n\n";
    Wait();

    cout << "\"하지만 수많은 오류를 해결하고,\n";
    cout << "던전을 탐험하면서 이제는 코드를 읽고,\n";
    cout << "직접 수정할 수 있게 되었다.\"\n\n";
    Wait();

    cout << "당신은 이제...\n";
    Wait();

    cout << "『진정한 내일배움캠프 수료생』이 되었다.\n\n";
}

void Ending::Print_Funny_Ending() const
{
    cout << "-----------------------------------------------------\n";
    cout << "                Hidden Memory...\n";
    cout << "-----------------------------------------------------\n\n";

    Wait();

    cout << "...\n";
    Wait();

    cout << "...\n";
    Wait();

    cout << "...\n\n";
    Wait();

    cout << "코드카타 시간\n\n";
    Wait();

    cout << "(-_-) Zzz...\n\n";
    Wait();

    cout << "??? : 000님??\n";
    Wait();

    cout << "??? : 계신가요??\n";
    Wait();

    cout << "??? : 안 계시면 부정출결 처리하겠습니다.\n\n";
    Wait();

    cout << "...\n";
    Wait();

    cout << "...\n\n";
    Wait();

    cout << "부정출결 누적으로 제적당했습니다.\n\n";
    Wait();

    cout << "GAME OVER\n\n";
}

void Ending::Print_Credit() const
{
    system("cls");

    cout << "=====================================================\n";
    cout << "                    END CREDIT\n";
    cout << "=====================================================\n\n";

    Wait();

    cout << "Team Please_NO_BOOOOOM\n\n";

    Wait();

    cout << "박성빈\n";
    cout << " - 전투 시스템\n";
    cout << " - 던전 시스템\n";
    cout << " - 팀장\n\n";

    Wait();

    cout << "정윤재\n";
    cout << " - 상점 시스템\n";
    cout << " - 인벤토리 시스템\n";
    cout << " - 부팀장\n\n";

    Wait();

    cout << "이미르\n";
    cout << " - 던전 시스템\n";
    cout << " - 몬스터\n\n";

    Wait();

    cout << "이영빈\n";
    cout << " - 플레이어 스탯\n";
    cout << " - 동료 및 버프 시스템\n\n";

    Wait();

    cout << "주소리\n";
    cout << " - 게임 로그\n";
    cout << " - Git 매니저\n\n";

    Wait();

    cout << "장우혁\n";
    cout << " - 레벨업 시스템\n";
    cout << " - 몬스터 담당\n\n";

    Wait();

    cout << "=====================================================\n";
    cout << "             THANK YOU FOR PLAYING\n";
    cout << "=====================================================\n";
    system("cls");

    cout << R"(
                                  __                              _    __           
 /  |                     /      /              /                /|   /  | /    /   
(   | ___  ___  ___  ___ (      (___  ___  ___    ___  ___      ( |  (   |(___ (___ 
|   )|   )|   )|___)|   )|      |    |   )|   )| |   )|___)       | )|   )|    |   )
|__/ |  / |    |__  |__/||      |__  |  / |__/ | |  / |__        _|/ |__/ |__  |  / 
                                          __/                                       
  ___                                                                               
 /    /      /    /    /            /                                               
(___    ___ (___ (___    ___  ___  (                                                
|    | |   )|   )|    | |   )|   ) |                                                
|    | |__/ |  / |__  | |  / |__/  _                                                
       __/                   __/                                                    
                 THANK YOU FOR PLAYING

)";

    Wait();
}