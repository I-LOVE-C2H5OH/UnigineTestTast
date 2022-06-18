#include "Train.h"


using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Train::Train(std::shared_ptr<Road> road, float speed, vector<CartType> const& Cart_types)
	:m_speed(speed)
{
	for (int i = 0; i < Cart_types.size(); i++)
	{
		if (Cart_types[i] == CartType::Barrel)
		{
			Cart vag(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_box.node"), road, m_speed, i);
			m_Carts.emplace_back(vag);
		}
		else if (Cart_types[i] == CartType::Van)
		{
			Cart vag(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_cylingr.node"), road, m_speed, i);
			m_Carts.emplace_back(vag);
		}
	}
}

void Train::speedAdd(float speedAdding) //the value that is added to the speed 
{
	if (!((m_speed >= 0.5 && speedAdding > 0) || (m_speed < 0.0005 && speedAdding <0)))
	{
		m_speed += speedAdding;
		for (int i = 0; i < m_Carts.size(); i++)
		{
			m_Carts[i].speedAdd(speedAdding);
		}
	}
}

float Train::getSpeed() const
{
	return m_speed;
}


NodePtr Train::getNodeForCamera()
{
	int size = m_Carts.size() - 1;
	return m_Carts[size].getNodeForCamera();
}

void Train::update()
{
	int lastCart = m_Carts.size() - 1;
	if (!m_Carts[lastCart].isEndRoads())
	{
		m_Carts[0].update(vec3(0,0,0), -1);
		vec3 reference = m_Carts[0].getFrontBogie();
		for (int i = 1; i < m_Carts.size(); i++)
		{
			m_Carts[i].update(reference, 3);
			reference = m_Carts[i].getFrontBogie();
		}
	}
}