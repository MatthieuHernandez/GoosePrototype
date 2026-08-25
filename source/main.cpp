#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "character/goblin.h"
#include "character/mage.h"
#include "character/merfolk.h"
#include "character/rogue.h"
#include "character/warrior.h"
#include "character/werewolf.h"
#include "game.h"

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    while (true)
    {
        displayIntro();

        std::vector<Hero> heroes{Warrior{}, Rogue{}, Mage{}};
        std::vector<Ennemi> enemies{Goblin{}, Werewolf{}, Merfolk{}};

        auto& hero = SelectCharacter(heroes, "Héros");
        auto& enemy = SelectCharacter(enemies, "Ennemi");

        Fight(hero, enemy);
        displayResult(hero, enemy);
    }

    return 0;
}
