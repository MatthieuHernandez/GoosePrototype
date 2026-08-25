#pragma once

#include <string>
#include <vector>

#include "character/ennemi.h"
#include "character/hero.h"

void displayIntro();

Hero& SelectCharacter(std::vector<Hero>& characters, const std::string& characterType);
Ennemi& SelectCharacter(std::vector<Ennemi>& characters, const std::string& characterType);

void Fight(Hero& hero, Ennemi& enemy);
void displayResult(const Hero& hero, const Ennemi& enemy);
