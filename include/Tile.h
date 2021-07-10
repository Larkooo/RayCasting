#pragma once

//#include "Texture.h"
#include <SFML/Graphics.hpp>

#include <unordered_map>

class Tile
{
public:
	static const uint16_t SIZE = 50;

	/*enum class TextureType : uint8_t
	{
		Cpp = 0
	};

	static const std::unordered_map<TextureType, sf::Texture> sTextures;*/

	enum class Type : uint8_t
	{
		Void = 0,
		Wall = 1
	};

private:
	Type m_Type;
	sf::Texture m_Texture;
	//std::unique_ptr<Texture> m_Texture = nullptr;
	
public:
	Tile(Type type = Type::Void, const std::string& texturePath = "");
	//Tile(Type type, Texture* texture) : m_Type(type), m_Texture(std::unique_ptr<Texture>(texture)) { std::cout << GetTexture()->GetData() << std::endl; }

	Type GetType() const { return m_Type; }
	sf::Texture& GetTexture() { return m_Texture; }
};