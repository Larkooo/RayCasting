#pragma once

#include <SFML/Graphics.hpp>

#include <iostream>

#include "Game.h"
#include "Ray.h"

#include "Utils.h"

class Player
{
	sf::Vector2f m_Position;
	sf::Vector2f m_Velocity;
	sf::Vector2f m_Direction;

	float m_Fov;

public:
	Player(sf::Vector2f position = { 8.0f, 8.0f }, sf::Vector2f velocity = { 0.0f, 0.0f }, sf::Vector2f direction = { 0.5f, 0.5f }, float fov = 45.0f) :
		m_Position(position), m_Velocity(velocity), m_Direction(direction), m_Fov(fov) {}

	sf::Vector2f GetPosition() const { return m_Position; }
	sf::Vector2f GetVelocity() const { return m_Velocity; }
	sf::Vector2f GetDirection() const { return m_Direction; }
	float GetFov() const { return m_Fov; }

	void SetPosition(sf::Vector2f position) { m_Position = position; }
	void SetVelocity(sf::Vector2f velocity) { m_Velocity = velocity; }
	void SetDirection(sf::Vector2f direction) { m_Direction = direction; }

	void HandleEvents(sf::Event event);
	void Update(float delta);
};