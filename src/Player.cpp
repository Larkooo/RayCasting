#include "Player.h"

void Player::HandleEvents(sf::Event event)
{
	if (event.type == sf::Event::KeyPressed)
		switch (event.key.code)
		{
		case sf::Keyboard::W:
			m_Velocity += m_Direction * 20.0f;
			break;
		case sf::Keyboard::S:
			m_Velocity -= m_Direction * 20.0f;
			break;
		case sf::Keyboard::Left:
		{
			float rAngle = atan2f(m_Direction.y, m_Direction.x);
			rAngle -= 0.0175f;
			m_Direction = { cosf(rAngle), sinf(rAngle) };
			break;
		}
		case sf::Keyboard::Right:
		{
			float rAngle = atan2f(m_Direction.y, m_Direction.x);
			rAngle += 0.0175f;
			m_Direction = { cosf(rAngle), sinf(rAngle) };
			break;
		}
		}
	//else if (event.type == sf::Event::MouseMoved)
	//{
	//	m_Direction.x *= event.mouseMove.x;
	//	m_Direction.y *= event.mouseMove.y;

	//	// normalize vector
	//	float magnitude = sqrtf(pow(m_Direction.x, 2) + pow(m_Direction.y, 2));
	//	m_Direction /= magnitude;
	//}
}

void Player::Update(float delta)
{
	m_Velocity *= delta;
	m_Position += m_Velocity;
}