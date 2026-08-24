#pragma once

#include <string>
#include <vector>

#include "character/character.h"

const Charactere& SelectCharacter(const std::vector<Charactere>& characters, const std::string& characterType);

void Fight(const Charactere& hero, const Charactere& enemy);
