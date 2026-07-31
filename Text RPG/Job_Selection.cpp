#include <string>
#include <iostream>

#include "Player.h"
#include "Monster.h"
#include "Level_Up.h"
#include "JYJ.h"
#include "Job_Selection.h"

using namespace std;

Player* Job_Selection(const string& name, int stat[])
{
    int jobChoice = 0;

    while (true)
    {
        cout << "조원을 선택해주세요.\n";
        cout << "1. JYJ\n";
        cout << "선택: ";
        cin >> jobChoice;

        switch (jobChoice)
        {
        case 1:
            return new JYJ(name, stat);

        default:
            cout << "올바른 번호를 입력해주세요.\n\n";
            break;
        }
    }
}