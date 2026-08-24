#include "game.h"

#include <iostream>
#include <limits>
#include <stdexcept>

const Charactere& SelectCharacter(const std::vector<Charactere>& characters, const std::string& characterType)
{
    std::cout << "\033[2J\033[H";

    if (characters.empty())
    {
        throw std::invalid_argument("La liste de personnages est vide.");
    }

    std::cout << "===== Selection : " << characterType << " =====\n\n";

    for (std::size_t index = 0; index < characters.size(); ++index)
    {
        std::cout << '[' << index + 1 << "]\n" << characters[index].displayStats() << "\n\n";
    }

    while (true)
    {
        std::cout << "Choisissez un " << characterType << " (1-" << characters.size() << ") : ";

        std::size_t choice;
        if (std::cin >> choice && choice >= 1 && choice <= characters.size())
        {
            std::cout << '\n';
            return characters[choice - 1];
        }

        if (std::cin.eof())
        {
            throw std::runtime_error("Lecture interrompue.");
        }

        std::cout << "Choix invalide. Reessayez.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void Fight(const Charactere& hero, const Charactere& enemy)
{
    std::cout << "\033[2J\033[H";
    std::cout << "===== Combat =====\n\n" << hero.displayCombatStats(enemy) << '\n';
}
