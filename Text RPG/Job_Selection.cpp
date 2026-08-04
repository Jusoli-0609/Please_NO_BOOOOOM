#include <string>
#include <iostream>
#include "Job_Selection.h"

int Job_Selection()
{
    int jobChoice = 0;

    std::cout << "직업을 선택해주세요.\n";
    std::cout << "1. JYJ\n";
    std::cout << "2. JSR\n";
    std::cout << "3. JWH\n";
    std::cout << "4. LYB\n";
    std::cout << "5. LMR\n";
    std::cout << "6. PSB\n";
    std::cout << "선택: ";
    std::cin >> jobChoice;

    return jobChoice;
}