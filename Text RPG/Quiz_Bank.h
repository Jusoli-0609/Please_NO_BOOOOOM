#pragma once

#include <string>
#include <vector>


struct Quiz
{
    std::string question;           // 문제 내용
    std::vector<std::string> choices; // 4지선다 보기
    int answer;                     // 정답 번호 (1 ~ 4)
};


extern std::vector<Quiz> EliteQuiz;
extern std::vector<Quiz> VariableTutorQuiz;
extern std::vector<Quiz> ArrayTutorQuiz;
extern std::vector<Quiz> FunctionTutorQuiz;
extern std::vector<Quiz> PointerTutorQuiz;
extern std::vector<Quiz> ObjectTutorQuiz;

extern std::vector<Quiz> KimDongHyunManagerQuiz;
extern std::vector<Quiz> MoonSeungHoManagerQuiz;