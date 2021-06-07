#include "LevelManager.h"

#include <GameObject.h>
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
#include "EnemyManagerComponent.h"
#include "SDL_SoundSystem.h"
//#include "SoundServiceLocator.h"
#include "TeleporterComponent.h"

#include "rapidjson.h"
#include "document.h"
#include "filereadstream.h"

void qbert::LevelManager::LoadLevel(std::wstring path,int gameMode,int level)
{
	float qbertSize = 40.0f;
	if (true)
	{
		using rapidjson::Document;
		Document jsonDoc;
		FILE* fp = nullptr;
		const wchar_t* fileName = path.c_str();
		_wfopen_s(&fp, fileName, L"rb");//non-Windows use"r"
		if (fp != nullptr)
		{
			fseek(fp, 0, SEEK_END);
			size_t size = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			//long current = ftell(fp);
			char* readBuffer = new char[size];
			rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
			jsonDoc.ParseStream(is);
			delete[] readBuffer;
			fclose(fp);
		}

		using rapidjson::Document;

		using rapidjson::Value;
		for (Value::ConstValueIterator itr = jsonDoc.Begin(); itr != jsonDoc.End(); ++itr)
		{
			const Value& element = *itr;
			m_LevelData.blocksWide = element["Blocks"].GetInt();
			m_LevelData.tileSize = element["TileSize"].GetFloat();
			m_LevelData.baseX = element["BaseX"].GetFloat();
			m_LevelData.baseY = element["BaseY"].GetFloat();
			qbertSize = element["Size"].GetFloat();
			m_LevelData.teleportPositions = std::vector<id>();
			for (Value::ConstValueIterator posItr = element["Teleport"].Begin(); posItr != element["Teleport"].End(); ++posItr)
			{
				const Value& positions = *posItr;
				m_LevelData.teleportPositions.push_back(id{ positions["x"].GetInt(),positions["y"].GetInt() });
			}
		}
	}
	else
	{
		m_LevelData.blocksWide = 7 + 1;
		m_LevelData.tileSize = 60.0f;
		m_LevelData.baseX = 20.0f;
		m_LevelData.baseY = 450.0f;
		m_LevelData.teleportPositions = std::vector<id>{ id{0,4},id{6,3} };
	}

	m_Level = level;
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Qbert");
	

	//dae::SoundSystem* pSoundSystem = new dae::SDL_SoundSystem();
	//dae::SoundServiceLocator::SetSoundSystem(pSoundSystem);
	// Tile Init
	id maxId{1,m_LevelData.blocksWide-1};
	LoadTiles(scene, 1, false);

	//Qbert Init
	auto qbert = std::make_shared<dae::GameObject>();
	auto* qRender = new dae::RenderComponent("Qbert.png", IdToPositionConverter(maxId).x, IdToPositionConverter(maxId).y, qbertSize, qbertSize);
	qbert->AddComponent(qRender, (int)dae::componentID::render);

	auto scoreFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto scoreText = new dae::TextComponent("", scoreFont, 80, 120);
	qbert->AddComponent(scoreText, (int)dae::componentID::text);
	auto scoreObserver = new ScoreObserver();
	auto scoreSubject = new dae::Subject();
	scoreSubject->Attach(scoreObserver);
	m_ScoreSubject = scoreSubject;
	auto scoreComp = new ScoreComponent(scoreText, scoreObserver);
	m_ScoreComp = scoreComp;
	scoreObserver->AttachScoreComp(scoreComp);
	qbert->AddComponent(scoreComp,(int)expandedComponentID::score);

	auto livesFont = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);
	auto livesText = new dae::TextComponent("", livesFont, 80, 100);
	qbert->AddComponent(livesText, (int)dae::componentID::text);
	auto livesObserver = new LivesObserver();
	auto livesSubject = new dae::Subject();
	livesSubject->Attach(livesObserver);
	auto liveComp = new LivesComponent(livesText, livesObserver);
	m_LivesComp = liveComp;
	livesObserver->AttachLivesComp(liveComp);
	qbert->AddComponent(liveComp, (int)expandedComponentID::lives);

	if (gameMode == 1)
	{
		auto qbert2 = std::make_shared<dae::GameObject>();
		auto* qRender2 = new dae::RenderComponent("Qbert.png", IdToPositionConverter(maxId).x, IdToPositionConverter(maxId).y, qbertSize, qbertSize);
		qbert2->AddComponent(qRender2, (int)dae::componentID::render);

		auto* qBertComp2 = new QbertComponent(qRender2, id{maxId.y,1}, qbertSize, scoreSubject, livesSubject);
		m_Qbert = qBertComp2;
		qbert2->AddComponent(qBertComp2, (int)expandedComponentID::qbert);
		scene.Add(qbert2);

		//Qbert Commands
		auto* pLeftDown2 = new Move(qBertComp2, id{ 0, -1 });
		dae::InputManager::GetInstance().AddCommand(pLeftDown2, dae::CB::ButtonDPadDown);
		auto* pLeftUp2 = new Move(qBertComp2, id{ -1,1 });
		dae::InputManager::GetInstance().AddCommand(pLeftUp2, dae::CB::ButtonDPadLeft);
		auto* pRightDown2 = new Move(qBertComp2, id{ 1,-1 });
		dae::InputManager::GetInstance().AddCommand(pRightDown2, dae::CB::ButtonDpadRight);
		auto* pRightUp2 = new Move(qBertComp2, id{ 0,1 });
		dae::InputManager::GetInstance().AddCommand(pRightUp2, dae::CB::ButtonDPadUp);


		auto* qBertComp = new QbertComponent(qRender, id{1,1}, qbertSize, scoreSubject, livesSubject);
		m_Qbert = qBertComp;
		qbert->AddComponent(qBertComp, (int)expandedComponentID::qbert);
		scene.Add(qbert);

		//Qbert Commands
		auto* pLeftDown = new Move(qBertComp, id{ 0, -1 });
		dae::InputManager::GetInstance().AddCommand(pLeftDown, dae::CB::ButtonA);
		auto* pLeftUp = new Move(qBertComp, id{ -1,1 });
		dae::InputManager::GetInstance().AddCommand(pLeftUp, dae::CB::ButtonX);
		auto* pRightDown = new Move(qBertComp, id{ 1,-1 });
		dae::InputManager::GetInstance().AddCommand(pRightDown, dae::CB::ButtonB);
		auto* pRightUp = new Move(qBertComp, id{ 0,1 });
		dae::InputManager::GetInstance().AddCommand(pRightUp, dae::CB::ButtonY);
	}
	else
	{
		auto* qBertComp = new QbertComponent(qRender, maxId, qbertSize, scoreSubject, livesSubject);
		m_Qbert = qBertComp;
		qbert->AddComponent(qBertComp, (int)expandedComponentID::qbert);
		scene.Add(qbert);

		//Qbert Commands
		auto* pLeftDown = new Move(qBertComp, id{ 0, -1 });
		dae::InputManager::GetInstance().AddCommand(pLeftDown, dae::CB::ButtonA);
		auto* pLeftUp = new Move(qBertComp, id{ -1,1 });
		dae::InputManager::GetInstance().AddCommand(pLeftUp, dae::CB::ButtonX);
		auto* pRightDown = new Move(qBertComp, id{ 1,-1 });
		dae::InputManager::GetInstance().AddCommand(pRightDown, dae::CB::ButtonB);
		auto* pRightUp = new Move(qBertComp, id{ 0,1 });
		dae::InputManager::GetInstance().AddCommand(pRightUp, dae::CB::ButtonY);
	}

	
	auto enMan = std::make_shared<dae::GameObject>();
	auto enManComp = new EnemyManagerComponent(gameMode, scene);
	enMan->AddComponent(enManComp, (int)expandedComponentID::enemyMan);
	scene.Add(enMan);
	m_EnemyManager = enManComp;
	
	AddTeleporters(scene,m_LevelData.teleportPositions,qbertSize);

	m_ScoreComp->Reset();
}

const qbert::LevelData& qbert::LevelManager::GetLevelData() const
{
	return m_LevelData;
}

void qbert::LevelManager::AddTileComponents(dae::Scene& scene, int colorVar, float middleX, float middleY, float size, id tileId ,int activations,bool reset)
{
	auto tile = std::make_shared<dae::GameObject>();
	//tile->AddComponent(new dae::RenderComponent(color + "Cube.png", middleX - size / 2.0f, middleY - size / 2.0f, size, size), (int)dae::componentID::render);
	auto tileRenderComp = new TileRenderComponent(colorVar, middleX - size / 2.0f, middleY - size / 2.0f, size, size);
	tile->AddComponent(tileRenderComp,(int)expandedComponentID::tileRender);
	auto tileComp = new TileComponent(tileId, tileRenderComp,activations,reset);
	tile->AddComponent(tileComp, (int)expandedComponentID::tile);
	m_TileVector.push_back(tileComp);
	scene.Add(tile);
}

void qbert::LevelManager::UpdateTile(id tileId)
{
	// Can be improved
	auto it = std::find_if(m_TileVector.begin(), m_TileVector.end(),
		[&tileId](TileComponent* tile)
		{
			return tile->GetId() == tileId;
		});
	if (it != m_TileVector.end())
	{
		(*it)->GetJumpedOn();
		if (CheckCompleted())
		{
			ReloadLevel(m_Level++);
		}
	}
}

qbert::id qbert::LevelManager::GetPlayerId() const
{
	return m_Qbert->GetOldId();
}

bool qbert::LevelManager::CheckCompleted() const
{
	for(auto tile : m_TileVector)
	{
		if (!tile->IsComplete())
		{
			return false;
		}
	}
	return true;
}

void qbert::LevelManager::ReloadLevel(int level)
{
	m_Level = (level % 3) + 1;

	int activations{1};
	bool reset{false};
	if (m_Level == 2)
	{
		activations++;
	}
	if (m_Level == 3)
	{
		reset = true;
	}

	m_Qbert->Reset();
	m_EnemyManager->Reset();
	for (auto element : m_TileVector)
	{
		element->Reset(activations,reset , m_Level-1);
		m_ScoreSubject->Notify(nullptr, (int)qbertEvents::ADD_SCORE_25);
	}
	for (auto element : m_TeleporterVector)
	{
		if (element->GetAvailable())
		{
			m_ScoreSubject->Notify(nullptr, (int)qbertEvents::ADD_SCORE_50);
		}
		element->Reset();
	}
}

void qbert::LevelManager::LoadTiles(dae::Scene& scene, int activations, bool reset)
{
	position position{};
	for (int y = 1; y < m_LevelData.blocksWide; y++)
	{
		for (int x = 1; x < m_LevelData.blocksWide - y + 1; x++)
		{
			id tileId{ x,y };
			position = IdToPositionConverter(tileId);
			position.y += 0.80f * m_LevelData.tileSize;
			//position.x += 0.50f * m_LevelData.tileSize;
			AddTileComponents(scene, 2, position.x, position.y, m_LevelData.tileSize, tileId,activations,reset); // should read from file
		}
	}
}

void qbert::LevelManager::RevertTile(id tileId)
{
	auto it = std::find_if(m_TileVector.begin(), m_TileVector.end(),
		[&tileId](TileComponent* tile)
		{
			return tile->GetId() == tileId;
		});
	if (it != m_TileVector.end())
	{
		(*it)->Deactivate();
	}
}

void qbert::LevelManager::QbertDeath()
{
	ReloadLevel(0);
	m_LivesComp->Reset();
	m_ScoreComp->Reset();
}

bool qbert::LevelManager::HandleCollision(position pos, float width, float height)
{
	return m_EnemyManager->HandleCollision(pos, width, height);
}

void qbert::LevelManager::ScoreEvent(int event)
{
	m_ScoreSubject->Notify(nullptr, event);
}

void qbert::LevelManager::AddTeleporters(dae::Scene& scene, std::vector<id> positions ,float size)
{
	for (auto el : positions)
	{
		auto teleport = std::make_shared<dae::GameObject>();
		auto teleportRenderComp = new dae::RenderComponent("Teleporter.png",0.f,0.f, size, size);
		teleport->AddComponent(teleportRenderComp, (int)dae::componentID::render);
		auto teleportComp = new TeleporterComponent(el,teleportRenderComp, size);
		teleport->AddComponent(teleportComp, (int)expandedComponentID::tile);
		m_TeleporterVector.push_back(teleportComp);
		scene.Add(teleport);
	}
}

bool qbert::LevelManager::IsOnTeleport(id position)
{
	auto it = std::find_if(m_TeleporterVector.begin(), m_TeleporterVector.end(),
		[&position](TeleporterComponent* tele)
		{
			return tele->GetId() == position;
		});
	if (it != m_TeleporterVector.end())
	{
		return (*it)->GetAvailable();
	}
	return false;
}

void qbert::LevelManager::ActivateTeleport(id position)
{
	auto it = std::find_if(m_TeleporterVector.begin(), m_TeleporterVector.end(),
		[&position](TeleporterComponent* tele)
		{
			return tele->GetId() == position;
		});
	if (it != m_TeleporterVector.end())
	{
		(*it)->Activate();
	}
}

