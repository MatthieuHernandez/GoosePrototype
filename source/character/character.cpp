#include "character.h"

#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace
{
std::size_t displayLength(const std::string& text)
{
    std::size_t length = 0;
    for (const unsigned char character : text)
    {
        if ((character & 0xC0) != 0x80)
        {
            ++length;
        }
    }
    return length;
}
}  // namespace

Charactere::Charactere(std::string name, int life, float blockage, int attack, int counterattack, float preparation,
                       std::string description)
{
    this->name = name;
    this->life = life;
    this->blockage = blockage;
    this->attack = attack;
    this->counterattack = counterattack;
    this->preparation = preparation;
    this->description = description;

    this->currentLife = this->life;
    this->currentPreparation = 1.0;
}

const std::string& Charactere::getName() const { return name; }

Action Charactere::getCurrentAction() const { return currentAction; }

int Charactere::getAttack() const { return attack; }

float Charactere::getCurrentPreparation() const { return currentPreparation; }

float Charactere::getBlockage() const { return blockage; }

int Charactere::getCounterattack() const { return counterattack; }

bool Charactere::isAlive() const { return currentLife > 0; }

void Charactere::receiveDamage(int damage)
{
    const int previousLife = currentLife;
    currentLife = std::max(0, currentLife - damage);
    const int damageTaken = previousLife - currentLife;

    std::cout << name << " subit " << damageTaken << " points de dégâts.\n";
    resetPreparation(true);
}

void Charactere::resetPreparation(bool isLost)
{
    if (isLost && currentPreparation != 1.0f)
    {
        std::cout << name << " perd sa préparation.\n";
    }

    currentPreparation = 1.0f;
}

void Charactere::increasePreparation() { currentPreparation *= preparation; }

std::string Charactere::displayStats() const
{
    constexpr std::size_t lineWidth = 29;

    std::ostringstream stats;
    const std::string blockagePercentage = std::to_string(static_cast<int>(blockage * 100)) + "%";
    const std::size_t padding = lineWidth - displayLength(name) - 2;
    const std::size_t leftPadding = padding / 2;
    const std::size_t rightPadding = padding - leftPadding;

    stats << std::setfill('-') << std::setw(leftPadding) << "" << ' ' << name << ' ' << std::setw(rightPadding) << ""
          << std::setfill(' ') << '\n'
          << "| " << std::left << std::setw(15) << "Vie" << "| " << std::setw(9) << life << "|\n"
          << "| " << std::setw(15) << "Blocage" << "| " << std::setw(9) << blockagePercentage << "|\n"
          << "| " << std::setw(15) << "Attaque" << "| " << std::setw(9) << attack << "|\n"
          << "| " << std::setw(15) << "Contre-attaque" << "| " << std::setw(9) << counterattack << "|\n"
          << "| " << std::setw(16) << "Préparation" << "| x" << std::setw(8) << preparation << "|";

    return stats.str();
}

std::string Charactere::displayCombatStats(const Charactere& opponent) const
{
    std::cout << "\033[2J\033[H";

    constexpr std::size_t lineWidth = 32;

    const auto formatNumber = [](float value)
    {
        std::ostringstream output;
        output << value;
        return output.str();
    };

    const auto makeLines = [&](const Charactere& character)
    {
        std::array<std::string, 6> lines;

        const std::size_t padding = lineWidth - displayLength(character.name) - 2;
        const std::size_t leftPadding = padding / 2;
        const std::size_t rightPadding = padding - leftPadding;

        std::ostringstream title;
        title << std::setfill('-') << std::setw(leftPadding) << "" << ' ' << character.name << ' '
              << std::setw(rightPadding) << "";
        lines[0] = title.str();

        const auto makeStatLine = [](const std::string& label, const std::string& value)
        {
            std::ostringstream line;
            line << "| " << label << std::string(15 - displayLength(label), ' ') << "| " << std::left << std::setw(12)
                 << value << '|';
            return line.str();
        };

        lines[1] = makeStatLine("Vie", std::to_string(character.currentLife) + "/" + std::to_string(character.life));
        lines[2] = makeStatLine("Blocage", std::to_string(static_cast<int>(character.blockage * 100)) + "%");
        lines[3] = makeStatLine("Attaque", std::to_string(character.attack));
        lines[4] = makeStatLine("Contre-attaque", std::to_string(character.counterattack));
        lines[5] = makeStatLine("Préparation", "x" + formatNumber(character.currentPreparation) + " (x" +
                                                   formatNumber(character.preparation) + ")");

        return lines;
    };

    const auto characterLines = makeLines(*this);
    const auto opponentLines = makeLines(opponent);
    std::ostringstream combatStats;

    for (std::size_t index = 0; index < characterLines.size(); ++index)
    {
        combatStats << characterLines[index] << (index == 3 ? "   VS   " : "        ") << opponentLines[index];
        if (index + 1 < characterLines.size())
        {
            combatStats << '\n';
        }
    }

    return combatStats.str();
}
