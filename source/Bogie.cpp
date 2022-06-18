#include "Bogie.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Bogie::Bogie(NodePtr const& bogie, std::shared_ptr<Road> const& road, float nulldistance)
	:m_distance(nulldistance), 
	m_bogieNode(bogie)
{
	m_road = make_shared<PosOnRoad>(road, nulldistance);

	m_splinePosition = m_road->getStartSplinePos();
	setPosAndUpvecAndDir();

}

void Bogie::distanceAdd(float frameSpeed, vec3 const& previous, float distance)
{
	m_distance += frameSpeed;
	m_splinePosition = m_road->addOffset(frameSpeed, previous, distance, m_splinePosition);
	setPosAndUpvecAndDir();

	wheelRotation(frameSpeed);
}

vec3 const& Bogie::getPosition() const
{
	return m_bogieNode->getWorldPosition();
}


bool Bogie::isEndRoads() const
{
	return m_road->isEndRoads(m_splinePosition);
}


void Bogie::setPosAndUpvecAndDir()
{
	vec3 pos = m_road->getNewPos(m_splinePosition);
	vec3 dir = m_road->getNewDir(m_splinePosition);
	vec3 up = m_road->getNewUpVec(m_splinePosition);
	m_bogieNode->setWorldPosition(pos);
	m_bogieNode->setWorldDirection(dir, up);
	m_bogieNode->rotate(-90, 0, 0);

}
void Bogie::wheelRotation(float offset)
{
	float angle = (180 * offset) / (Consts::PI * 1.5f);
	m_bogieNode->findNode("front_axle")->rotate(-angle, 0, 0);
	m_bogieNode->findNode("back_axle")->rotate(-angle, 0, 0);
}
