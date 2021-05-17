#include "Helpers.h"

#include "GameObject.h"
#include "RenderComponent.h"
#include "TileComponent.h"

void qbert::AddTileComponents(std::shared_ptr<dae::GameObject> object, const std::string& color, float middleX, float middleY, float size, int width, int i)
{
	object->AddComponent(new dae::RenderComponent(color + "Cube.png", middleX - size / 2.0f, middleY - size / 2.0f , size, size),(int)dae::componentID::render);
	object->AddComponent(new qbert::TileComponent(width*20+i),(int)qbert::expandedComponentID::tile);
}


qbert::position qbert::IdToPositionConverter(int id)
{
	return qbert::position{ (float)id, (float)id };
}