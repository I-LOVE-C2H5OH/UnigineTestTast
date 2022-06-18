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
	Road(Unigine::WorldSplineGraphPtr const& road);

	/**
	* splinePos - position on spline 0 < splinePos < CountSegment Taken from Unugine doc
	*/
	Unigine::Math::Vec3 calcPoint(float splinePos) const;
	Unigine::Math::Vec3 calcTangent(float splinePos) const;
	Unigine::Math::Vec3 calcUpVector(float splinePos) const;
	int getSegmentCount() const;
private:
	
	Unigine::WorldSplineGraphPtr m_road;
	Unigine::Vector<Unigine::SplineSegmentPtr> m_roadSegments ;
	float m_roadLenght = 0;
};
#endif