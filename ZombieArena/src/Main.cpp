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
	sf::Time gameTimeTotal;

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
		/*
		************
		HANDLE INPUT
		************
		*/
		// Handle events by polling
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

		// Handle the LEVELING state
		if (state == State::LEVELING_UP)
		{
			if (event.key.code == sf::Keyboard::Num1)
			{
				state = State::PLAYING;
			}
			
			if (event.key.code == sf::Keyboard::Num2)
			{
				state = State::PLAYING;
			}
			
			if (event.key.code == sf::Keyboard::Num3)
			{
				state = State::PLAYING;
			}
			
			if (event.key.code == sf::Keyboard::Num4)
			{
				state = State::PLAYING;
			}
			
			if (event.key.code == sf::Keyboard::Num5)
			{
				state = State::PLAYING;
			}
			
			if (event.key.code == sf::Keyboard::Num6)
			{
				state = State::PLAYING;
			}

			if (state == State::PLAYING)
			{
				// Prepare the level
				arena.width = 500;
				arena.height = 500;
				arena.left = 0;
				arena.top = 0;

				int tileSize = 50;

				// Spawn the player int he middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Reset the clock so there isn't a fram jump
				clock.restart();
			}
		}

		/*
		****************
		UPDATE THE FRAME
		****************
		*/
		if (state == State::PLAYING)
		{
			// Update the delta time
			sf::Time dt = clock.restart();
			
			// Update our total game time
			gameTimeTotal += dt;

			// Make a decimal fraction of 1 from the delta time
			float dtAsSeconds = dt.asSeconds();

			// Where is the mouse pointer currently
			mouseScreenPosition = sf::Mouse::getPosition();

			// Convert the mouse position into world coordinates of the mainView
			mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(), mainView);

			// Update our player
			player.update(dtAsSeconds, sf::Mouse::getPosition());

			// Store the players new position
			sf::Vector2f playerPosition(player.getCenter());

			// Make the view center around the player
			mainView.setCenter(player.getCenter());
		}

	}

	return 0;
}