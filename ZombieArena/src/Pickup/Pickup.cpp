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

sf::FloatRect Pickup::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

sf::Sprite Pickup::getSprite()
{
	return m_Sprite;
}

bool Pickup::isSpawned()
{
	return m_Spawned;
}

int Pickup::gotIt()
{
	m_Spawned = false;
	m_SecondsSinceDespawn = 0;
	return m_Value;
}

void Pickup::update(float elapsedTime)
{
	if (m_Spawned)
	{
		m_SecondsSinceSpawn += elapsedTime;
	}
	else
	{
		m_SecondsSinceDespawn += elapsedTime;
	}

	// Do we need to hide the pickup?
	if (m_SecondsSinceSpawn > m_SecondsToLive && m_Spawned)
	{
		// Remove the pickup and put it somewhere else
		m_Spawned = false;
		m_SecondsSinceDespawn = 0;
	}

	// Do we need to spawn a pickup?
	if (m_SecondsSinceDespawn > m_SecondsToWait && !m_Spawned)
	{
		// spawn the new pickup and reset the timer
		spawn();
	}
}