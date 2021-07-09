#include "World.h"

#include <iostream>

void World::Init()
{
	srand((uint32_t) time(0));

	/*for (size_t i = 0; i < m_Map.size(); i++)
	{
		m_Map[i] = Tile(Tile::Type((rand() % 10) == 0));
	}*/

	for (size_t i = 0; i < m_Map.size(); i++)
	{
		if (i % MAP_HEIGHT == 0)
		{
			m_Map[i] = Tile(Tile::Type::Wall);
			if (i != 0)
				m_Map[i - 1] = Tile(Tile::Type::Wall);
		}
		else if (i < MAP_HEIGHT || i > m_Map.size() - MAP_HEIGHT)
			m_Map[i] = Tile(Tile::Type::Wall);
	}
}