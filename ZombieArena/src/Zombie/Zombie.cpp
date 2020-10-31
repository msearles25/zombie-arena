#include <ctime>
#include <cstdlib>
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