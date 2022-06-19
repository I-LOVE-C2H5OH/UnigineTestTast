#include "PosOnRoad.h"
#include <UnigineLogic.h>

#include <UnigineStreams.h>
#include <UnigineWorlds.h>

#include <UnigineWorld.h>
#include <UnigineGame.h>

#include <memory>
#include <vector>

class Bogie 
{
public:
	Bogie(Unigine::NodePtr const& bogie, std::shared_ptr<Road> const& road, float nullDistance);
	void distanceAdd(float frameSpeed, Unigine::Math::vec3 const& pos, float distance);
	Unigine::Math::vec3 const& getPosition() const;
	bool isEndRoads() const;
private:
	void setPosAndUpvecAndDir();
	void wheelRotation(float offset);

	/**
	 * Position on spline 0 < splinePos < CountSegment Taken from Unugine doc.
	 */
	float m_splinePosition = 0; 
	float m_distance = 0;
	Unigine::NodePtr m_bogieNode;
	std::shared_ptr<PosOnRoad> m_road;
};