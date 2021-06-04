#include "LevelManager.h"


#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Helpers.h"
#include "InputManager.h"
#include "LivesComponent.h"
#include "LivesObserver.h"
#include "QbertCommands.h"
#include "QbertComponent.h"
#include "ResourceManager.h"
#include "ScoreComponent.h"
#include "TileComponent.h"
#include "TileRenderComponent.h"
#include "ScoreObserver.h"
#include "LivesObserver.h"
#include "Subject.h"

void qbert::LevelManager::LoadLevel()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Qbert");

	m_LevelData.blocksWide = 7+1;
	m_LevelData.heightOffset = 20;
	m_LevelData.tileSize = 60.0f;
	m_LevelData.baseX = 20.0f;
	m_LevelData.baseY = 450.0f;
	m_LevelData.teleportPositions = std::vector<int>{ 150,127 };


	// Tile Init
	id maxId{};
	maxId.x = 1;
	maxId.y = m_LevelData.blocksWide - 1;
	position position{};
	for (int y = 1; y < m_LevelData.blocksWide; y++)
	{
		for (int x = 1; x < m_LevelData.blocksWide -y+1; x++)
		{
			id tileId{ x,y };
			position = IdToPositionConverter(tileId);
			position.y += 0.80f * m_LevelData.tileSize;
			//position.x += 0.50f * m_LevelData.tileSize;
			AddTileComponents(scene, 2, position.x , position.y, m_LevelData.tileSize, tileId); // should read from file
		}
	}

	//Qbert Init
	m_Qbert = std::make_shared<dae::GameObject>();
	float qbertSize = 40.0f;
	auto* qRender = new dae::RenderComponent("Qbert.png", IdToPositionConverter(maxId).x, IdToPositionConverter(maxId).y, qbertSize, qbertSize);
	m_Qbert->AddComponent(qRender, (int)dae::componentID::render);

	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto scoreText = new dae::TextComponent("", scoreFont, 80, 120);
	m_Qbert->AddComponent(scoreText, (int)dae::componentID::text);
	auto scoreObserver = new ScoreObserver();
	auto scoreSubject = new dae::Subject();
	scoreSubject->Attach(scoreObserver);
	auto scoreComp = new ScoreComponent(scoreText, scoreObserver);
	scoreObserver->AttachScoreComp(scoreComp);
	m_Qbert->AddComponent(scoreComp,(int)expandedComponentID::score);

	auto livesFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto livesText = new dae::TextComponent("", livesFont, 80, 100);
	m_Qbert->AddComponent(livesText, (int)dae::componentID::text);
	auto livesObserver = new LivesObserver();
	auto livesSubject = new dae::Subject();
	livesSubject->Attach(livesObserver);
	auto liveComp = new LivesComponent(livesText, livesObserver);
	livesObserver->AttachLivesComp(liveComp);
	m_Qbert->AddComponent(liveComp, (int)expandedComponentID::lives);
	
	auto* qBert = new QbertComponent(qRender, maxId, qbertSize, scoreSubject,livesSubject);
	m_Qbert->AddComponent(qBert, (int)expandedComponentID::qbert);
	
	scene.Add(m_Qbert);

	//Qbert Commands
	auto* pLeftDown = new Move(qBert, id{ 0, -1});
	dae::InputManager::GetInstance().AddCommand(pLeftDown, dae::CB::ButtonA);
	auto* pLeftUp = new Move(qBert, id{-1,1});
	dae::InputManager::GetInstance().AddCommand(pLeftUp, dae::CB::ButtonX);
	auto* pRightDown = new Move(qBert, id{1,-1});
	dae::InputManager::GetInstance().AddCommand(pRightDown, dae::CB::ButtonB);
	auto* pRightUp = new Move(qBert,id{0,1});
	dae::InputManager::GetInstance().AddCommand(pRightUp, dae::CB::ButtonY);
	
}

const LevelData& qbert::LevelManager::GetLevelData() const
{
	return m_LevelData;
}

void qbert::LevelManager::AddTileComponents(dae::Scene& scene, int colorVar, float middleX, float middleY, float size, id tileId)
{
	auto tile = std::make_shared<dae::GameObject>();
	//tile->AddComponent(new dae::RenderComponent(color + "Cube.png", middleX - size / 2.0f, middleY - size / 2.0f, size, size), (int)dae::componentID::render);
	TileRenderComponent* tileRenderComp = new TileRenderComponent(colorVar, middleX - size / 2.0f, middleY - size / 2.0f, size, size);
	tile->AddComponent(tileRenderComp,(int)expandedComponentID::tileRender);
	tile->AddComponent(new qbert::TileComponent(tileId,tileRenderComp), (int)expandedComponentID::tile);
	m_TileVector.push_back(tile);
	scene.Add(tile);
}

void qbert::LevelManager::UpdateTile(id tileId)
{
	// Can be improved
	auto it = std::find_if(m_TileVector.begin(), m_TileVector.end(),
		[&tileId](std::shared_ptr<dae::GameObject> tile)
		{
			return static_cast<TileComponent*>(tile->GetComponent((int)qbert::expandedComponentID::tile))->GetId() == tileId;
		});
	if (it != m_TileVector.end())
	{
		static_cast<TileComponent*>(it->get()->GetComponent((int)qbert::expandedComponentID::tile))->GetJumpedOn();
	}
}

qbert::id qbert::LevelManager::GetPlayerId() const
{
	auto qbertComp = m_Qbert->GetComponent((int)expandedComponentID::qbert);
	if (qbertComp != nullptr)
	{
		return static_cast<QbertComponent*>(qbertComp)->GetOldId();
	}
	return id{ 1,m_LevelData.blocksWide - 1 }; // top position
}

