#include <ctime>
#include <cstdlib>
#include <math.h>
#include "../TextureHolder/TextureHolder.h"
#include "Zombie.h"

void Zombie::spawn(float startX, float startY, int type, int seed)
{
	switch (type)
	{
	case 0:
		// Bloater type
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("assets/graphics/bloater.png"));

		m_Speed = BLOATER_SPEED;
		m_Health = BLOATER_HEALTH;
		break;
	case 1:
		// Chaser type
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("assets/graphics/chaser.png"));

		m_Speed = CHASER_SPEED;
		m_Health = CHASER_HEALTH;
		break;
	case 2:
		// Crawler type
		m_Sprite = sf::Sprite(TextureHolder::GetTexture("assets/graphics/crawler.png"));

		m_Speed = CRAWLER_SPEED;
		m_Health = CRAWLER_HEALTH;
		break;
	}

	// Modify the speed to make the zombie unique
	// Speed modifier
	std::srand((int)time(0) * seed);

	// Somewhere between 80 and 100
	float modifier = (std::rand() % MAX_VARRIANCE) + OFFSET;	
	m_Speed *= modifier;

	// Initialize it's location
	m_Position.x = startX;
	m_Position.y = startY;

	// Set its origin to the center of its sprite
	m_Sprite.setOrigin(25, 25);

	// Set its position
	m_Sprite.setPosition(m_Position);
}

bool Zombie::hit()
{
	m_Health--;
	
	if (m_Health <= 0)
	{
		// Dead
		m_Alive = false;
		m_Sprite.setTexture(TextureHolder::GetTexture("graphics/blood.png"));

		return true;
	}

	// injured but not dead yet
	return false;
}

bool Zombie::isAlive()
{
	return m_Alive;
}

sf::FloatRect Zombie::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

sf::Sprite Zombie::getSprite()
{
	return m_Sprite;
}

void Zombie::update(float elapsedTime, sf::Vector2f playerLocation)
{
	float playerX = playerLocation.x;
	float playerY = playerLocation.y;

	// Update the zombis position
	if (playerX > m_Position.x)
	{
		m_Position.x += m_Speed * elapsedTime;
	}

	if (playerY > m_Position.y)
	{
		m_Position.y += m_Speed * elapsedTime;
	}

	if (playerX < m_Position.x)
	{
		m_Position.x -= m_Speed * elapsedTime;
	}

	if (playerY < m_Position.y)
	{
		m_Position.y -= m_Speed * elapsedTime;
	}

	// Move the sprite
	m_Sprite.setPosition(m_Position);

	// Face the sprite in the correct direction
	float angle = (std::atan2(playerY - m_Position.y,
		playerX - m_Position.x) * 180) / 3.141f;

	m_Sprite.setRotation(angle);
}