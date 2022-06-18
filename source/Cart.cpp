#include "Cart.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Cart::Cart(NodePtr const& bogieFront, NodePtr const& bogieBack, NodePtr const& upper,
	std::shared_ptr<Road> const& road, float speed, int position)
	:m_upper(upper),
	m_speed(speed)
{
	const float cartLength = 7.0f;
	const float distanceBetweenBages = 4.0f;
	m_bogieBack = make_unique<Bogie>(bogieBack, road, cartLength * position);
	
	m_bogieFront = make_unique<Bogie>(bogieFront, road, cartLength * position + 
		distanceBetweenBages);
	const vec3 bogieFrontPos(m_bogieFront->getPosition());
	const vec3 bogieBackPos(m_bogieBack->getPosition());
	m_upper->setPosition(centerPoint(bogieFrontPos, bogieBackPos));
	const quat rotWorldUpper(0, 0, 90 + angleBetweenBogiesDegrees(bogieFrontPos, bogieBackPos));
	m_upper->setRotation(rotWorldUpper);
}

int Cart::update(Math::vec3 const& pos, float distance)
{
	float speed = m_speed * Game::getIFps();
	m_bogieBack->distanceAdd(speed, pos, distance);
	m_bogieFront->distanceAdd(speed, m_bogieBack->getPosition(), 4);
	const vec3 bogieFrontPos(m_bogieFront->getPosition());
	const vec3 bogieBackPos(m_bogieBack->getPosition());
	const vec3 posWorldUpper(centerPoint(bogieFrontPos, bogieBackPos));
	const quat rotWorldUpper(0, 0, 90 + angleBetweenBogiesDegrees(bogieFrontPos, bogieBackPos));
	m_upper->setWorldPosition(posWorldUpper);
	m_upper->setWorldRotation(rotWorldUpper);
	return 0;
}

void Cart::speedAdd(float speedAdding)
{
	m_speed += speedAdding;
}

NodePtr const& Cart::getNodeForCamera() const
{
	return m_upper;
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

vec3 const& Cart::getFrontBogie() const
{
	return m_bogieFront->getPosition();
}
float Cart::space(Vec3 const& pointOne, Vec3 const& pointTwo) const
{
	const float newX = pointOne.x - pointTwo.x;
	const float newY = pointOne.y - pointTwo.y;
	return Math::fsqrt(newX * newX + newY * newY);
}

Vec3 const& Cart::centerPoint(Vec3 const& point1, Vec3 const& point2) const
{
	return Vec3((point1.x + point2.x) / 2, (point1.y + point2.y) / 2, 0);
}


float Cart::angleBetweenBogiesDegrees(Vec3 const& front, Vec3 const& back) const
{
	const vec2 temp = vec2(front.x - back.x, front.y - back.y);
	// atan2 returns angle in radians, 1 radian ~~ 57.29578 degrees.
	return atan2(temp.y, temp.x) * 57.29578f;;
}