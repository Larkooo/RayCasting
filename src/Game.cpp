#include "Game.h"

#include "World.h"

Game* Game::sInstance = nullptr;

Game::Game(sf::VideoMode mode, const std::string& title)
{
	m_World = new World;
	// Create window
	create(mode, title);
	sInstance = this;
}

void Game::Init()
{
	//setFramerateLimit(60);
	m_World->Init();

	m_Running = true;
}
void Game::HandleEvents()
{
	mDt = m_Clock.restart();

	sf::Event event;
	while (pollEvent(event))
	{
		if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
			m_Running = false;
		else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::MouseMoved)
			m_World->HandleEvents(event);
	}
}
void Game::Update()
{
	m_World->Update(mDt.asSeconds());
}
void Game::Render()
{
	clear();

	// Render background, floor and ceiling
	float gradientHeight = getSize().y / 8.0f;
	for (uint16_t i = 0; i < (getSize().y / 2) / gradientHeight; i++)
	{
		sf::RectangleShape shape({ (float)getSize().x, gradientHeight });
		shape.setPosition({ 0.0f, (float)getSize().y / 2 + i * gradientHeight });
		shape.setFillColor(sf::Color(10 + i * 10, 10 + i * 10, 10 + i * 10));
		draw(shape);
	}

	m_World->Render();
	display();
}
void Game::Clean()
{
	close();
}