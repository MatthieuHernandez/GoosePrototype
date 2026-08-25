#pragma once

#include "ennemi.h"

class Goblin : public Ennemi
{
  public:
    Goblin();
    Action selectAction() override;
};
