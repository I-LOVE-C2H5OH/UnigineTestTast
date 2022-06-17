#include "PosOnRoad.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

PosOnRoad::PosOnRoad(std::shared_ptr<Road> road, float distance)
	:sss(road)
{
	m_road = road.get();
	m_segmentCount = road->getSegmentCount();
	calcInit(distance);
}


float PosOnRoad::getStart_t() const
{
	return m_t;
}
void PosOnRoad::calcInit(float distance)
{
	float dist = 0;
	float tmax = m_road->getSegmentCount();
	vec3 pos = m_road->calcPoint(0);
	for (float i = 0.0f; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= distance)
		{
			m_t = i;
			i = tmax + 1;
		}
	}

}
float PosOnRoad::correct(float pred_position_distance, float distance, vec3 const& pred_position, float inT)
{
	float tmax = m_road->getSegmentCount();
	vec3 post = m_road->calcPoint(inT);
	if (pred_position_distance > distance)
	{
		for (float i = inT; i > 0; i -= 0.0001)
		{
			post = m_road->calcPoint(i);
			pred_position_distance = space(pred_position, post);
			if (pred_position_distance <= distance) //Checking the "distance traveled" for the required offset
			{
				inT = i;
				i = -1;  //forced exit from the loop
			}
		}
	}
	else if (pred_position_distance < distance) 
	{
		for (float i = inT; i < tmax; i += 0.0001)
		{
			post = m_road->calcPoint(i);
			pred_position_distance = space(pred_position, post);
			if (pred_position_distance >= distance) //Checking the "distance traveled" for the required offset
			{
				inT = i;
				i = tmax + 1;  //forced exit from the loop
			}
		}
	}

	return inT;

}

bool PosOnRoad::isEndRoads(float inT) const
{
	if (inT >= m_segmentCount - 0.1 || inT == 0)
	{
		return true;
	}
	return false;
}

float PosOnRoad::addOffset(float offset, Math::vec3 const& pred_position, float distance, float inT)
{
	float dist = 0;
	float tmax = m_road->getSegmentCount();
	vec3 pos = m_road->calcPoint(inT);
	for (float i = inT; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		
		pos = post;
		if (dist >= offset) //Checking the "distance traveled" for the required offset
		{
			inT = i;
			i = tmax + 1; //forced exit from the loop
		}
	}
	float pred_position_distance = space(pred_position, pos);
	if (!approximate(pred_position_distance, 0.05f, distance))
	{
		inT = correct(pred_position_distance, distance, pred_position, inT);
	}
	return inT;
}

bool PosOnRoad::approximate(float value, float inaccuracy, float reference_distance)
{
	bool returned = false;
	if (reference_distance < 0 || (value <= reference_distance + inaccuracy && value >=  reference_distance - inaccuracy))
	{
		returned = true;
	}
		return returned;
}

float PosOnRoad::addOffset(float offset, float inT)
{
	float dist = 0;
	float tmax = m_road->getSegmentCount();
	vec3 pos = m_road->calcPoint(inT);
	for (float i = inT; i < tmax; i += 0.0001)
	{
		vec3 post = m_road->calcPoint(i);
		dist += space(post, pos);
		pos = post;
		if (dist >= offset) //Checking the "distance traveled" for the required offset
		{
			inT = i;
			i = tmax + 1;  //forced exit from the loop
		}
	}
	return inT;
}



vec3 const& PosOnRoad::getNewPos(float t)
{	
	return m_road->calcPoint(t) + vec3(0,0,1);
}

vec3 const& PosOnRoad::getNewDir(float t)
{
	return m_road->calcTangent(t);
}

vec3 const& PosOnRoad::getNewUpVec(float t)
{
	return m_road->calcUpVector(t);
}

float PosOnRoad::space(Vec3 const& point_0, Vec3 const& point_1)
{
	float newX = point_0.x - point_1.x;
	float newY = point_0.y - point_1.y;
	return Math::fsqrt(newX * newX + newY * newY);
}