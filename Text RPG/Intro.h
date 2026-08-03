#pragma once

class Console_Manager;     
class Ascii_Art_Manager;    // 전방 선언

class Intro
{
public:
    void Show(Console_Manager& console, Ascii_Art_Manager& art);
};