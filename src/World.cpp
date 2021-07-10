#include "World.h"

#include <iostream>

void World::Init()
{
	srand((uint32_t) time(0));

	bool yes = true;
	for (size_t i = 0; i < m_Map.size(); i++)
	{
		if (yes)
		{
			m_Map[i] = Tile(Tile::Type((rand() % 10) == 0), "./res/textures/c++.jpg");
			yes = false;
		}
		else
		{
			m_Map[i] = Tile(Tile::Type((rand() % 10) == 0));
		}
	}

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

void World::Render()
{
	// Used variables
	sf::Vector2u renderSize = Game::sInstance->getSize();
	sf::Vector2f playerDirection = m_Player.GetDirection();
	float rPlayerFov = m_Player.GetFov() * PI / 180.0f;

	// Projected world
	// Window width is the number of casted rays
	std::vector<Ray> rays;
	std::vector<sf::Vertex> vertices;

	static sf::Texture texture;

	static auto loadTexture = [&]() {texture.loadFromFile("./res/textures/c++.jpg"); return 0; }();

	static sf::Vector2u textureSize = { 630, 630 };

	for (size_t i = 0; i < renderSize.x; i++)
	{
		// First part of this calculation is to find the initial angle
		// The player angle subtracted by the player's fov gives us the starting angle
		// Then in the second part, we add the step to our angle
		// The step is our fov divided by our window width and multiplied by the current x, so we can know the step between each ray
		float rAngle = (atan2f(playerDirection.y, playerDirection.x) - rPlayerFov / 2.0f + (i * (rPlayerFov / renderSize.x)));

		// Ray going from our player's position to the calculated angle
		// in a vectorial form
		rays.push_back({ m_Player.GetPosition(), { cosf(rAngle), sinf(rAngle) } });

		// DDA
		sf::Vector2f stepSize(sqrtf(1 + powf(rays[i].GetDirection().y / rays[i].GetDirection().x, 2)), sqrtf(1 + powf(rays[i].GetDirection().x / rays[i].GetDirection().y, 2)));
		sf::Vector2i rayMapPosition = (sf::Vector2i) rays[i].GetOrigin();

		// x = length in columns
		// y = length in rows
		sf::Vector2f rayLength;

		sf::Vector2i step;
		if (rays[i].GetDirection().x < 0)
		{
			step.x = -1;
			rayLength.x = (rays[i].GetOrigin().x - (float) rayMapPosition.x) * stepSize.x;
		}
		else
		{
			step.x = 1;
			rayLength.x = ((float) (rayMapPosition.x + 1) - rays[i].GetOrigin().x) * stepSize.x;
		}

		if (rays[i].GetDirection().y < 0)
		{
			step.y = -1;
			rayLength.y = (rays[i].GetOrigin().y - (float) rayMapPosition.y) * stepSize.y;
		}
		else
		{
			step.y = 1;
			rayLength.y = ((float) (rayMapPosition.y + 1) - rays[i].GetOrigin().y) * stepSize.y;
		}

		float rayDistance = 0.0f;
		float maxDistance = 100.0f;
		while (rayDistance < maxDistance)
		{
			// increment vector length
			if (rayLength.x < rayLength.y)
			{
				rayMapPosition.x += step.x;
				rayDistance = rayLength.x;
				rayLength.x += stepSize.x;
			}
			else
			{
				rayMapPosition.y += step.y;
				rayDistance = rayLength.y;
				rayLength.y += stepSize.y;
			}

			if (rayMapPosition.x < 0 || rayMapPosition.x >= MAP_WIDTH || rayMapPosition.y < 0 || rayMapPosition.y >= MAP_HEIGHT)
				break;

			// check if hit
			if (m_Map[rayMapPosition.x + MAP_WIDTH * rayMapPosition.y].GetType() == Tile::Type::Wall)
			{
				//Tile& tile = m_Map[rayMapPosition.x + MAP_WIDTH * rayMapPosition.y];

				// raw distance
				rays[i].mHit = rayDistance;
			
				// Fix the fish eye by alternating the distance depending on the delta angle
				// cosf(rayAngle - playerAngle)
				rayDistance *= cosf(rAngle - atan2f(playerDirection.y, playerDirection.x));

				//Calculate distance of perpendicular ray (Euclidean distance will give fisheye effect!)
				double perpWallDist;
				if (rayLength.y > rayLength.x) perpWallDist = (rayMapPosition.x - rays[i].GetOrigin().x + (1 - step.x) / 2) / rays[i].GetDirection().x;
				else           perpWallDist = (rayMapPosition.y - rays[i].GetOrigin().y + (1 - step.y) / 2) / rays[i].GetDirection().y;

				sf::Color color;
				if (rayDistance > 15.0f)
					color = sf::Color(15, 15, 15);
				else if (rayDistance > 14.0f)
					color = sf::Color(20, 20, 20);
				else if (rayDistance > 13.0f)
					color = sf::Color(30, 30, 30);
				else if (rayDistance > 12.0f)
					color = sf::Color(40, 40, 40);
				else if (rayDistance > 10.0)
					color = sf::Color(50, 50, 50);
				else if (rayDistance > 8.0f)
					color = sf::Color(80, 80, 80);
				else if (rayDistance > 6.0f)
					color = sf::Color(100, 100, 100);
				else if (rayDistance > 4.0f)
					color = sf::Color(130, 130, 130);
				else if (rayDistance > 2.0f)
					color = sf::Color(150, 150, 150);
				else if (rayDistance > 1.0f)
					color = sf::Color(200, 200, 200);
				else
					color = sf::Color::White;

				int lineHeight = renderSize.y / perpWallDist;
				
				//std::cout << rayDistance << std::endl;

				float ceiling = (renderSize.y / 2.0f) - (renderSize.y / rayDistance);
				float floor = renderSize.y - ceiling;

				/*int ceiling = -lineHeight / 2 + renderSize.y / 2;
				if (ceiling < 0) ceiling = 0;
				int floor = lineHeight / 2 + renderSize.y / 2;
				if (ceiling >= renderSize.y) floor = renderSize.y - 1;*/

				// check if tile is textured
				//if (tile.GetTexture().getSize().x > 0)
					
				//sf::Texture tileTexture = tile.GetTexture();

				// wall x
				float localX;
				if (rayLength.y > rayLength.x)
					localX = rays[i].GetOrigin().y + perpWallDist * rays[i].GetDirection().y;
				else
					localX = rays[i].GetOrigin().x + perpWallDist * rays[i].GetDirection().x;
				localX -= floorf(localX);

				// find the texture coordinate to display with our x wall
				uint32_t texX = localX * textureSize.x;
				if (rayLength.y > rayLength.x && rays[i].GetDirection().x > 0)
					texX = textureSize.x - texX - 1;
				if (rayLength.x > rayLength.y && rays[i].GetDirection().y < 0)
					texX = textureSize.x - texX - 1;

				// ceiling - floor = line height
				float texStep = 1.0f * textureSize.y / (floor - ceiling);
				// Starting texture coordinate
				double texPosStart = (ceiling - renderSize.y / 2 + (floor - ceiling) / 2) * texStep;
				double texPosEnd = (floor - renderSize.y / 2 + (floor - ceiling) / 2) * texStep;

				uint32_t texYStart = (int)(texPosStart) & (textureSize.y - 1);
				uint32_t texYEnd = (int)(texPosEnd) & (textureSize.y - 1);

				//std::cout << texX << std::endl;

				// if ray hits a vertical line and color isn't too low, reduce the color, to add more depth
				if (rayLength.y > rayLength.x && color.r > 50)
				{
					color.r -= 30; color.g -= 30; color.b -= 30;
				}

				//std::cout << texX << std::endl;

				vertices.push_back({ { (float)i, (float) ceiling }, color, { (float)texX, (float)texPosStart }});
				vertices.push_back({ { (float)i, (float) floor }, color, { (float)texX, (float)texPosEnd } });

				break;
			}
		}
	}

	// Draw walls vertices
	//sf::Texture::bind(&texture);
	sf::RenderStates states(&texture);

	Game::sInstance->draw(vertices.data(), vertices.size(), sf::Lines, states);

	// Mini map
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
			playerShape.setPosition(m_Player.GetPosition() * (float)Tile::SIZE * MINIMAP_SCALE);
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
}
