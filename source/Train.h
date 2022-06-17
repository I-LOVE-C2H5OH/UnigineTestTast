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
	Train(std::shared_ptr<Road> road, float speed, std::vector<CartType> const& Cart_types);
	void update();
	Unigine::NodePtr getNodeForCamera() ;
	void speedAdd(float value_for_the_sum_to_the_speed);
	float getSpeed() const;

private:
	float m_speed = 0; 
	Unigine::Vector<Cart> m_Carts;
};