#pragma once

#include "ennemi.h"

class Werewolf : public Ennemi
{
  public:
    Werewolf();
    Action selectAction() override;
    void recordActionResult(bool succeeded) override;

  private:
    bool hasPreviousAction = false;
    bool previousActionSucceeded = false;
};
