#ifndef __Road_HEADER__
#define __Road_HEADER__

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>

#include <vector>
#include <memory>


class Road 
{
public:
	Road(Unigine::WorldSplineGraphPtr road);
	Unigine::Math::Vec3 calcPoint(float t);
	// t - position on spline 0 < t < CountSegment Taken from Unugine doc
	Unigine::Math::Vec3 calcTangent(float t);
	Unigine::Math::Vec3 calcUpVector(float t);
	int getSegmentCount();
private:
	
	Unigine::WorldSplineGraphPtr m_road;
	Unigine::Vector<Unigine::SplineSegmentPtr> m_road_segment;
	float m_road_Lenght = 0;
};
#endif