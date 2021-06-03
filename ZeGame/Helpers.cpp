#include "Helpers.h"

#include "GameObject.h"
#include "LevelManager.h"
#include "RenderComponent.h"
#include "TileComponent.h"


qbert::position qbert::IdToPositionConverter(id id)
{
	const LevelData& levelData = LevelManager::GetInstance().GetLevelData();
	float x = levelData.baseX;
	float y = levelData.baseY;

	x += float(id.x) * levelData.tileSize;
	x += float(id.y) / 2.0f * levelData.tileSize;
	y -= 0.80f * levelData.tileSize;
	y -= 0.750f * float(id.y) * levelData.tileSize;
	
	return qbert::position{ x,y };
}

bool qbert::IsOnTeleport(id id)
{

	return id.x != id.x;
}


bool qbert::IsValidIdPosition(id testId)
{
	auto data = LevelManager::GetInstance().GetLevelData();
	const int width = data.blocksWide;
	const int offset = data.heightOffset;
	id maxId{};
	maxId.x = 1;
	maxId.y = data.blocksWide - 1;
	
	// Check if on platform

	/*if (IsOnTeleport(id))
	{
		return true;
	}*/
	if (testId.y == 0 || maxId < testId)
	{
		return false;
	}
	if (testId.x == 0)
	{
		return false;
	}
	if (testId.x+testId.y > width)
	{
		return false;
	}
	
	return true;
}