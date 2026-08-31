#include "werewolf.h"

#include <random>

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

    static std::mt19937 randomGenerator(std::random_device{}());

    if (previousActionSucceeded && currentAction == Action::prepare)
    {
        static std::uniform_int_distribution<int> prepareOrAttack(0, 1);
        currentAction = prepareOrAttack(randomGenerator) == 0 ? Action::prepare : Action::attack;
    }
    else if (!previousActionSucceeded)
    {
        static std::uniform_int_distribution<int> actionOffset(1, 2);
        currentAction = static_cast<Action>((static_cast<int>(currentAction) + actionOffset(randomGenerator)) % 3);
    }

    return currentAction;
}
