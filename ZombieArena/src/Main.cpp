#include <SFML/Graphics.hpp>
#include "Player/Player.h"

int main()
{
	enum class State					// The game will always be in one of these four states
	{
		PAUSED, 
		LEVELING_UP,
		GAME_OVER,
		PLAYING
	};

	State state = State::GAME_OVER;		// Start with the GAME_OVER state

	// Get the screen resolution and create a window for the game
	sf::Vector2f resolution;
	resolution.x = sf::VideoMode::getDesktopMode().width;
	resolution.y = sf::VideoMode::getDesktopMode().height;

	sf::RenderWindow window(sf::VideoMode(resolution.x, resolution.y), "Zombie Arena");

	// Create an SFML view for the main acton
	sf::View mainView(sf::FloatRect(0, 0, resolution.x, resolution.y));

	// Clock for timing things throuhgout the game
	sf::Clock clock;

	// How long has the PLAYING state been active
	sf::Time getTimeTotal;

	// Mouse relation to the world coordinates
	sf::Vector2f mouseWorldPosition;

	// Mouse in relation to the screen
	sf::Vector2i mouseScreenPosition;

	// Creating an instance of our Player class
	Player player;

	// Boundaries of our arena
	sf::IntRect arena;

	// Our main game loop
	while (window.isOpen())
	{
		// Handle input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyPressed)
			{
				// Pause the game while playing
				if (event.key.code == sf::Keyboard::Return && state == State::PLAYING)
				{
					state = State::PAUSED;
				}
				else if (event.key.code == sf::Keyboard::Return && state == State::PAUSED) // Start playing again
				{
					state == State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				else if (event.key.code == sf::Keyboard::Return && state == State::GAME_OVER) // start a new game in GAME_OVER state
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{

				}
			}
		}

		// Handle the player quitting the game
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}

		// Handle our WASD inputs while playing
		if (state == State::PLAYING)
		{
			// Handling pressing and releasing of the WASD keys
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				player.moveUp();
			}
			else
			{
				player.stopUp();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				player.moveDown();
			}
			else
			{
				player.stopDown();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				player.moveLeft();
			}
			else
			{
				player.stopLeft();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				player.moveRight();
			}
			else
			{
				player.stopRight();
			}
		}


	}

	return 0;
}