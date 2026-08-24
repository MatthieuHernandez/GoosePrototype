#include "ennemi.h"

#include <random>

Action Ennemi::selectMove()
{
    static std::mt19937 randomGenerator(std::random_device{}());
    static std::uniform_int_distribution<int> moveDistribution(0, 2);

    currentMove = static_cast<Action>(moveDistribution(randomGenerator));
    return currentMove;
}
