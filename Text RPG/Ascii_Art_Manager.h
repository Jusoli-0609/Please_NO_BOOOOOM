#pragma once

#include <string>

class Console_Manager;

class Ascii_Art_Manager
{
public:
    void Print(const std::string& file_Name) const;
    void Print_At(Console_Manager& console, const std::string& file_Name,int x,int y) const;
};