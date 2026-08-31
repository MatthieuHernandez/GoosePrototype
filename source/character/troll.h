#pragma once

#include "ennemi.h"

class Troll : public Ennemi
{
  public:
    Troll();
    Action selectAction() override;
};
