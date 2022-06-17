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
	Unigine::Math::vec3 const& getNewPos(float t);
	float getStart_t() const;
	Unigine::Math::vec3 const& getNewDir(float t);
	Unigine::Math::vec3 const& getNewUpVec(float t);
	float addOffset(float offset, float inT);
	float addOffset(float offset, Unigine::Math::vec3 const& initialPosition, 
		float distance, float inT);
	float space(Unigine::Math::Vec3 const& pointOne, Unigine::Math::Vec3 const& pointTwo); 
	//calculates the distance between points on the XY axis
	bool isEndRoads(float inT) const;
private:
	bool approximate(float value, float inaccuracy, float referenceDistance); 
	//checking for the maximum margin of error inaccuracy
	void calcInit(float distance); 
	//calculates the initial t at which the distance from the beginning of the spline will be equal to the input value
	float correct(float initialPositionDistance, float distance,
		Unigine::Math::vec3 const& pred_position, float inT);
	float m_t = 0;
	// t - position on spline 0<t<CountSegment
	std::shared_ptr<Road> m_road;
	int m_segmentCount = 0;
};