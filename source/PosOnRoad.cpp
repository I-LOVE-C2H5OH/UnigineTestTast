#include "PosOnRoad.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

PosOnRoad::PosOnRoad(std::shared_ptr<Road> road, float distance)
	:m_road(road)
{
	m_segmentCount = road->getSegmentCount();
	calcInit(distance);
}

void PosOnRoad::calcInit(float distance)
{
	float dist = 0;
	const float tmax = m_road->getSegmentCount();
	vec3 pos = m_road->calcPoint(0);
	for (float i = 0.0f; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= distance)
		{
			m_splinePosition = i;
			i = tmax + 1;
		}
	}
}

float PosOnRoad::getStartSplinePos() const
{
	return m_splinePosition;
}

vec3 const& PosOnRoad::getNewPos(float splinePos) const
{	
	return m_road->calcPoint( splinePos) + vec3(0,0,1);
}

vec3 const& PosOnRoad::getNewDir(float splinePos) const
{
	return m_road->calcTangent( splinePos);
}

vec3 const& PosOnRoad::getNewUpVec(float splinePos) const
{
	return m_road->calcUpVector( splinePos);
}

float PosOnRoad::addOffset(float offset, Math::vec3 const& predPosition, float distance, float inSplinePos) const
{
	float dist = 0;
	const float tmax = m_road->getSegmentCount();
	vec3 pos = m_road->calcPoint(inSplinePos);
	for (float i = inSplinePos; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);

		pos = post;
		//Checking the "distance traveled" for the required offset
		if (dist >= offset)
		{
			inSplinePos = i;
			//forced exit from the loop
			i = tmax + 1;
		}
	}
	float predPositionDistance = space(predPosition, pos);
	if (distance > 0 && !approximate(predPositionDistance, 0.05f, distance))
	{
		inSplinePos = correct(predPositionDistance, distance, predPosition, inSplinePos);
	}
	return inSplinePos;
}

float PosOnRoad::space(Vec3 const& point0, Vec3 const& point1) const
{
	const float newX = point0.x - point1.x;
	const float newY = point0.y - point1.y;
	return Math::fsqrt(newX * newX + newY * newY);
}

bool PosOnRoad::isEndRoads(float inSplinePos) const
{
	if (inSplinePos >= m_segmentCount - 0.1 || inSplinePos == 0)
	{
		return true;
	}
	return false;
}

bool PosOnRoad::approximate(float value, float inaccuracy, float referenceDistance) const
{
	bool returned = false;
	if (referenceDistance < 0 || (value <= referenceDistance + inaccuracy && value >= referenceDistance - inaccuracy))
	{
		returned = true;
	}
	return returned;
}

float PosOnRoad::correct(float predPositionDistance, float distance, vec3 const& predPosition, float inSplinePos) const
{
	const float tmax = m_road->getSegmentCount();
	vec3 post = m_road->calcPoint(inSplinePos);
	if (predPositionDistance > distance)
	{
		for (float i = inSplinePos; i > 0; i -= 0.0001)
		{
			post = m_road->calcPoint(i);
			predPositionDistance = space(predPosition, post);
			//Checking the "distance traveled" for the required offset
			if (predPositionDistance <= distance)
			{
				inSplinePos = i;
				//forced exit from the loop
				i = -1;
			}
		}
	}
	else if (predPositionDistance < distance)
	{
		for (float i = inSplinePos; i < tmax; i += 0.0001)
		{
			post = m_road->calcPoint(i);
			predPositionDistance = space(predPosition, post);
			//Checking the "distance traveled" for the required offset
			if (predPositionDistance >= distance)
			{
				inSplinePos = i;
				//forced exit from the loop
				i = tmax + 1;
			}
		}
	}

	return inSplinePos;
}