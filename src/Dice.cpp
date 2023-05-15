#include <random>
#include "Dice.h"

static std::random_device rd;
static std::mt19937 eng(rd());
static std::uniform_int_distribution<> d4(1,4);
static std::uniform_int_distribution<> d6(1,6);
static std::uniform_int_distribution<> d8(1,8);
static std::uniform_int_distribution<> d10(1,10);
static std::uniform_int_distribution<> d12(1,12);
static std::uniform_int_distribution<> d20(1,20);
static std::uniform_int_distribution<> d100(1,100);

int Dice::RollDice(int sides)
{
    switch (sides)
    {
    case 4:
        return d4(eng);
        break;
    case 6:
        return d6(eng);
        break;
    case 8:
        return d8(eng);
        break;
    case 10:
        return d10(eng);
        break;
    case 12:
        return d12(eng);
        break;
    case 20:
        return d20(eng);
        break;
    case 100:
        return d100(eng);
        break;    
    default:
        std::uniform_int_distribution<> dist(1,sides);
        return dist(eng);
        break;
    }
}