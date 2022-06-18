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
	Cart(Unigine::NodePtr const& bogieFront, Unigine::NodePtr const& bogieBack, 
		Unigine::NodePtr Upper, std::shared_ptr<Road> const& road, float speed, int position);
	int update(Unigine::Math::vec3 const& pos, float distance);
	void speedAdd(float speedAdding);
	Unigine::NodePtr const& getNodeForCamera() const;
	float getSpeed() const;
	bool isEndRoads() const;
	Unigine::Math::vec3 const& getFrontBogie() const;
	
private:

	/**
	* Calculates the distance between points on the XY axis.
	*/
	float space(Unigine::Math::vec3 const& pointOne, Unigine::Math::vec3 const& pointTwo) const; 

	/**
	* Calculates the centerPoint between points on the XY axis.
	*/
	Unigine::Math::vec3 const& centerPoint(Unigine::Math::vec3 const& point1,
		Unigine::Math::vec3 const& point2) const;

	/**
	* Calculates the Angle between points on the XY axis.
	*/
	float angleBetweenBogiesDegrees(Unigine::Math::vec3 const& front, 
		Unigine::Math::vec3 const& back) const;
	float m_speed = 0;
	std::shared_ptr<Bogie> m_bogieFront;
	std::shared_ptr<Bogie> m_bogieBack;

	/*
	* Node platformand top.
	*/
	Unigine::NodePtr m_upper; 
};