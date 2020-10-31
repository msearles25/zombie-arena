#pragma once
#include <SFML/Graphics.hpp>

class Pickup
{
private:
	// Start value for pickups
	const int HEALTH_START_VALUE{ 50 };
	const int AMMO_START_VALUE{ 12 };
	const int START_WAIT_TIME{ 10 };
	const int START_SECONDS_TO_LIVE{ 5 };

	// Sprite for a pickup
	sf::Sprite m_Sprite;

	// The arena where it will be spawned
	sf::IntRect m_Arena;

	// How much is the pickup worth
	int m_Value;

	// What kind of pickup is it?
	// 1 = health, 2 = ammo
	int m_Type;

	// Handle the spawning and disappearing of the pickup
	bool m_Spawned;
	float m_SecondsSinceSpawn;
	float m_SecondsSinceDespawn;
	float m_SecondsToLive;
	float m_SecondsToWait;
public:
	Pickup(int type);

	// Prepare the new pickup
	void setArena(sf::IntRect arena);

	void spawn();

	// check the current position of a pickup
	sf::FloatRect getPosition();

	// Get the sprite so to draw in main
	sf::Sprite getSprite();

	// Let the pickup update itself each frame
	void update(float elapsedTime);

	// Is the pickup currently spawned?
	bool isSpawned();

	// Get the pickup
	int gotIt();
	
	// Upgrade the value 
	void upgrade();
};