#pragma once

#include <array>

#include "Game.h"

#include "Tile.h"
#include "Player.h"

const uint16_t MAP_WIDTH = 16;
const uint16_t MAP_HEIGHT = 16;

class World
{
	
	std::array<Tile, MAP_WIDTH * MAP_HEIGHT> m_Map;
	Player m_Player;

public:
	World() = default;

	Player& GetPlayer() { return m_Player; }
	std::array<Tile, MAP_WIDTH * MAP_HEIGHT>& GetMap() { return m_Map; }

	void Init();
	void HandleEvents(sf::Event event)
	{
		m_Player.HandleEvents(event);
	}
	void Update(float elapsedTime)
	{
		m_Player.Update(elapsedTime);
	}
	void Render();
};