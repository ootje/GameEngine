#include "Helpers.h"

#include "LevelManager.h"


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

	return LevelManager::GetInstance().IsOnTeleport(id);
}


bool qbert::IsValidIdPosition(id testId)
{
	// Check if on platform

	if (IsOnTeleport(testId))
	{
		return true;
	}
	return IsValidIdPositionEnemy(testId);
}

bool qbert::IsValidIdPositionEnemy(id testId)
{
	auto data = LevelManager::GetInstance().GetLevelData();
	const int width = data.blocksWide;
	id maxId{};
	maxId.x = 1;
	maxId.y = data.blocksWide - 1;
	
	if (testId.y == 0 || maxId < testId)
	{
		return false;
	}
	if (testId.x == 0)
	{
		return false;
	}
	if (testId.x + testId.y > width)
	{
		return false;
	}

	return true;
}