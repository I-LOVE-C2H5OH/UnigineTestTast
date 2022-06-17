#include "PosOnRoad.h"

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>
#include <memory>

class Bogie 
{
public:
	Bogie(Unigine::NodePtr const& bogie, std::shared_ptr<Road> road, float nullDistance);
	void distanceAdd(float frameSpeed);
	void distanceAdd(float frameSpeed, Unigine::Math::vec3 const& pos, float distance);
	Unigine::Math::vec3 const& getPosition();
	bool isEndRoads();
private:
	void setPosAndUpvecAndDir();
	void wheelRotation(float offset);
	const float m_pi = 3.1415926f; //Pi
	const float m_r = 1.5f / 2; //Wheel Radius
	float m_t = 0; // t - position on spline 0 < t < CountSegment Taken from Unugine doc
	float m_distance = 0;
	Unigine::NodePtr m_bogieNode;
	std::shared_ptr<PosOnRoad> m_road;
};