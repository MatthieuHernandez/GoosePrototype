#include "ennemi.h"

#include <random>

Action Ennemi::selectRandomAction()
{
    static std::mt19937 randomGenerator(std::random_device{}());
    static std::uniform_int_distribution<int> actionDistribution(0, 2);

    currentAction = static_cast<Action>(actionDistribution(randomGenerator));
    return currentAction;
}

void Ennemi::recordActionResult(bool succeeded) { (void)succeeded; }
