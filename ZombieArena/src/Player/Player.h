#pragma once
#include <SFML/Graphics.hpp>

class Player
{
private:
	const float START_SPEED{ 200.0f };
	const float START_HEALTH{ 100.0f };

	
	sf::Vector2f m_Position;										// the players current position
	
	sf::Sprite m_Sprite;											// Player Sprite
	sf::Texture m_Texture;											// Player Texture

	sf::Vector2f m_Resolution;										// Screen Resolution

	sf::IntRect m_Arena;											// Current arena size

	int m_TileSize;													// Size of each tile in the arena

	bool m_UpPressed;												// Direction(s) the player is currently moving
	bool m_DownPressed;
	bool m_LeftPressed;
	bool m_RightPressed;
	
	int m_Health;													// Players current health
	int m_MaxHealth;												// The maximum health that the player can have

	sf::Time m_LastHit;												// The time that the player was last hit

	float m_Speed;													// Speed (pixels per second)
public:
	Player();

	void spawn(sf::IntRect arena, sf::Vector2f resolution, int tileSize);

	void resetPlayerStats();										// Call at the end of every game

	bool hit(sf::Time timeHit);										// Handle the player getting hit by a zombie
	sf::Time getLastHitTime();										// How long since the player was last hit

	sf::FloatRect getPosition();									// Where is the player currently at
	sf::Vector2f getCenter();										// Where is the center of the player
	float getRotation();											// What angle is the player currently facing

	sf::Sprite getSprite();											// Send a copy of the player sprite tot he main function

	void moveLeft();												// Moving the player
	void moveRight();
	void moveUp();
	void moveDown();

	void stopLeft();												// Stop the players movement in a direction
	void stopRight();
	void stopUp();
	void stopDown();

	void update(float elapsedTime, sf::Vector2i mousePosition);		// Call this once every frame

	void upgradeSpeed();											// Give the player a boost to speed
	void upgradeHealth();											// Give the player more maximum health
	void increaseHealthLevel(int amount);							// Refill the players health to full

	int getHealth();												// Get the players current health
};

