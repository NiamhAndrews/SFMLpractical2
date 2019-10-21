#include "Game.h"
#include <SFML/Graphics.hpp>

using namespace sf;

sf::RenderWindow* window = new RenderWindow(sf::VideoMode(800, 600), "Launching...");;

Game::Game(){}

void Game::initialize()
{
	player = new Player();

	if (!player->playerTexture.loadFromFile("hedgehog.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading player image" << std::endl;
	}
	player->playerSprite.setTexture(player->playerTexture);
	player->playerSprite.setPosition(50.0f, 50.0f);
	player->playerSprite.setScale(.1, .1);
	

	npc = new NPC();

	if (!npc->npcTexture.loadFromFile("crow.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading npc image" << std::endl;
	}
	npc->npcSprite.setTexture(npc->npcTexture);
	npc->npcSprite.setPosition(400.0f, 50.0f);
	npc->npcSprite.setScale(.1, .1);

	window->setSize(sf::Vector2u(640, 480));
	window->setTitle("Game");
}

void Game::run()
{
	initialize();

	while (window->isOpen())
	{
		update();
		draw();
	}
}

void Game::update()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window->close();

		player->update();
		npc->update();

		if (player->playerSprite.getGlobalBounds().intersects(npc->npcSprite.getGlobalBounds()))
		{
			std::cout << "\n\n!! Touching has occured !! \nThe hedgehog has been eaten by the crow. \nRIP\n\n";
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			player->playerSprite.move(5, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			player->playerSprite.move(-5, 0);
		}
	}

}

void Game::draw()
{
	window->clear();
	window->draw(player->playerSprite);
	window->draw(npc->npcSprite);
	//player->draw();
	//npc->draw();
	window->display();
}


