#include "werewolf.h"

Werewolf::Werewolf()
    : Ennemi("Loup-garou", 130, 0.7f, 10, 10, 2.5f, "Rusé et méthodique")
{
}

Action Werewolf::selectAction()
{
    if (!hasPreviousAction)
    {
        return selectRandomAction();
    }

    const int roll = rollPercentage();

    if (previousActionSucceeded && currentAction == Action::prepare)
    {
        currentAction = roll <= 50 ? Action::prepare : Action::attack;
    }
    else if (!previousActionSucceeded)
    {
        const int actionOffset = roll <= 50 ? 1 : 2;
        currentAction = static_cast<Action>((static_cast<int>(currentAction) + actionOffset) % 3);
    }

    return currentAction;
}
