#include "Helpers.h"

#include "GameObject.h"
#include "LevelManager.h"
#include "RenderComponent.h"
#include "TileComponent.h"


qbert::position qbert::IdToPositionConverter(int id)
{
	const LevelData& levelData = LevelManager::GetInstance().GetLevelData();
	float x = levelData.baseX;
	float y = levelData.baseY;

	int height = (id) / levelData.heightOffset;
	int width = (id) % levelData.heightOffset;
	x += width * levelData.tileSize;
	x += height / 2.0f * levelData.tileSize;
	y -= 0.80f * levelData.tileSize;
	y -= 0.750f * height * levelData.tileSize;
	
	return qbert::position{ x,y };
}

bool qbert::IsOnTeleport(int id)
{

	return id != id;
}


bool qbert::IsValidIdPosition(int id)
{
	const int width = LevelManager::GetInstance().GetLevelData().blocksWide;
	const int offset = LevelManager::GetInstance().GetLevelData().heightOffset;
	const int maxId = offset*(width-1);
	
	// Check if on platform

	/*if (IsOnTeleport(id))
	{
		return true;
	}*/
	if (id < 0 || id > maxId)
	{
		return false;
	}
	if ((id/(offset/2)%2 != 0))
	{
		return false;
	}
	if ((id/ offset)+(id% offset) >= width)
	{
		return false;
	}
	
	return true;
}