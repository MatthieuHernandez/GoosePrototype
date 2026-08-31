#include <memory>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

#include "character/goblin.h"
#include "character/mage.h"
#include "character/merfolk.h"
#include "character/rogue.h"
#include "character/troll.h"
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

        std::vector<std::unique_ptr<Hero>> heroes;
        heroes.emplace_back(std::make_unique<Warrior>());
        heroes.emplace_back(std::make_unique<Rogue>());
        heroes.emplace_back(std::make_unique<Mage>());
        std::vector<std::unique_ptr<Ennemi>> enemies;
        enemies.emplace_back(std::make_unique<Goblin>());
        enemies.emplace_back(std::make_unique<Werewolf>());
        enemies.emplace_back(std::make_unique<Merfolk>());
        enemies.emplace_back(std::make_unique<Troll>());

        auto& hero = SelectCharacter(heroes, "Héros");
        auto& enemy = SelectCharacter(enemies, "Ennemi");

        Fight(hero, enemy);
        displayResult(hero, enemy);
    }

    return 0;
}
