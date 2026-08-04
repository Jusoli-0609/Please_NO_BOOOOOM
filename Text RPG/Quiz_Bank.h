#pragma once
#include <string>
#include <vector>

enum class Chapter_Type;

struct Quiz
{
    std::string question;
    std::vector<std::string> choices;
    int answer;
};

struct Tutor_Question
{
    std::string description;
    std::string code;
    std::string correct_Answer;
};

enum class Final_Boss_Question_Type
{
    MULTIPLE_CHOICE,
    SUBJECTIVE
};

struct Final_Boss_Question
{
    Final_Boss_Question_Type type;
    std::string description;
    std::string code;
    std::string choices[4];
    int correct_Choice;
    std::string correct_Answer;
};

extern std::vector<Quiz> Variable_Elite_Quiz;
extern std::vector<Quiz> Array_Elite_Quiz;
extern std::vector<Quiz> Function_Elite_Quiz;
extern std::vector<Quiz> Pointer_Elite_Quiz;
extern std::vector<Quiz> Object_Elite_Quiz;

extern std::vector<Tutor_Question> Variable_Tutor_Quiz;
extern std::vector<Tutor_Question> Array_Tutor_Quiz;
extern std::vector<Tutor_Question> Function_Tutor_Quiz;
extern std::vector<Tutor_Question> Pointer_Tutor_Quiz;
extern std::vector<Tutor_Question> Object_Tutor_Quiz;

extern std::vector<Quiz> EliteQuiz;
extern std::vector<Quiz> VariableTutorQuiz;
extern std::vector<Quiz> ArrayTutorQuiz;
extern std::vector<Quiz> FunctionTutorQuiz;
extern std::vector<Quiz> PointerTutorQuiz;
extern std::vector<Quiz> ObjectTutorQuiz;
extern std::vector<Quiz> KimDongHyunManagerQuiz;
extern std::vector<Quiz> MoonSeungHoManagerQuiz;

const std::vector<Quiz>* Get_Elite_Question_Bank(Chapter_Type chapter_Type);
const std::vector<Tutor_Question>* Get_Tutor_Question_Bank(Chapter_Type chapter_Type);

constexpr int FINAL_BOSS_QUESTION_COUNT = 10;

void Get_Final_Boss_Questions(Final_Boss_Question final_Boss_Questions[]);

std::vector<Final_Boss_Question> Create_Final_Boss_Question_Pool();