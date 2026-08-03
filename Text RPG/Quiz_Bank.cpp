#include "Quiz_Bank.h"

// 전역 문제 은행 실체 정의
std::vector<Quiz> EliteQuiz = {
    { "C++에서 객체를 생성할 때 동적 할당에 사용하는 키워드는?", { "malloc", "new", "alloc", "create" }, 2 },
    { "클래스의 상속을 나타내는 기호는?", { ":", "->", "::", "." }, 1 },
    { "동적 할당된 메모리를 해제할 때 사용하는 키워드는?", { "free", "delete", "remove", "drop" }, 2 },
    { "C++에서 표준 입출력을 다루기 위한 헤더 파일은?", { "<stdio.h>", "<iostream>", "<stdlib.h>", "<string>" }, 2 }
};

std::vector<Quiz> VariableTutorQuiz = {
    { "다음 중 C++ 기본 데이터 타입이 아닌 것은?", { "int", "float", "String", "double" }, 3 },
    { "상수를 선언할 때 사용하는 키워드는?", { "static", "const", "final", "define" }, 2 },
    { "참(true)과 거짓(false)만을 저장하는 자료형은?", { "bool", "char", "int", "short" }, 1 },
    { "C++에서 한 줄 주석을 작성할 때 사용하는 기호는?", { "/*", "//", "#", "--" }, 2 }
};

std::vector<Quiz> ArrayTutorQuiz = {
    { "배열의 첫 번째 요소의 인덱스는?", { "1", "0", "-1", "없음" }, 2 },
    { "int arr[5]; 로 선언된 배열의 마지막 요소 인덱스는?", { "4", "5", "6", "알 수 없음" }, 1 },
    { "for문에서 조건식이 거짓(false)이 되었을 때 일어나는 현상은?", { "반복문 종료", "무한 루프", "에러 발생", "초기화문으로 이동" }, 1 },
    { "반복문의 실행 흐름을 즉시 탈출할 때 사용하는 제어문은?", { "continue", "break", "return", "goto" }, 2 }
};

std::vector<Quiz> FunctionTutorQuiz = {
    { "반환 값이 없는 함수의 반환 타입은?", { "int", "null", "void", "empty" }, 3 },
    { "함수가 실행을 마치고 호출한 곳으로 값을 돌려줄 때 사용하는 키워드는?", { "send", "return", "pass", "yield" }, 2 },
    { "동일한 이름의 함수를 매개변수의 타입이나 개수를 다르게 하여 여러 개 정의하는 것은?", { "오버라이딩", "오버로딩", "캐스팅", "캡슐화" }, 2 },
    { "함수 내부에서 자기 자신을 다시 호출하는 함수는?", { "인라인 함수", "재귀 함수", "람다 함수", "가상 함수" }, 2 }
};

std::vector<Quiz> PointerTutorQuiz = {
    { "포인터가 가리키는 메모리 주소의 값을 가져오는 연산자는?", { "&", "*", "->", "." }, 2 },
    { "변수의 메모리 주소를 구하기 위해 사용하는 연산자는?", { "*", "&", "%", "&&" }, 2 },
    { "아무것도 가리키지 않는 포인터를 안전하게 초기화할 때 사용하는 키워드는?", { "NULL", "0", "nullptr", "void" }, 3 },
    { "포인터를 통해 구조체나 클래스 멤버에 접근할 때 사용하는 연산자는?", { ".", "->", "::", "*" }, 2 }
};

std::vector<Quiz> ObjectTutorQuiz = {
    { "클래스 내부의 멤버 변수에 기본적으로 적용되는 접근 지정자는?", { "public", "protected", "private", "internal" }, 3 },
    { "객체가 생성될 때 자동으로 호출되는 특수한 멤버 함수는?", { "소멸자", "생성자", "캡슐화", "가상함수" }, 2 },
    { "C++ 표준 템플릿 라이브러리에서 가변 길이 배열을 제공하는 컨테이너는?", { "std::list", "std::vector", "std::map", "std::queue" }, 2 },
    { "자식 클래스 외부에는 숨기고, 자식 클래스 내부 접근은 허용하는 접근 지정자는?", { "public", "private", "protected", "friend" }, 3 }
};

// Quiz_Bank.cpp 파일 하단

std::vector<Quiz> KimDongHyunManagerQuiz = {
    { "int arr[3] = {10, 20, 30}; int* p = arr; 일 때, *(p + 1) + arr[2]의 값은?", {"30", "40", "50", "60"}, 3 },
    { "void func(int& a) { a += 10; } 실행 후 int x = 5; func(x); 호출 시 x의 값은?", {"5", "10", "15", "에러 발생"}, 3 },
    { "std::vector<int> v = {1, 2, 3}; v.pop_back(); v.push_back(4); 실행 후 v.size()는?", {"2", "3", "4", "5"}, 2 },
    { "int a = 5, b = 10; bool res = (a > 3 && b++ < 10); 실행 후 b의 값은?", {"9", "10", "11", "12"}, 3 },
    { "C++에서 클래스의 기본 접근 제한자는 무엇인가?", {"public", "private", "protected", "internal"}, 2 }
};

std::vector<Quiz> MoonSeungHoManagerQuiz = {
    { "int a = 10; int* p = &a; int** pp = &p; 일 때 **pp + 5의 값은?", {"15", "a의 주소값", "p의 주소값", "컴파일 에러"}, 1 },
    { "부모 클래스 포인터로 자식 객체 해제 시 메모리 누수를 막기 위한 키워드는?", {"static", "virtual", "override", "const"}, 2 },
    { "int* ptr = new int[5]; 동적 할당 메모리의 올바른 해제 구문은?", {"delete ptr;", "free(ptr);", "delete[] ptr;", "remove(ptr);"}, 3 },
    { "std::map<string, int>에서 존재하지 않는 키에 map[key] 접근 시 현상은?", {"런타임 에러", "NULL 반환", "기본값으로 자동 생성", "컴파일 에러"}, 3 },
    { "64비트 환경에서 double* p; 의 sizeof(p) 크기는 몇 바이트인가?", {"4바이트", "8바이트", "16바이트", "가변적"}, 2 },
    { "객체 생성 없이 클래스에서 직접 호출 가능한 멤버 선언 키워드는?", {"inline", "explicit", "static", "friend"}, 3 }
};