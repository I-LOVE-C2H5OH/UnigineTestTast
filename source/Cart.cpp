#include "Cart.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Cart::Cart(NodePtr const& bogieFront, NodePtr const& bogieBack, NodePtr Upper,
	std::shared_ptr<Road> const& road, float speed, int position)
	:m_upper(Upper),
	m_speed(speed)
{
	m_bogieBack = make_unique<Bogie>(bogieBack, road, 7 * position);
	
	m_bogieFront = make_unique<Bogie>(bogieFront, road, 7 * position + 4);

	m_upper->setPosition(centerPoint(m_bogieBack->getPosition(),
		m_bogieFront->getPosition()));

	m_upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(m_bogieFront->getPosition(), m_bogieBack->getPosition())));
}

int Cart::update(Math::vec3 const& pos, float distance)
{
	float speed = m_speed * Game::getIFps();
	m_bogieBack->distanceAdd(speed, pos, distance);
	m_bogieFront->distanceAdd(speed, m_bogieBack->getPosition(), 4);

	m_upper->setPosition(centerPoint(m_bogieBack->getPosition(),
		m_bogieFront->getPosition()));
	m_upper->setRotation(quat(0, 0, 90 +
		getAngleBetweenBogies(m_bogieFront->getPosition(), m_bogieBack->getPosition())));
	return 0;
}

NodePtr const& Cart::getNodeForCamera() const
{
	return m_upper;
}
void Cart::speedAdd(float speedAdding)
{
	m_speed += speedAdding;
}

float Cart::getSpeed() const
{
	return m_speed;
}

bool Cart::isEndRoads() const
{
	if (m_bogieFront->isEndRoads() && m_bogieBack->isEndRoads())
	{
		return true;
	}
	return false;
}

vec3 const& Cart::getFrontBogie()
{
	return m_bogieFront->getPosition();
}
float Cart::space(Vec3 const& pointOne, Vec3 const& pointTwo)
{
	float newX = pointOne.x - pointTwo.x;
	float newY = pointOne.y - pointTwo.y;
	return Math::fsqrt(newX * newX + newY * newY);
}

Vec3 Cart::centerPoint(Vec3 point1, Vec3 point2)
{
	return Vec3((point1.x + point2.x) / 2, (point1.y + point2.y) / 2, 0);
}

// atan2 returns angle in radians, 1 radian ~~ 57.29578 degrees.
float Cart::getAngleBetweenBogies(Vec3 front, Vec3 back)
{
	vec2 temp = vec2(front.x - back.x, front.y - back.y);
	return atan2(temp.y, temp.x) * 57.29578f;
}