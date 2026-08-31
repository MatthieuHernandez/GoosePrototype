#include "troll.h"

Troll::Troll()
    : Ennemi("Troll", 140, 0.5f, 15, 10, 1.8f, "Agressif et endurant")
{
}

Action Troll::selectAction()
{
    const int roll = rollPercentage();

    if (previousActionSucceeded)
    {
        if (roll <= 80)
        {
            currentAction = Action::attack;
        }
        else if (roll <= 90)
        {
            currentAction = Action::block;
        }
        else
        {
            currentAction = Action::prepare;
        }
    }
    else
    {
        if (roll <= 40)
        {
            currentAction = Action::attack;
        }
        else if (roll <= 80)
        {
            currentAction = Action::block;
        }
        else
        {
            currentAction = Action::prepare;
        }
    }

    return currentAction;
}
