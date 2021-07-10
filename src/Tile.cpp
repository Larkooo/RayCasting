#include "Tile.h"

#include <iostream>

Tile::Tile(Type type, const std::string& texturePath) : m_Type(type)
{
	if (texturePath.length() > 0)
		m_Texture.loadFromFile(texturePath);
}