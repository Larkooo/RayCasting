#pragma once

class Tile
{
public:
	static const uint16_t SIZE = 50;

	enum class Type : uint16_t
	{
		Void = 0,
		Wall = 1
	};

private:
	Type m_Type;
	
public:
	Tile(Type type = Type::Void) : m_Type(type) {}

	Type GetType() const { return m_Type; }
};