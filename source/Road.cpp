#include "Road.h"

using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Road::Road(WorldSplineGraphPtr const& road)
	:m_road(road)
{
	m_road->getSplineSegments(m_roadSegments );
	for (SplineSegmentPtr& segment : m_roadSegments )
	{
		segment->assignSource(
			"Rels_Strelka\\_Nodes\\PutWood\\PutWood_100m_.node",
			SplineSegment::FORWARD_X);
		segment->setSegmentMode(
			"Rels_Strelka\\_Nodes\\PutWood\\PutWood_100m_.node",
			SplineSegment::SEGMENT_STRETCH);
		m_roadLenght += segment->getLength();
	}
}

Vec3 Road::calcPoint(float splinePos) const
{
	const  int segment = splinePos;
	splinePos -= segment;
	return m_roadSegments [segment]->calcPoint(splinePos) + m_road->getWorldPosition();
}

Vec3 Road::calcTangent(float splinePos) const
{
	const int segment = splinePos;
	splinePos -= segment;
	return m_roadSegments [segment]->calcTangent((splinePos));
}

Vec3 Road::calcUpVector(float splinePos) const
{
	const int segment = splinePos;
	splinePos -= segment;
	return m_roadSegments [segment]->calcUpVector(splinePos);
}

int Road::getSegmentCount() const
{
	return m_roadSegments.size();
}
