#include "Road.h"

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>

#include <memory>


class PosOnRoad 
{
public:
	PosOnRoad(std::shared_ptr<Road> road, float distance);

	/**
	* Calculates the initial splinePos at which the distance from the beginning of the spline will be equal to the input value.
	*/
	void calcInit(float distance);
	float getStartSplinePos() const;
	Unigine::Math::vec3 const& getNewPos(float splinePos) const;
	Unigine::Math::vec3 const& getNewDir(float splinePos) const;
	Unigine::Math::vec3 const& getNewUpVec(float splinePos) const;
	float addOffset(float offset, Unigine::Math::vec3 const& initialPosition, 
		float distance, float inSplinePos) const;

	/**
	* Calculates the distance between points on the XY axis.
	*/
	float space(Unigine::Math::Vec3 const& pointOne, Unigine::Math::Vec3 const& pointTwo) const;
	bool isEndRoads(float inSplinePos) const;
private:

	/**
	* Checking for the maximum margin of error inaccuracy.
	*/
	bool approximate(float value, float inaccuracy, float referenceDistance) const;
	
	float correct(float initialPositionDistance, float distance,
		Unigine::Math::vec3 const& predPosition, float inSplinePos) const;

	/**
	* SplinePos - position on spline 0<t<CountSegment.
	*/
	float m_splinePosition = 0;
	std::shared_ptr<Road> m_road;
	int m_segmentCount = 0;
};