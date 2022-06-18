#include "Bogie.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Bogie::Bogie(NodePtr const& bogie, std::shared_ptr<Road> road, float nulldistance)
	:m_distance(nulldistance), 
	m_bogieNode(bogie)
{
	m_road = make_shared<PosOnRoad>(road, nulldistance);

	m_t = m_road->getStart_t();
	setPosAndUpvecAndDir();

}
void Bogie::setPosAndUpvecAndDir()
{
	vec3 pos = m_road->getNewPos(m_t);
	vec3 dir = m_road->getNewDir(m_t);
	vec3 up = m_road->getNewUpVec(m_t);
	m_bogieNode->setWorldPosition(pos);
	m_bogieNode->setWorldDirection(dir, up);
	m_bogieNode->rotate(-90, 0, 0);

}
void Bogie::wheelRotation(float offset)
{
	float angle = (180 * offset) / (m_pi * m_r);
	m_bogieNode->findNode("front_axle")->rotate(-angle, 0, 0);
	m_bogieNode->findNode("back_axle")->rotate(-angle, 0, 0);
}

bool Bogie::isEndRoads() 
{
	return m_road->isEndRoads(m_t);
}

void Bogie::distanceAdd(float frameSpeed, vec3 const& previous, float distance)
{
	m_distance += frameSpeed;
	m_t = m_road->addOffset(frameSpeed, previous, distance, m_t);
	setPosAndUpvecAndDir();

	wheelRotation(frameSpeed);
}
vec3 const& Bogie::getPosition()
{
	return m_bogieNode->getWorldPosition();
}