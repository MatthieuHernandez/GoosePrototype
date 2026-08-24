#pragma once
#include <string>

enum class Action
{
    attack = 0,
    block = 1,
    prepare = 2
};

class Charactere
{
  public:
    Charactere(std::string name, int life, float blockage, int attack, int counterattack, float preparation,
               std::string description);

    std::string displayStats() const;
    std::string displayCombatStats(const Charactere& opponent) const;

  protected:
    Action currentMove;

  private:
    std::string name;

    int life;

    float blockage;

    int attack;

    int counterattack;

    float preparation;

    std::string description;

    int currentLife;

    float currentPreparation;
};
