#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
private:
	// Position of the bullet
	sf::Vector2f m_Position;

	// Look of the bullet
	sf::RectangleShape m_BulletShape;

	// Is this bullet currently in motion
	bool m_InFlight{ false };

	// Speed at which the bullet will travel
	float m_BulletSpeed{ 1000 };

	// What fraction of 1 pixel does the bullet travel, 
	// horizontally and vertically each frame?
	// These will be derived from m_BulletSPeed
	float m_BulletDistanceX;
	float m_BulletDistanceY;

	// Some boundaries so the bullet won't fly forever
	float m_MaxX;
	float m_MinX;
	float m_MaxY;
	float m_MinY;
public:
	Bullet();

	// stop the bullet
	void stop();

	// Return the value of m_InFlight
	bool isInFlight();

	// Launch a new bullet
	void shoot(float startX, float startY, float xTarget, float yTarget);

	// Tell the calling code where the bullet currently is
	sf::FloatRect getPosition();

	// Return the actual shape of the bullet
	sf::RectangleShape getShape();

	// Update the bullet each frame
	void update(float elapsedTime);
};

