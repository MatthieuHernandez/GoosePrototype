cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_COMPILER clang++ CACHE STRING "C++ compiler" FORCE)

project(GoosePrototype LANGUAGES CXX)

add_executable(GoosePrototype
    source/main.cpp
    source/game.cpp
    source/character/character.cpp
    source/character/ennemi.cpp
    source/character/goblin.cpp
    source/character/mage.cpp
    source/character/merfolk.cpp
    source/character/playable_character.cpp
    source/character/rogue.cpp
    source/character/warrior.cpp
    source/character/werewolf.cpp
)
