#pragma once

#include "character.h"

class Ennemi;

class Hero : public Charactere
{
  public:
    using Charactere::Charactere;

    void selectMove(Action action);
    void resolveAction(Ennemi& enemy);
    std::string displayAction(const Ennemi& enemy) const;
};
