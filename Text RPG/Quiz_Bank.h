#pragma once

#include <string>
#include <vector>

//======================================================
// Quiz 구조체 정의 (중복 선언 방지 및 완전한 타입 정의)
//======================================================
struct Quiz
{
    std::string question;           // 문제 내용
    std::vector<std::string> choices; // 4지선다 보기
    int answer;                     // 정답 번호 (1 ~ 4)
};

//======================================================
// 문제 은행 전역 변수 (extern 선언)
//======================================================
extern std::vector<Quiz> EliteQuiz;
extern std::vector<Quiz> VariableTutorQuiz;
extern std::vector<Quiz> ArrayTutorQuiz;
extern std::vector<Quiz> FunctionTutorQuiz;
extern std::vector<Quiz> PointerTutorQuiz;
extern std::vector<Quiz> ObjectTutorQuiz;