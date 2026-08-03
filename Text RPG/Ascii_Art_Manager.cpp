#include "Ascii_Art_Manager.h"
#include <fstream>
#include <iostream>

void Ascii_Art_Manager::Print(const std::string& File_Name) const
{
    std::ifstream file;
    file.open(File_Name);   //파일 열기

    if (!file)  //파일 스트림 상태가 정상적이지 않다면
    {
        std::cout << "파일 열기 실패: " << File_Name << '\n';
        return;
    }

    std::string line;   //한 줄씩 저장
    while (std::getline(file, line))
    {
        std::cout << line << '\n';
    }   //한줄씩 내려가며 읽는 반복문
}