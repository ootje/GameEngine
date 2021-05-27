#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Singleton.h"


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

	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;

		void AddTileComponents(dae::Scene& scene, const std::string& color, float middleX, float middleY, float size, int width, int i);
		
		std::vector<std::shared_ptr<dae::GameObject>> m_TileVector;
		std::shared_ptr<dae::GameObject> m_Qbert;
		LevelData m_LevelData;
	};

}
