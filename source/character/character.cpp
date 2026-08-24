#include "character.h"

#include <array>
#include <iomanip>
#include <sstream>

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

std::string Charactere::displayStats() const
{
    constexpr std::size_t lineWidth = 29;

    std::ostringstream stats;
    const std::string blockagePercentage = std::to_string(static_cast<int>(blockage * 100)) + "%";
    const std::size_t padding = lineWidth - name.length() - 2;
    const std::size_t leftPadding = padding / 2;
    const std::size_t rightPadding = padding - leftPadding;

    stats << std::setfill('-') << std::setw(leftPadding) << "" << ' ' << name << ' ' << std::setw(rightPadding) << ""
          << std::setfill(' ') << '\n'
          << "| " << std::left << std::setw(15) << "Vie" << "| " << std::setw(9) << life << "|\n"
          << "| " << std::setw(15) << "Blocage" << "| " << std::setw(9) << blockagePercentage << "|\n"
          << "| " << std::setw(15) << "Attaque" << "| " << std::setw(9) << attack << "|\n"
          << "| " << std::setw(15) << "Contre-attaque" << "| " << std::setw(9) << counterattack << "|\n"
          << "| " << std::setw(15) << "Preparation" << "| x" << std::setw(8) << preparation << "|";

    return stats.str();
}

std::string Charactere::displayCombatStats(const Charactere& opponent) const
{
    constexpr std::size_t lineWidth = 29;

    const auto formatNumber = [](float value)
    {
        std::ostringstream output;
        output << value;
        return output.str();
    };

    const auto makeLines = [&](const Charactere& character)
    {
        std::array<std::string, 6> lines;

        const std::size_t padding = lineWidth - character.name.length() - 2;
        const std::size_t leftPadding = padding / 2;
        const std::size_t rightPadding = padding - leftPadding;

        std::ostringstream title;
        title << std::setfill('-') << std::setw(leftPadding) << "" << ' ' << character.name << ' '
              << std::setw(rightPadding) << "";
        lines[0] = title.str();

        const auto makeStatLine = [](const std::string& label, const std::string& value)
        {
            std::ostringstream line;
            line << "| " << std::left << std::setw(15) << label << "| " << std::setw(9) << value << '|';
            return line.str();
        };

        lines[1] = makeStatLine("Vie", std::to_string(character.currentLife) + "/" + std::to_string(character.life));
        lines[2] = makeStatLine("Blocage", std::to_string(static_cast<int>(character.blockage * 100)) + "%");
        lines[3] = makeStatLine("Attaque", std::to_string(character.attack));
        lines[4] = makeStatLine("Contre-attaque", std::to_string(character.counterattack));
        lines[5] = makeStatLine("Preparation", "x" + formatNumber(character.currentPreparation) + " (x" +
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
