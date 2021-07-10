#pragma once

#include <SFML/Graphics.hpp>

class Tile
{
public:
	static const uint16_t SIZE = 50;

	enum class TextureType : uint8_t
	{
		WallBanner = 0, // offsets
		Wall = 1,
		PinkStone = 2,
		Stone = 3,
		BlueStone = 4,
		YellowStone = 5,
		Wood = 6,
		MultiStone = 7
	};

	//static sf::Texture sTexture;

	enum class Type : uint8_t
	{
		Void = 0,
		Wall = 1
	};

private:
	Type m_Type;
	TextureType m_TextureType;
	
public:
	Tile(Type type = Type::Void, TextureType textureType = TextureType::Wall) : m_Type(type), m_TextureType(textureType) {};

	Type GetType() const { return m_Type; }
	TextureType GetTextureType() const { return m_TextureType; }
};