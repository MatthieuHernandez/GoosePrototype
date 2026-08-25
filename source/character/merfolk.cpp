#include "merfolk.h"

#include <random>

Merfolk::Merfolk()
    : Ennemi("Sirène", 100, 0.9f, 5, 7, 5.0f, "Patiente et calculatrice")
{
}

Action Merfolk::selectAction()
{
    if (getCurrentPreparation() > 100.0f)
    {
        currentAction = Action::attack;
        return currentAction;
    }

    static std::mt19937 randomGenerator(std::random_device{}());
    static std::uniform_int_distribution<int> percentage(1, 100);
    const int roll = percentage(randomGenerator);

    if (hasPreviousAction && previousActionSucceeded && currentAction == Action::prepare)
    {
        currentAction = roll <= 75 ? Action::attack : Action::prepare;
    }
    else if (hasPreviousAction && previousActionSucceeded && currentAction == Action::block)
    {
        if (roll <= 20)
        {
            currentAction = Action::attack;
        }
        else if (roll <= 40)
        {
            currentAction = Action::prepare;
        }
        else
        {
            currentAction = Action::block;
        }
    }
    else if (roll <= 20)
    {
        currentAction = Action::attack;
    }
    else if (roll <= 60)
    {
        currentAction = Action::prepare;
    }
    else
    {
        currentAction = Action::block;
    }

    return currentAction;
}

void Merfolk::recordActionResult(bool succeeded)
{
    hasPreviousAction = true;
    previousActionSucceeded = succeeded;
}
