#include "Train.h"
 
using namespace Unigine;
using namespace std;
using namespace Unigine::Math;

Train::Train(std::shared_ptr<Road> const& road, float speed, vector<CartType> const& CartsTypes)
	:m_speed(speed)
{
	for (int i = 0; i < CartsTypes.size(); i++)
	{
		if (CartsTypes[i] == CartType::Barrel)
		{
			Cart vag(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_box.node"), road, m_speed, i);
			m_carts.emplace_back(vag);
		}
		else if (CartsTypes[i] == CartType::Van)
		{
			Cart vag(World::loadNode("Bogie.node"), World::loadNode("Bogie.node"),
				World::loadNode("Up_cylingr.node"), road, m_speed, i);
			m_carts.emplace_back(vag);
		}
	}
}

void Train::update()
{
	int lastCart = m_carts.size() - 1;
	if (!m_carts[lastCart].isEndRoads())
	{
		m_carts[0].update(vec3(0, 0, 0), -1);
		vec3 reference = m_carts[0].getFrontBogie();
		for (int i = 1; i < m_carts.size(); i++)
		{
			m_carts[i].update(reference, 3.0f);
			reference = m_carts[i].getFrontBogie();
		}
	}
}

void Train::speedAdd(float speedAdding) 
{
	
	if (!((m_speed >= 0.5 && speedAdding > 0) || (m_speed < 0.0005 && speedAdding <0)))
	{
		m_speed += speedAdding;
		for (int i = 0; i < m_carts.size(); i++)
		{
			m_carts[i].speedAdd(speedAdding);
		}
	}
}

NodePtr Train::getNodeForCamera() const
{
	int size = m_carts.size() - 1;
	return m_carts[size].getNodeForCamera();
}

float Train::getSpeed() const
{
	return m_speed;
}