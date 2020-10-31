#include "Pickup.h"
#include "../TextureHolder/TextureHolder.h"

Pickup::Pickup(int type)
{
	// Store the type of the pickup
	m_Type = type;
	
	// Associate the texture with our sprite
	if (m_Type == 1)
	{
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("assets/graphics/health_pickup.png"));

		// How much is the pickup worth?
		m_Value = HEALTH_START_VALUE;
	}
	else
	{
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("assets/graphics/ammo_pickup.png"));

		// How much is the pickup worth?
		m_Value = AMMO_START_VALUE;
	}

	m_Sprite.setOrigin(25, 25);

	m_SecondsToLive = START_SECONDS_TO_LIVE;
	m_SecondsToWait = START_WAIT_TIME;
}

void Pickup::setArena(sf::IntRect arena)
{
	// Copy the arena details into the pickup m_Arena
	m_Arena.left = arena.left + 50;
	m_Arena.width = arena.width - 50;
	m_Arena.top = arena.top + 50;
	m_Arena.height = arena.height - 50;

	spawn();
}

void Pickup::spawn()
{
	// Spawn at a random location
	srand((int)time(0) / m_Type);
	int x{ (rand() % m_Arena.width) };
	
	srand((int)time(0) * m_Type);
	int y{ (rand() % m_Arena.height) };

	m_SecondsSinceSpawn = 0;
	m_Spawned = true;

	m_Sprite.setPosition(x, y);
}