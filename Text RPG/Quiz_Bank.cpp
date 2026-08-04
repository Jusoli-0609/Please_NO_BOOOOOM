#include "Quiz_Bank.h"
#include "Monster.h"

#include <vector>

//챕터 1 객관식 문제(정예 몬스터)
std::vector<Quiz> Variable_Elite_Quiz =
{
	{
		"다음 중 정수값을 저장하는 자료형은 무엇인가?",
		{
			"int",
			"bool",
			"if",
			"while"
		},
		1
	},
	{
		"다음 코드에서 출력되는 결과는 무엇인가?\n"
		"int number = 10;\n"
		"if (number > 5)\n"
		"{\n"
		"\tcout << \"통과\";\n"
		"}",
		{
			"아무것도 출력되지 않음",
			"통과",
			"10",
			"오류 발생"
		},
		2
	},
	{
		"참 또는 거짓만 저장할 수 있는 자료형은 무엇인가?",
		{
			"int",
			"string",
			"bool",
			"float"
		},
		3
	}
};
//챕터 2 객관식 문제(정예 몬스터)
std::vector<Quiz> Array_Elite_Quiz =
{
	{
		"다음 배열에서 두 번째 값은 무엇인가?\n"
		"int numbers[3] = { 10, 20, 30 };",
		{
			"10",
			"20",
			"30",
			"3"
		},
		2
	},
	{
		"반복 횟수가 정해져 있을 때 주로 사용하는 반복문은 무엇인가?",
		{
			"if",
			"switch",
			"for",
			"return"
		},
		3
	},
	{
		"다음 반복문은 몇 번 실행되나요?\n"
		"int count = 0;\n"
		"while (count < 3)\n"
		"{\n"
		"\tcount++;\n"
		"}",
		{
			"1번",
			"2번",
			"3번",
			"무한 반복"
		},
		3
	}
};
//챕터 3 객관식 문제(정예 몬스터)
std::vector<Quiz> Function_Elite_Quiz =
{
	{
		"함수에 값을 전달하기 위해 사용하는 것은 무엇인가?",
		{
			"반환값",
			"매개변수",
			"조건문",
			"배열"
		},
		2
	},
	{
		"함수에서 계산한 결과를 돌려줄 때 사용하는 키워드는 무엇인가?",
		{
			"return",
			"break",
			"continue",
			"switch"
		},
		1
	},
	{
		"다음 함수의 반환값은 무엇인가요?\n"
		"int Add(int number_A, int number_B)\n"
		"{\n"
		"\treturn number_A + number_B;\n"
		"}\n"
		"Add(3, 5);",
		{
			"2",
			"3",
			"5",
			"8"
		},
		4
	}
};
//챕터 4 객관식 문제(정예 몬스터)
std::vector<Quiz> Pointer_Elite_Quiz =
{
	{
		"변수의 메모리 주소를 저장하는 변수는 무엇인가?",
		{
			"배열",
			"포인터",
			"함수",
			"반복문"
		},
		2
	},
	{
		"포인터가 아무 주소도 가리키지 않음을 나타내는 값은 무엇인가?",
		{
			"false",
			"zero",
			"nullptr",
			"empty"
		},
		3
	},
	{
		"다음 코드에서 pointer에 저장되는 것은 무엇인가?\n"
		"int number = 10;\n"
		"int* pointer = &number;",
		{
			"number의 값 10",
			"number의 메모리 주소",
			"pointer의 이름",
			"nullptr"
		},
		2
	}
};
//챕터 5 객관식 문제(정예 몬스터)
std::vector<Quiz> Object_Elite_Quiz =
{
	{
		"데이터와 기능을 하나로 묶어 표현하는 문법은 무엇인가?",
		{
			"class",
			"while",
			"return",
			"if"
		},
		1
	},
	{
		"기존 클래스의 기능을 새로운 클래스가 물려받는 것은 무엇인가?",
		{
			"반복",
			"상속",
			"조건",
			"포인터"
		},
		2
	},
	{
		"크기를 자유롭게 늘리거나 줄일 수 있는 STL 컨테이너는 무엇인가?",
		{
			"if",
			"int",
			"vector",
			"return"
		},
		3
	}
};

// 챕터 1 주관식 문제(튜터님)
std::vector<Tutor_Question> Variable_Tutor_Quiz =
{
	{
		"정수를 저장할 자료형을 입력하세요.",
		"____ score = 100;",
		"int"
	},
	{
		"참 또는 거짓을 저장할 자료형을 입력하세요.",
		"____ is_Clear = true;",
		"bool"
	},
	{
		"조건을 검사하는 코드를 입력하세요.",
		"____ (score >= 100)\n"
		"{\n"
		"\tcout << \"입장 가능\";\n"
		"}",
		"if"
	}
};
// 챕터 2 주관식 문제(튜터님)
std::vector<Tutor_Question> Array_Tutor_Quiz =
{
	{
		"여러 값을 순서대로 저장하는 자료구조의 이름을 입력하세요.",
		"int numbers[3] = { 1, 2, 3 };\n"
		"// 위 자료구조의 이름: ____",
		"array"
	},
	{
		"정해진 횟수만큼 반복하는 코드를 입력하세요.",
		"____ (int i = 0; i < 3; i++)\n"
		"{\n"
		"\tcout << i << endl;\n"
		"}",
		"for"
	},
	{
		"조건이 참인 동안 반복하는 코드를 입력하세요.",
		"____ (count < 3)\n"
		"{\n"
		"\tcount++;\n"
		"}",
		"while"
	}
};
// 챕터 3 주관식 문제(튜터님)
std::vector<Tutor_Question> Function_Tutor_Quiz =
{
	{
		"함수로 전달받는 number의 역할을 영어로 입력하세요.",
		"void Print_Number(int number)\n"
		"{\n"
		"\tcout << number;\n"
		"}\n"
		"// number의 역할: ____",
		"parameter"
	},
	{
		"함수의 계산 결과를 반환하는 코드를 입력하세요.",
		"int Add(int number_A, int number_B)\n"
		"{\n"
		"\t____ number_A + number_B;\n"
		"}",
		"return"
	},
	{
		"Add와 같이 특정 기능을 묶은 코드 단위를 영어로 입력하세요.",
		"int Add(int number_A, int number_B)\n"
		"{\n"
		"\treturn number_A + number_B;\n"
		"}\n"
		"// 위 코드 단위: ____",
		"function"
	}
};
// 챕터 4 주관식 문제(튜터님)
std::vector<Tutor_Question> Pointer_Tutor_Quiz =
{
	{
		"메모리 주소를 저장하는 변수의 종류를 영어로 입력하세요.",
		"int value = 10;\n"
		"int* value_Pointer = &value;\n"
		"// value_Pointer의 종류: ____",
		"pointer"
	},
	{
	    "포인터가 아무 주소도 가리키지 않도록 초기화하는 키워드를 입력하세요.",
	    "int* value_Pointer = ____;",
	    "nullptr"
    },
	{
		"변수의 값이 저장되는 공간을 영어로 입력하세요.",
		"int value = 10;\n"
		"// value가 저장되는 공간: ____",
		"memory"
	}
};
// 챕터 5 주관식 문제(튜터님)
std::vector<Tutor_Question> Object_Tutor_Quiz =
{
	{
		"객체를 만들기 위한 설계도를 선언하는 코드를 입력하세요.",
		"____ Player\n"
		"{\n"
		"public:\n"
		"\tint hp;\n"
		"};",
		"class"
	},
	{
		"부모 클래스의 기능을 자식 클래스가 물려받는 관계를 영어로 입력하세요.",
		"class Child : public Parent\n"
		"{\n"
		"};\n"
		"// 위 클래스 관계: ____",
		"inheritance"
	},
	{
		"크기가 동적으로 변하는 STL 컨테이너를 입력하세요.",
		"____<int> numbers;\n"
		"numbers.push_back(10);",
		"vector"
	}
};

void Get_Final_Boss_Questions(Final_Boss_Question final_Boss_Questions[])
{
	//1. 변수·조건문 객관식(최종보스)
	final_Boss_Questions[0].type = Final_Boss_Question_Type::MULTIPLE_CHOICE;
	final_Boss_Questions[0].description = "다음 코드의 출력 결과는 무엇인가?";
	final_Boss_Questions[0].code =
		"int score = 85;\n"
		"\n"
		"if (score >= 90)\n"
		"{\n"
		"\tcout << \"A\";\n"
		"}\n"
		"else\n"
		"{\n"
		"\tcout << \"B\";\n"
		"}";
	final_Boss_Questions[0].choices[0] = "A";
	final_Boss_Questions[0].choices[1] = "B";
	final_Boss_Questions[0].choices[2] = "85";
	final_Boss_Questions[0].choices[3] = "아무것도 출력되지 않음";
	final_Boss_Questions[0].correct_Choice = 2;
	final_Boss_Questions[0].correct_Answer = "";

	//2. 변수·조건문 주관식(최종보스)
	final_Boss_Questions[1].type = Final_Boss_Question_Type::SUBJECTIVE;
	final_Boss_Questions[1].description = "두 조건이 모두 참인지 검사하는 연산자를 입력하세요.";
	final_Boss_Questions[1].code =
		"if (hp > 0 ____ mp > 0)\n"
		"{\n"
		"\tcout << \"전투 가능\";\n"
		"}";
	final_Boss_Questions[1].correct_Choice = 0;
	final_Boss_Questions[1].correct_Answer = "&&";

	//3. 배열·반복문 객관식(최종보스)
	final_Boss_Questions[2].type = Final_Boss_Question_Type::MULTIPLE_CHOICE;
	final_Boss_Questions[2].description = "다음 코드의 출력 결과는 무엇인가?";
	final_Boss_Questions[2].code =
		"int numbers[3] = { 2, 4, 6 };\n"
		"int total = 0;\n"
		"\n"
		"for (int i = 0; i < 3; i++)\n"
		"{\n"
		"\ttotal += numbers[i];\n"
		"}\n"
		"\n"
		"cout << total;";

	final_Boss_Questions[2].choices[0] = "6";
	final_Boss_Questions[2].choices[1] = "8";
	final_Boss_Questions[2].choices[2] = "10";
	final_Boss_Questions[2].choices[3] = "12";
	final_Boss_Questions[2].correct_Choice = 4;
	final_Boss_Questions[2].correct_Answer = "";

	//4. 배열·반복문 주관식(최종보스)
	final_Boss_Questions[3].type = Final_Boss_Question_Type::SUBJECTIVE;
	final_Boss_Questions[3].description = "현재 반복만 건너뛰고 다음 반복으로 이동하는 키워드를 입력하세요.";
	final_Boss_Questions[3].code =
		"for (int i = 0; i < 5; i++)\n"
		"{\n"
		"\tif (i == 2)\n"
		"\t{\n"
		"\t\t____;\n"
		"\t}\n"
		"\n"
		"\tcout << i << endl;\n"
		"}";

	final_Boss_Questions[3].correct_Choice = 0;
	final_Boss_Questions[3].correct_Answer = "continue";

	//5. 함수 객관식(최종보스)
	final_Boss_Questions[4].type = Final_Boss_Question_Type::MULTIPLE_CHOICE;
	final_Boss_Questions[4].description = "다음 코드의 출력 결과는 무엇인가?";
	final_Boss_Questions[4].code =
		"int Multiply(int number_A, int number_B)\n"
		"{\n"
		"\treturn number_A * number_B;\n"
		"}\n"
		"\n"
		"cout << Multiply(3, 4);";

	final_Boss_Questions[4].choices[0] = "3";
	final_Boss_Questions[4].choices[1] = "4";
	final_Boss_Questions[4].choices[2] = "7";
	final_Boss_Questions[4].choices[3] = "12";
	final_Boss_Questions[4].correct_Choice = 4;
	final_Boss_Questions[4].correct_Answer = "";

	//6. 함수 주관식(최종보스)
	final_Boss_Questions[5].type = Final_Boss_Question_Type::SUBJECTIVE;
	final_Boss_Questions[5].description = "반환값이 없는 함수의 반환 자료형을 입력하세요.";
	final_Boss_Questions[5].code =
		"____ Print_Message()\n"
		"{\n"
		"\tcout << \"최종 보스 등장\";\n"
		"}";

	final_Boss_Questions[5].correct_Choice = 0;
	final_Boss_Questions[5].correct_Answer = "void";

	//7. 포인터·메모리 객관식(최종보스)
	final_Boss_Questions[6].type = Final_Boss_Question_Type::MULTIPLE_CHOICE;
	final_Boss_Questions[6].description = "다음 코드의 출력 결과는 무엇인가?";
	final_Boss_Questions[6].code =
		"int value = 5;\n"
		"int* value_Pointer = &value;\n"
		"\n"
		"*value_Pointer = 20;\n"
		"\n"
		"cout << value;";
	final_Boss_Questions[6].choices[0] = "5";
	final_Boss_Questions[6].choices[1] = "10";
	final_Boss_Questions[6].choices[2] = "20";
	final_Boss_Questions[6].choices[3] = "메모리 주소";
	final_Boss_Questions[6].correct_Choice = 3;
	final_Boss_Questions[6].correct_Answer = "";

	//8. 포인터·메모리 주관식(최종보스)
	final_Boss_Questions[7].type = Final_Boss_Question_Type::SUBJECTIVE;
	final_Boss_Questions[7].description = "변수의 메모리 주소를 가져오는 연산자를 입력하세요.";
	final_Boss_Questions[7].code =
		"int value = 10;\n"
		"int* value_Pointer = ____value;";
	final_Boss_Questions[7].correct_Choice = 0;
	final_Boss_Questions[7].correct_Answer = "&";

	//9. 객체지향·STL 객관식(최종보스)
	final_Boss_Questions[8].type = Final_Boss_Question_Type::MULTIPLE_CHOICE;
	final_Boss_Questions[8].description = "다음 코드의 출력 결과는 무엇인가?";
	final_Boss_Questions[8].code =
		"vector<int> numbers = { 10, 20 };\n"
		"\n"
		"numbers.push_back(30);\n"
		"\n"
		"cout << numbers.size();";

	final_Boss_Questions[8].choices[0] = "1";
	final_Boss_Questions[8].choices[1] = "2";
	final_Boss_Questions[8].choices[2] = "3";
	final_Boss_Questions[8].choices[3] = "30";
	final_Boss_Questions[8].correct_Choice = 3;
	final_Boss_Questions[8].correct_Answer = "";

	//10. 객체지향·STL 주관식(최종보스)
	final_Boss_Questions[9].type = Final_Boss_Question_Type::SUBJECTIVE;
	final_Boss_Questions[9].description = "Player를 공개 상속받기 위해 빈칸에 들어갈 키워드를 입력하세요.";
	final_Boss_Questions[9].code =
		"class Warrior : ____ Player\n"
		"{\n"
		"public:\n"
		"\tvoid Attack();\n"
		"};";
	final_Boss_Questions[9].correct_Choice = 0;
	final_Boss_Questions[9].correct_Answer = "public";
}

std::vector<Final_Boss_Question> Create_Final_Boss_Question_Pool()
{
	std::vector<Final_Boss_Question> question_Pool(FINAL_BOSS_QUESTION_COUNT);

	Get_Final_Boss_Questions(question_Pool.data());

	return question_Pool;
}

std::vector<Quiz> VariableTutorQuiz ={};
std::vector<Quiz> ArrayTutorQuiz ={};
std::vector<Quiz> FunctionTutorQuiz ={};
std::vector<Quiz> PointerTutorQuiz ={};
std::vector<Quiz> ObjectTutorQuiz ={};
std::vector<Quiz> KimDongHyunManagerQuiz ={};
std::vector<Quiz> MoonSeungHoManagerQuiz ={};

const std::vector<Quiz>* Get_Elite_Question_Bank(Chapter_Type chapter_Type)
{
	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
		return &Variable_Elite_Quiz;

	case Chapter_Type::ARRAY_LOOP_OCEAN:
		return &Array_Elite_Quiz;

	case Chapter_Type::FUNCTION_RUINS:
		return &Function_Elite_Quiz;

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
		return &Pointer_Elite_Quiz;

	case Chapter_Type::OBJECT_STL_FACTORY:
		return &Object_Elite_Quiz;

	default:
		return nullptr;
	}
}

const std::vector<Tutor_Question>* Get_Tutor_Question_Bank(Chapter_Type chapter_Type)
{
	switch (chapter_Type)
	{
	case Chapter_Type::VARIABLE_CONDITION_FOREST:
		return &Variable_Tutor_Quiz;

	case Chapter_Type::ARRAY_LOOP_OCEAN:
		return &Array_Tutor_Quiz;

	case Chapter_Type::FUNCTION_RUINS:
		return &Function_Tutor_Quiz;

	case Chapter_Type::POINTER_MEMORY_GRAVEYARD:
		return &Pointer_Tutor_Quiz;

	case Chapter_Type::OBJECT_STL_FACTORY:
		return &Object_Tutor_Quiz;

	default:
		return nullptr;
	}
}