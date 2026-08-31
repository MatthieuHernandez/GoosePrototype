#include "ennemi.h"

#include <random>

Action Ennemi::selectRandomAction()
{
    static std::mt19937 randomGenerator(std::random_device{}());
    static std::uniform_int_distribution<int> actionDistribution(0, 2);

    currentAction = static_cast<Action>(actionDistribution(randomGenerator));
    return currentAction;
}

int Ennemi::rollPercentage()
{
    static std::mt19937 randomGenerator(std::random_device{}());
    static std::uniform_int_distribution<int> percentage(1, 100);
    return percentage(randomGenerator);
}

void Ennemi::recordActionResult(bool succeeded)
{
    hasPreviousAction = true;
    previousActionSucceeded = succeeded;
}
