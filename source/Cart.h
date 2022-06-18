#include "Bogie.h"
#include "CartType.h"

#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>
#include <memory>

class Cart
{
public:
	Cart(Unigine::NodePtr const& bogie_Front, Unigine::NodePtr const& bogie_BACK, 
		Unigine::NodePtr Upper, std::shared_ptr<Road> road, float speed, int position);
	int update(Unigine::Math::vec3 const& pos, float distance);
	Unigine::NodePtr const& getNodeForCamera() const;
	void speedAdd(float speedAdding);
	float getSpeed() const;
	bool isEndRoads();
	Unigine::Math::vec3 const& getFrontBogie();
	
private:
	float space(Unigine::Math::vec3 const& pointOne, Unigine::Math::vec3 const& pointTwo); //calculates the distance between points on the XY axis
	Unigine::Math::vec3 centerPoint(Unigine::Math::vec3 point1,
		Unigine::Math::vec3 point2); //calculates the centerPoint between points on the XY axis
	float getAngleBetweenBogies(Unigine::Math::vec3 front, Unigine::Math::vec3 back); //calculates the Angle between points on the XY axis
	float m_speed = 0;
	std::shared_ptr<Bogie> m_bogieFront;
	std::shared_ptr<Bogie> m_bogieBack;
	Unigine::NodePtr m_upper; // node platform and top
};