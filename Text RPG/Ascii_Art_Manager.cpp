#include "Ascii_Art_Manager.h"
#include "Console_Manager.h"

#include <fstream>
#include <iostream>
#include <string>

void Ascii_Art_Manager::Print(const std::string& file_Name) const
{
    std::ifstream file(file_Name);

    if (!file)
    {
        std::cout << "파일 열기 실패: " << file_Name << '\n';
        return;
    }
    //파일을 열지 못한 경우 오류 메시지를 출력

    std::string line;
    //텍스트 파일에서 한 줄씩 읽어올 문자열

    while (std::getline(file, line))
    {
        std::cout << line << '\n';
    }
    //파일의 마지막 줄까지 반복
}

void Ascii_Art_Manager::Print_At(
    Console_Manager& console,
    const std::string& file_Name,int x,int y) const
{
    std::ifstream file(file_Name);
    //입력받은 경로의 텍스트 파일을 엵기

    if (!file)
    {
        console.Print_At(x, y, "파일 열기 실패: " + file_Name);
        return;
    }
    //파일 열기에 실패하면 지정 좌표에 오류를 출력

    std::string line;

    int currentY = y;
    // 첫 번째 줄은 전달받은 y 위치에서 출력

    while (std::getline(file, line))
    {
        console.Print_At(x,currentY,line);
        ++currentY;
    }
    // 한 줄을 출력할 때마다 y좌표를 1씩 증가
}