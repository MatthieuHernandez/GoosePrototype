cmake_minimum_required(VERSION 3.16)

project(GoosePrototype LANGUAGES CXX)

add_executable(GoosePrototype
    source/main.cpp
    source/game.cpp
    source/character/character.cpp
    source/character/ennemi.cpp
    source/character/goblin.cpp
    source/character/mage.cpp
    source/character/merfolk.cpp
    source/character/hero.cpp
    source/character/rogue.cpp
    source/character/troll.cpp
    source/character/warrior.cpp
    source/character/werewolf.cpp
)

target_compile_features(GoosePrototype PRIVATE cxx_std_17)

set_target_properties(GoosePrototype PROPERTIES CXX_EXTENSIONS OFF)

if(WIN32)
    set_property(
        TARGET GoosePrototype
        PROPERTY MSVC_RUNTIME_LIBRARY
        "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()
