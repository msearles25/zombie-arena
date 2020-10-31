#include <SFML/Graphics.hpp>
#include "Bullet/Bullet.h"
#include "Main.h"
#include "Pickup/Pickup.h"
#include "Player/Player.h"
#include "TextureHolder/TextureHolder.h"

int main()
{
	TextureHolder holder;				// Here is the instance of TextureHolder

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

	// Create the background 
	sf::VertexArray background;
	// Load the texture for our background vertex array
	sf::Texture backgroundTexture{ TextureHolder::GetTexture("assets/graphics/background_sheet.png") };

	// Prepare for the horde
	int numZombies;
	int numZombiesAlive;
	Zombie *zombies{ nullptr };

	// Prepare the bullets
	Bullet bullets[100];
	int currentBullet{ 0 };
	int bulletsSpare{ 24 };
	int bulletsInMag{ 6 };
	int magSize{ 6 };
	float fireRate{ 1 };

	// when was the fire button last pressed
	sf::Time lastPressed;

	// Hide the mouse pointer and replace it with the crosshair
	window.setMouseCursorVisible(false);
	sf::Sprite crosshairSprite;
	sf::Texture crosshairTexture = TextureHolder::GetTexture("assets/graphics/crosshair.png");
	crosshairSprite.setTexture(crosshairTexture);
	crosshairSprite.setOrigin(25, 25);

	// Create two pickups
	Pickup healthPickup(1);
	Pickup ammoPickup(2);

	// Scores
	int score{ 0 };
	int hiScore{ 0 };

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
					state = State::PLAYING;
					// Reset the clock so there isn't a frame jump
					clock.restart();
				}
				else if (event.key.code == sf::Keyboard::Return && state == State::GAME_OVER) // start a new game in GAME_OVER state
				{
					state = State::LEVELING_UP;
				}

				if (state == State::PLAYING)
				{
					// Reloading
					if (event.key.code == sf::Keyboard::R)
					{
						if (bulletsSpare >= magSize)
						{
							// Plenty of bullets to reload
							bulletsInMag = magSize;
							bulletsSpare -= magSize;
						}
						else if (bulletsSpare > 0)
						{
							// only a few bullets
							bulletsInMag = bulletsSpare;
							bulletsSpare = 0;
						}
						else
						{

						}
					}
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

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (gameTimeTotal.asMilliseconds() - 
					lastPressed.asMilliseconds() >
					1000 / fireRate && bulletsInMag > 0)
				{
					// Pass the center of the player and the center of the crosshair
					// to the shoot function
					bullets[currentBullet].shoot(
						player.getCenter().x, player.getCenter().y,
						mouseWorldPosition.x, mouseWorldPosition.y);

					currentBullet++;

					if (currentBullet > 99)
					{
						currentBullet = 0;
					}
					lastPressed = gameTimeTotal;

					bulletsInMag--;
				}
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

				// Pass the vertex array by reference
				// to the createBackground function
				int tileSize{ CreateBackground(background, arena) };

				// Spawn the player int he middle of the arena
				player.spawn(arena, resolution, tileSize);

				// Configure the pickups
				healthPickup.setArena(arena);
				ammoPickup.setArena(arena);

				// Create a horde of zombies
				numZombies = 10;

				// Delete the previously allocated memory(if it exists) to not cause a memory leak
				delete[] zombies;
				zombies = createHorde(numZombies, arena);
				numZombiesAlive = numZombies;

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

			// Set the crosshair to the mouse world location
			crosshairSprite.setPosition(mouseWorldPosition);

			// Update our player
			player.update(dtAsSeconds, sf::Mouse::getPosition());

			// Store the players new position
			sf::Vector2f playerPosition(player.getCenter());

			// Make the view center around the player
			mainView.setCenter(player.getCenter());

			// Loop through each Zombie and update them
			for (int i{ 0 }; i < numZombies; i++)
			{
				if (zombies[i].isAlive())
				{
					zombies[i].update(dt.asSeconds(), playerPosition);
				}
			}

			// Update any bullets that are currenlty in flight
			for (int i{ 0 }; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					bullets[i].update(dtAsSeconds);
				}
			}

			healthPickup.update(dtAsSeconds);
			ammoPickup.update(dtAsSeconds);

			// COLLISION DETECTON
			// Has a zombie been shot?
			for (int i{ 0 }; i < 100; i++)
			{
				for (int j{ 0 }; j < numZombies; j++)
				{
					if (bullets[i].isInFlight() && zombies[j].isAlive())
					{
						if (bullets[i].getPosition().intersects(zombies[j].getPosition()))
						{
							// Stop the bullet
							bullets[i].stop();

							// Register the hit and see if it killed the zombie
							if (zombies[j].hit())
							{
								// Is a kill
								score += 10;
								if (score > hiScore)
								{
									hiScore = score;
								}

								numZombiesAlive--;

								// When all the zombies are dead
								if (numZombiesAlive == 0)
								{
									state = State::LEVELING_UP;
								}
							}
						}
					}
				}
			}

			// Has the player been hit by a zombie?
			for (int i{ 0 }; i < numZombies; i++)
			{
				if (player.getPosition().intersects(zombies[i].getPosition()) && zombies[i].isAlive())
				{
					if (player.hit(gameTimeTotal))
					{

					}

					if (player.getHealth() <= 0)
					{
						state = State::GAME_OVER;
					}
				}
			}
		}

		/*
		**************
		DRAW THE SCENE
		**************
		*/
		if (state == State::PLAYING)
		{
			window.clear();
			
			// Set the mainView to be displayed in the window 
			// then draw everything related to it
			window.setView(mainView);
			
			// Draw the Background
			window.draw(background, &backgroundTexture);

			// Draw the zombies
			for (int i{ 0 }; i < numZombies; i++)
			{
				window.draw(zombies[i].getSprite());
			}

			// Draw the bullets
			for (int i{ 0 }; i < 100; i++)
			{
				if (bullets[i].isInFlight())
				{
					window.draw(bullets[i].getShape());
				}
			}

			// Draw the player
			window.draw(player.getSprite());

			// Draw the pickups
			if (ammoPickup.isSpawned())
			{
				window.draw(ammoPickup.getSprite());
			}
			if (healthPickup.isSpawned())
			{
				window.draw(healthPickup.getSprite());
			}

			// Draw the crosshair
			window.draw(crosshairSprite);
		}
		
		if (state == State::LEVELING_UP)
		{

		}
		
		if (state == State::PAUSED)
		{

		}
		
		if (state == State::GAME_OVER)
		{

		}

		window.display();
	}

	// Delete the previously allocated memory on the heap(if it exists)
	delete[] zombies;

	return 0;
}