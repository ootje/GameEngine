#pragma once
#include <memory>
#include <string>

/*
Components id
base = 0
render = 1
text = 2
 */




namespace dae {
	class GameObject;
}

namespace qbert
{
	enum class expandedComponentID
	{
		tile = 5,
	};
	
	struct position
	{
		float x;
		float y;
	};

	
	void AddTileComponents(std::shared_ptr<dae::GameObject> object,const std::string& color, float middleX, float middleY, float size,int width, int i);

	//int PositionToIdConverter(float x, float y);
	position IdToPositionConverter(int id);
}
