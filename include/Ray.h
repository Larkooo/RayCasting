#pragma once

#include <SFML/Graphics.hpp>

class Ray
{
	/** Starting position of the ray*/
	sf::Vector2f m_Origin;
	/** Direction of the ray, must be normalized */
	sf::Vector2f m_Direction;

public:
	/** Distance to the hit, if there is one */
	float mHit = 0.0f;

public:
	Ray(sf::Vector2f origin = { 0.0f, 0.0f }, sf::Vector2f direction = { 1.0f, 0.0f }) : 
		m_Origin(origin), m_Direction(direction) {}

	sf::Vector2f GetOrigin() const { return m_Origin; }
	sf::Vector2f GetDirection() const { return m_Direction; }

	void SetOrigin(sf::Vector2f origin) { m_Origin = origin; }
	void SetDirection(sf::Vector2f direction) { m_Direction = direction; }
};