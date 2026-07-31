#pragma once
#include <string>
#include "Inventory.h"
#include "Magician.h"

void CreateCharacter(std::string& name, int stat[]);
void InputHPMP(int stat[]);
void Inputstats(int stat[]);
void PrintStatus(std::string& name, int stat[]);
void ChoiceJob(std::string& name, int stat[], Player*& player);
void Upgrade(std::string&, int stat[], Inventory<Item>&);