#include "Cart.h"
#include <UnigineLogic.h>
#include <UnigineStreams.h>

#include <UnigineWorlds.h>
#include <UnigineWorld.h>

#include <UnigineGame.h>
#include <vector>

class Train 
{
public:
	Train(std::shared_ptr<Road> const& road, float speed, std::vector<CartType> const& CartsTypes);
	void update();

	/**
	* The value that is added to the speed.
	*/
	void speedAdd(float speedAdding);
	Unigine::NodePtr getNodeForCamera() const;
	float getSpeed() const;
private:
	float m_speed = 0; 
	Unigine::Vector<Cart> m_carts;
};