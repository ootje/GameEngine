#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Singleton.h"
#include "Helpers.h"

namespace dae {
	class GameObject;
	class Scene;
}

struct LevelData
{
	int blocksWide;
	int heightOffset;
	float tileSize;
	float baseX;
	float baseY;
	std::vector<int> teleportPositions;
};

namespace qbert
{
	class LevelManager final : public dae::Singleton<LevelManager>
	{
	public:
		void LoadLevel();
		const LevelData& GetLevelData() const;
		void UpdateTile(id tileId);

	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;

		void AddTileComponents(dae::Scene& scene, int colorVar, float middleX, float middleY, float size, id tileId);
		
		std::vector<std::shared_ptr<dae::GameObject>> m_TileVector;
		std::shared_ptr<dae::GameObject> m_Qbert;
		LevelData m_LevelData;
	};

}
