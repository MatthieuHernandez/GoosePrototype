#pragma once

#include "ennemi.h"

class Merfolk : public Ennemi
{
  public:
    Merfolk();
    Action selectAction() override;
    void recordActionResult(bool succeeded) override;

  private:
    bool hasPreviousAction = false;
    bool previousActionSucceeded = false;
};
