#pragma once

#include "ennemi.h"

class Merfolk : public Ennemi
{
  public:
    Merfolk();
    Action selectAction() override;
};
