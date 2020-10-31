#pragma once
#include <SFML/Graphics.hpp>
#include "Zombie/Zombie.h"

int CreateBackground(sf::VertexArray &rVA, sf::IntRect arena);

Zombie *createHorde(int numZombies, sf::IntRect arena);