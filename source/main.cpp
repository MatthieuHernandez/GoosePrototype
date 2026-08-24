#include <iostream>
#include <vector>

#include "character/goblin.h"
#include "character/mage.h"
#include "character/merfolk.h"
#include "character/rogue.h"
#include "character/warrior.h"
#include "character/werewolf.h"
#include "game.h"

int main()
{
    const std::vector<Charactere> heroes{Warrior{}, Rogue{}, Mage{}};
    const std::vector<Charactere> enemies{Goblin{}, Werewolf{}, Merfolk{}};

    const auto& hero = SelectCharacter(heroes, "Hero");
    const auto& enemy = SelectCharacter(enemies, "Ennemi");

    Fight(hero, enemy);

    return 0;
}
