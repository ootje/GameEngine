#include "LevelManager.h"


#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Helpers.h"
#include "InputManager.h"
#include "QbertCommands.h"
#include "QbertComponent.h"
#include "TileComponent.h"

void qbert::LevelManager::LoadLevel()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Qbert");

	m_LevelData.blocksWide = 7;
	m_LevelData.heightOffset = 20;
	m_LevelData.tileSize = 60.0f;
	m_LevelData.baseX = 20.0f;
	m_LevelData.baseY = 400.0f;
	m_LevelData.teleportPositions = std::vector<int>{ 150,127 };
	
	position basePosition{ m_LevelData.baseX,m_LevelData.baseY };
	position offsetPosition = basePosition;
	for (int width = 0; width < m_LevelData.blocksWide; width++)
	{
		for (int i = 0; i < m_LevelData.blocksWide -width; i++)
		{
			AddTileComponents(scene, "Orange", offsetPosition.x , offsetPosition.y, m_LevelData.tileSize, width,i); // should read from file
			offsetPosition.x += m_LevelData.tileSize;
		}
		basePosition.x += m_LevelData.tileSize/2.0f;
		basePosition.y -= 0.75f* m_LevelData.tileSize;
		offsetPosition = basePosition;
	}

	m_Qbert = std::make_shared<dae::GameObject>();
	float qbertSize = 40.0f;
	auto* qRender = new dae::RenderComponent("Qbert.png", IdToPositionConverter(m_LevelData.heightOffset * (m_LevelData.blocksWide - 1)).x, IdToPositionConverter(m_LevelData.heightOffset * (m_LevelData.blocksWide - 1)).y, qbertSize, qbertSize);
	m_Qbert->AddComponent(qRender, (int)dae::componentID::render);
	auto* qBert = new QbertComponent(qRender, m_LevelData.heightOffset*(m_LevelData.blocksWide-1), qbertSize);
	m_Qbert->AddComponent(qBert, (int)expandedComponentID::qbert);
	scene.Add(m_Qbert);

	auto* pLeftDown = new Move(qBert,-m_LevelData.heightOffset);
	dae::InputManager::GetInstance().AddCommand(pLeftDown, dae::CB::ButtonA);

	auto* pLeftUp = new Move(qBert, m_LevelData.heightOffset-1);
	dae::InputManager::GetInstance().AddCommand(pLeftUp, dae::CB::ButtonX);

	auto* pRightDown = new Move(qBert, -m_LevelData.heightOffset+1);
	dae::InputManager::GetInstance().AddCommand(pRightDown, dae::CB::ButtonB);

	auto* pRightUp = new Move(qBert,m_LevelData.heightOffset);
	dae::InputManager::GetInstance().AddCommand(pRightUp, dae::CB::ButtonY);
	
}

const LevelData& qbert::LevelManager::GetLevelData() const
{
	return m_LevelData;
}

void qbert::LevelManager::AddTileComponents(dae::Scene& scene, const std::string& color, float middleX, float middleY, float size, int width, int i)
{
	auto tile = std::make_shared<dae::GameObject>();
	tile->AddComponent(new dae::RenderComponent(color + "Cube.png", middleX - size / 2.0f, middleY - size / 2.0f, size, size), (int)dae::componentID::render);
	tile->AddComponent(new qbert::TileComponent(width * 20 + i), (int)qbert::expandedComponentID::tile);
	m_TileVector.push_back(tile);
	scene.Add(tile);
}

