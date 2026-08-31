#pragma once

#include "character.h"

class Ennemi : public Charactere
{
  public:
    using Charactere::Charactere;

    virtual Action selectAction() = 0;
    virtual void recordActionResult(bool succeeded);

  protected:
    Action selectRandomAction();
    int rollPercentage();

    bool hasPreviousAction = false;
    bool previousActionSucceeded = false;
};
