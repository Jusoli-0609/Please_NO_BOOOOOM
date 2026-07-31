#include "PotionRecipe.h"
#include <iostream>

using namespace std;

void PotionRecipe::PrintInfo() const
{
    cout << potionName << ": "
        << ingredient1Name << " x" << ingredient1Count << ", "
        << ingredient2Name << " x" << ingredient2Count
        << endl;
}