#include "hero.h"

#include <cmath>

#include "ennemi.h"

void Hero::selectMove(Action action) { this->currentAction = action; }

std::string Hero::displayAction(const Ennemi& enemy) const
{
    const auto actionToVerb = [](Action action) -> std::string
    {
        switch (action)
        {
            case Action::attack:
                return "attaque";
            case Action::block:
                return "bloque";
            case Action::prepare:
                return "prépare";
        }
        return "ne fait rien";
    };

    return getName() + " " + actionToVerb(getCurrentAction()) + ", " + enemy.getName() + " " +
           actionToVerb(enemy.getCurrentAction()) + ".";
}

void Hero::resolveAction(Ennemi& enemy)
{
    const auto resolveAttack = [&](Charactere& attacker, Charactere& defender)
    {
        const int attackDamage =
            static_cast<int>(std::ceil(attacker.getAttack() * attacker.getCurrentPreparation()));

        if (defender.getCurrentAction() == Action::block)
        {
            const int reducedDamage =
                static_cast<int>(std::ceil(attackDamage * (1.0f - defender.getBlockage())));
            defender.receiveDamage(reducedDamage);
            attacker.resetPreparation();
            attacker.receiveDamage(defender.getCounterattack());
        }
        else
        {
            defender.receiveDamage(attackDamage);
            attacker.resetPreparation();
        }
    };

    if (getCurrentAction() == Action::attack && enemy.getCurrentAction() == Action::attack)
    {
        const int heroDamage =
            static_cast<int>(std::ceil(enemy.getAttack() * enemy.getCurrentPreparation()));
        const int enemyDamage = static_cast<int>(std::ceil(getAttack() * getCurrentPreparation()));
        receiveDamage(heroDamage);
        enemy.receiveDamage(enemyDamage);
        return;
    }

    if (getCurrentAction() == Action::attack)
    {
        resolveAttack(*this, enemy);
        return;
    }

    if (enemy.getCurrentAction() == Action::attack)
    {
        resolveAttack(enemy, *this);
        return;
    }

    if (getCurrentAction() == Action::prepare)
    {
        increasePreparation();
    }

    if (enemy.getCurrentAction() == Action::prepare)
    {
        enemy.increasePreparation();
    }
}
