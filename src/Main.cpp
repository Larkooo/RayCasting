#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "Game.h"

const uint16_t WIDTH = 1280;
const uint16_t HEIGHT = 720;

int main()
{
	sf::VideoMode mode(WIDTH, HEIGHT);
	Game game(mode, "RayCaster");

	game.Init();

	while (game.IsRunning())
	{
		game.HandleEvents();
		game.Update();
		game.Render();
	}

	game.Clean();
}