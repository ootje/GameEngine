#pragma once
#include <memory>
#include <string>
#include <vector>

#include "Singleton.h"
#include "Helpers.h"

namespace dae {
	class Subject;
	class GameObject;
	class Scene;
}

namespace qbert
{

	struct LevelData
	{
		int blocksWide;
		float tileSize;
		float baseX;
		float baseY;
		std::vector<qbert::id> teleportPositions;
	};
	
	class TeleporterComponent;
	class LivesComponent;
	class ScoreComponent;
	class TileComponent;
	class EnemyManagerComponent;
	class QbertComponent;

	class LevelManager final : public dae::Singleton<LevelManager>
	{
	public:
		void LoadLevel(std::wstring path,int gameMode,int level = 1);
		const LevelData& GetLevelData() const;
		void UpdateTile(id tileId);
		void RevertTile(id tileId);
		id GetPlayerId() const;
		void QbertDeath();
		bool HandleCollision(position pos, float width, float height);
		void ScoreEvent(int event);
		bool IsOnTeleport(id position);
		void ActivateTeleport(id position);
	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;

		void ReloadLevel(int level = 1);
		
		bool CheckCompleted() const;

		void LoadTiles(dae::Scene& scene,int activations,bool reset);
		void AddTileComponents(dae::Scene& scene, int colorVar, float middleX, float middleY, float size, id tileId,int activations,bool reset);
		void AddTeleporters(dae::Scene& scene, std::vector<id> positions, float size);
		
		std::vector<TeleporterComponent*> m_TeleporterVector;
		std::vector<TileComponent*> m_TileVector;
		QbertComponent* m_Qbert;
		EnemyManagerComponent* m_EnemyManager;
		LevelData m_LevelData;
		ScoreComponent* m_ScoreComp;
		LivesComponent* m_LivesComp;
		dae::Subject* m_ScoreSubject;
		
		int m_Level;
	};

}
