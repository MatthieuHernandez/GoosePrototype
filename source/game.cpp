#include "game.h"

#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>

#ifdef _WIN32
#include <conio.h>
#endif

void displayIntro()
{
    std::cout << "\033[2J\033[H"
              << "=====================================\n"
              << "========== Goose Prototype ==========\n"
              << "=====================================\n\n"
              << "Ce prototype a été développé pour tester un nouveau système de combat pour un futur jeu.\n"
              << "Le combat fonctionne un peu comme un jeu de pierre-feuille-ciseaux :\n\n"
              << "- Attaquer inflige des dégâts et annule la préparation.\n"
              << "- Bloquer réduit les dégâts d'une attaque et permet de contre-attaquer.\n"
              << "- Préparer augmente la puissance de la prochaine attaque (cumulable).\n"
              << "- 3 classes sont disponibles : Guerrier, Voleur et Mage.\n"
              << "- 4 ennemis au comportement unique sont affrontables.\n\n\n"
              << "Appuyez sur n'importe quelle touche pour continuer." << std::flush;

#ifdef _WIN32
    _getch();
#else
    std::cin.get();
#endif
}

template <typename CharacterType>
CharacterType& SelectCharacterFrom(std::vector<std::unique_ptr<CharacterType>>& characters,
                                   const std::string& characterType)
{
    std::cout << "\033[2J\033[H";

    if (characters.empty())
    {
        throw std::invalid_argument("La liste de personnages est vide.");
    }

    std::cout << "===== Sélection : " << characterType << " =====\n\n";

    for (std::size_t index = 0; index < characters.size(); ++index)
    {
        std::cout << '[' << index + 1 << "]\n" << characters[index]->displayStats() << "\n\n";
    }

    while (true)
    {
        std::cout << "Choisissez un " << characterType << " (1-" << characters.size() << ") : ";

        std::size_t choice;
        if (std::cin >> choice && choice >= 1 && choice <= characters.size())
        {
            std::cout << '\n';
            return *characters[choice - 1];
        }

        if (std::cin.eof())
        {
            throw std::runtime_error("Lecture interrompue.");
        }

        std::cout << "Choix invalide. Réessayez.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

Hero& SelectCharacter(std::vector<std::unique_ptr<Hero>>& characters, const std::string& characterType)
{
    return SelectCharacterFrom(characters, characterType);
}

Ennemi& SelectCharacter(std::vector<std::unique_ptr<Ennemi>>& characters, const std::string& characterType)
{
    return SelectCharacterFrom(characters, characterType);
}

void Fight(Hero& hero, Ennemi& enemy)
{
    std::cout << "\033[2J\033[H";
    std::cout << "===== Combat =====\n\n";
    std::string recap;

    while (hero.isAlive() && enemy.isAlive())
    {
        std::cout << hero.displayCombatStats(enemy) << "\n\n";

        if (!recap.empty())
        {
            std::cout << recap << '\n';
        }

        std::cout << "[1] Attaquer\n"
                  << "[2] Bloquer\n"
                  << "[3] Préparer\n"
                  << "Votre action : ";

        int choice;
        while (!(std::cin >> choice) || choice < 1 || choice > 3)
        {
            if (std::cin.eof())
            {
                throw std::runtime_error("Lecture interrompue.");
            }

            std::cout << "Action invalide. Choisissez entre 1 et 3 : ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        hero.selectAction(static_cast<Action>(choice - 1));
        enemy.selectAction();

        std::ostringstream recapStream;
        recapStream << hero.displayAction(enemy) << '\n';

        std::streambuf* consoleBuffer = std::cout.rdbuf(recapStream.rdbuf());
        hero.resolveAction(enemy);
        std::cout.rdbuf(consoleBuffer);

        recap = recapStream.str();
    }

    std::cout << hero.displayCombatStats(enemy) << "\n\n" << recap << '\n';
}

void displayResult(const Hero& hero, const Ennemi& enemy)
{
    if (!hero.isAlive() && !enemy.isAlive())
    {
        std::cout << "Égalité !\n";
    }
    else if (hero.isAlive())
    {
        std::cout << hero.getName() << " remporte le combat !\n";
    }
    else
    {
        std::cout << enemy.getName() << " remporte le combat !\n";
    }

    std::cout << "\nAppuyez sur n'importe quelle touche pour continuer." << std::flush;

#ifdef _WIN32
    _getch();
#else
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
#endif
}
