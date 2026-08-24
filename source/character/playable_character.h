#pragma once
#include "character.h"

class PlayableCharacter : public Charactere
{
  public:
    using Charactere::Charactere;

    void selectMove(Action action);
};
