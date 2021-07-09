#pragma once

class World;

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class Game : public sf::RenderWindow
{
	World* m_World;
	sf::Clock m_Clock;
	bool m_Running = false; 

public:
	sf::Time mDt;

	static Game* sInstance;

	Game(sf::VideoMode mode = { 800, 600 }, const std::string& title = "Window");

	World* GetWorld() { return m_World; }
	bool IsRunning() { return m_Running; }

	void Init();
	void HandleEvents();
	void Update();
	void Render();
	void Clean();
};

