#pragma once

#include "character.h"

class Ennemi : public Charactere
{
  public:
    using Charactere::Charactere;

    Action selectMove();
};
