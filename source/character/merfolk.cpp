#include "merfolk.h"

Merfolk::Merfolk()
    : Ennemi("Sirène", 110, 0.9f, 5, 14, 5.0f, "Patiente et calculatrice")
{
}

Action Merfolk::selectAction()
{
    if (getCurrentPreparation() > 100.0f)
    {
        currentAction = Action::attack;
        return currentAction;
    }

    const int roll = rollPercentage();

    if (hasPreviousAction && previousActionSucceeded && currentAction == Action::prepare)
    {
        currentAction = roll <= 75 ? Action::attack : Action::prepare;
    }
    else if (hasPreviousAction && previousActionSucceeded && currentAction == Action::block)
    {
        if (roll <= 10)
        {
            currentAction = Action::attack;
        }
        else if (roll <= 30)
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
