#pragma once
#include <SFML/Graphics.hpp>

class Zombie
{
private:
	// How fast is each zombie type
	const float BLOATER_SPEED{ 40.0f };
	const float CHASER_SPEED{ 80.0f };
	const float CRAWLER_SPEED{ 20.0f };

	// How tough is each zombie type
	const float BLOATER_HEALTH{ 5.0f };
	const float CHASER_HEALTH{ 1.0f };
	const float CRAWLER_HEALTH{ 3.0f };

	// Make each zombie slightly vary its speed
	const int MAX_VARRIANCE{ 30 };
	const int OFFSET{ 101 - MAX_VARRIANCE };

	// where is the zombie 
	sf::Vector2f m_Position;

	// A sprite for the zombie
	sf::Sprite m_Sprite;

	// How fast the can this zombie move
	float m_Speed;

	// How much health does the zombie have
	float m_Health;

	// Is the zombie alive
	bool m_Alive;
public:
	// Handle when a bullet hits the zombie
	bool hit();
	
	// Check if the zombie is still alive
	bool isAlive();

	// Spawn a new zombie
	void spawn(float startX, float startY, int type, int seed);

	// Return a rectangle that is the position of the zombie in the world
	sf::FloatRect getPosition();

	// Get a copy of the sprite to draw
	sf::Sprite getSprite();

	// Update the zombie each frame
	void update(float elapsedTime, sf::Vector2f playerLocation);
};