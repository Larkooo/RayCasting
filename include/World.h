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
	void Render() 
	{
		// Projected world
		// Window width is the number of casted rays
		std::vector<Ray> rays;
		for (size_t i = 0; i < Game::sInstance->getSize().x; i++)
		{
			sf::Vector2f direction = m_Player.GetDirection();
			// First part of this calculation is to find the initial angle
			// The player angle substracted by the player's fov gives us the starting angle
			// Then in the second part, we add the step to our angle
			// The step is our fov divided by our window width and multiplied by the current x, so we can know the step between each ray
			float rAngle = (atan2f(direction.y, direction.x) - ((m_Player.GetFov() / 2) * PI / 180.0f)) + (i * ((m_Player.GetFov() * PI / 180.0f) / Game::sInstance->getSize().x));

			// Ray going from our player's position to the calculated angle
			// in a vectorial form
			rays.push_back({ m_Player.GetPosition(), { cosf(rAngle), sinf(rAngle) } });
			
			

			// This is really bad, really need to implement DDA
			// x < depth
			for (float x = 0; x < MAP_HEIGHT; x += 0.1f)
			{
				sf::Vector2f rayPos(rays[i].GetOrigin() + rays[i].GetDirection()* x);

				if (rayPos.x < 0 || rayPos.x >= MAP_WIDTH || rayPos.y < 0 || rayPos.y >= MAP_HEIGHT)
					break;

				// If ray hit wall
				if (m_Map[(int32_t) rayPos.x + MAP_WIDTH * (int32_t) rayPos.y].GetType() == Tile::Type::Wall)
				{
					sf::RectangleShape wall({ 1, (float) Game::sInstance->getSize().y });
					// Set the position of the wall to the current column and middle of the screen
					wall.setPosition((float) i, (float) Game::sInstance->getSize().y / 2);
					// Set the origin of the wall to its middle so we can scale it up and down depending on the floor and ceiling
					wall.setOrigin(wall.getSize() / 2.0f);

					// Scale up and down the wall depending on its distance from the ray
					float distance = sqrtf(powf((float) (rayPos - rays[i].GetOrigin()).x,2) + powf((float) (rayPos - rays[i].GetOrigin()).y,2));

					rays[i].mHit = distance;

					sf::Color color;
					//if (distance > 16.0f)
					//	color = sf::Color(0, 0, 0);
					if (distance > 15.0f)
						color = sf::Color(15, 15, 15);
					else if (distance > 14.0f)
						color = sf::Color(20, 20, 20);
					else if (distance > 13.0f)
						color = sf::Color(30, 30, 30);
					else if (distance > 12.0f)
						color = sf::Color(40, 40, 40);
					else if (distance > 10.0)
						color = sf::Color(50, 50, 50);
					else if (distance > 8.0f)
						color = sf::Color(80, 80, 80);
					else if (distance > 6.0f)
						color = sf::Color(100, 100, 100);
					else if (distance > 4.0f)
						color = sf::Color(130, 130, 130);
					else if (distance > 2.0f)
						color = sf::Color(150, 150, 150);
					else if (distance > 1.0f)
						color = sf::Color(200, 200, 200);
					else
						color = sf::Color::White;
					
					float wallScale = 1.0f - (distance / MAP_HEIGHT);

					wall.setScale({ 1.0f, std::fmaxf(wallScale, 0.0f) });
					wall.setFillColor(color);

					Game::sInstance->draw(wall);
					break;
				}
			}
		}

		// Minimap
		const float MINIMAP_SCALE = 0.1f;
		for (size_t i = 0; i < MAP_WIDTH; i++)
		{
			for (size_t m = 0; m < MAP_HEIGHT; m++)
			{
				// tiles
				sf::RectangleShape rect({ Tile::SIZE * MINIMAP_SCALE, Tile::SIZE * MINIMAP_SCALE });
				rect.setFillColor((uint16_t)m_Map[i + MAP_WIDTH * m].GetType() == 1 ? sf::Color::White : sf::Color(30, 30, 30));
				rect.setPosition(i * Tile::SIZE * MINIMAP_SCALE, m * Tile::SIZE * MINIMAP_SCALE);
				Game::sInstance->draw(rect);

				// player
				sf::CircleShape playerShape(2.0f);
				playerShape.setPosition(m_Player.GetPosition() * (float) Tile::SIZE * MINIMAP_SCALE);
				playerShape.setOrigin({ playerShape.getRadius(), playerShape.getRadius() });
				playerShape.setFillColor(sf::Color::Blue);
				Game::sInstance->draw(playerShape);
				
				// rays
				std::vector<sf::Vertex> rayVertices;
				size_t count = 0;
				for (Ray& r : rays)
				{
					count++;
					if (count % 10 != 0) continue;
					rayVertices.push_back({ playerShape.getPosition(), sf::Color::Green });
					rayVertices.push_back({ playerShape.getPosition() + r.GetDirection() * r.mHit * (float)Tile::SIZE * MINIMAP_SCALE, sf::Color::White });
				}

				Game::sInstance->draw(rayVertices.data(), rayVertices.size(), sf::Lines);
			}
		}

		//std::cout << m_Player.GetPosition().x << " " << m_Player.GetPosition().y << std::endl;
		//m_Player.Render();
	}
};