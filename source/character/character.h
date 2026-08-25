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

    const std::string& getName() const;
    Action getCurrentAction() const;
    int getAttack() const;
    float getCurrentPreparation() const;
    float getBlockage() const;
    int getCounterattack() const;
    bool isAlive() const;

    void receiveDamage(int damage);
    void resetPreparation(bool isLost);
    void increasePreparation();

  protected:
    Action currentAction;

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
