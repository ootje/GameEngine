#include "EnemyManagerComponent.h"

#include "EnemyComponent.h"
#include <RenderComponent.h>
#include <GameObject.h>

#include "CoilyBehaviour.h"
#include "LevelManager.h"
#include "PlayerCoilyBehaviour.h"
#include "SlickBehaviour.h"
#include "UggBehaviour.h"

qbert::EnemyManagerComponent::EnemyManagerComponent(const std::string& fileName, dae::Scene& scene)
{
	m_Elapsed = 0.0f;
	m_Duration = 5.0f;
	m_InactiveEnemy = true;
	
	std::string temp = fileName;
	const float size = 40.f;
	const LevelData& data = LevelManager::GetInstance().GetLevelData();
	m_Enemies = std::vector<EnemyComponent*>();
	
	auto ugg = std::make_shared<dae::GameObject>();
	auto uggRender = new dae::RenderComponent("Ugg.png", 0.0f, 0.0f, size, size);
	ugg->AddComponent(uggRender, (int)dae::componentID::render);
	auto uggBehav = new UggBehaviour(false);
	auto uggComp = new EnemyComponent(id{ 1,1 }, size, uggBehav, uggRender, true);
	ugg->AddComponent( uggComp,(int)expandedComponentID::enemyComp);
	scene.Add(ugg);
	m_Enemies.push_back(uggComp);

	auto wrong = std::make_shared<dae::GameObject>();
	auto wrongRender = new dae::RenderComponent("Ugg.png", 0.f, 0.f, size, size);
	wrong->AddComponent(wrongRender, (int)dae::componentID::render);
	auto wrongBeh = new UggBehaviour(true);
	auto wrongComp = new EnemyComponent(id{ data.blocksWide - 1,1 }, size, wrongBeh, wrongRender, true);
	wrong->AddComponent(wrongComp, (int)expandedComponentID::enemyComp);
	scene.Add(wrong);
	m_Enemies.push_back(wrongComp);

	auto slick = std::make_shared<dae::GameObject>();
	auto slickRender = new dae::RenderComponent("Slick.png", 0.f, 0.f, size, size);
	slick->AddComponent(slickRender, (int)dae::componentID::render);
	auto slickBeh = new SlickBehaviour();
	auto slickComp = new EnemyComponent(id{ 1,data.blocksWide - 1 }, size, slickBeh, slickRender, false, true);
	slick->AddComponent(slickComp, (int)expandedComponentID::enemyComp);
	scene.Add(slick);
	m_Enemies.push_back(slickComp);

	auto sam = std::make_shared<dae::GameObject>();
	auto samRender = new dae::RenderComponent("Sam.png", 0.f, 0.f, size, size);
	sam->AddComponent(samRender, (int)dae::componentID::render);
	auto samBeh = new SlickBehaviour();
	auto samComp = new EnemyComponent(id{ 1,data.blocksWide - 1 }, size, samBeh, samRender, false,true);
	sam->AddComponent(samComp, (int)expandedComponentID::enemyComp);
	scene.Add(sam);
	m_Enemies.push_back(samComp);

	auto coily = std::make_shared<dae::GameObject>();
	auto coilyRender = new dae::RenderComponent("Coily.png", 0.f, 0.f, size, size);
	coily->AddComponent(coilyRender, (int)dae::componentID::render);
	EnemyBehaviour* coilyBeh = nullptr;
	if (true)
	{
		coilyBeh = new CoilyBehaviour();
	}
	else
	{
		coilyBeh = new PlayerCoilyBehaviour();
	}
	auto coilyComp = new EnemyComponent(id{ 1,data.blocksWide - 1 }, size, coilyBeh, coilyRender, true);
	coily->AddComponent(coilyComp, (int)expandedComponentID::enemyComp);
	scene.Add(coily);
	m_Enemies.push_back(coilyComp);


	for (auto el : m_Enemies)
	{
		el->Deactivate();
	}
}

qbert::EnemyManagerComponent::~EnemyManagerComponent()
{
	
}

void qbert::EnemyManagerComponent::Update(float dt)
{
	if (m_InactiveEnemy)
	{
		m_Elapsed += dt;
		if (m_Elapsed >= m_Duration)
		{
			m_Elapsed = 0.0f;
			m_InactiveEnemy = false;
			std::vector<int> randomEnemy{};
			for (int i = 0; i < (int)m_Enemies.size(); i++)
			{
				if (!m_Enemies[i]->GetIsActive())
				{
					randomEnemy.push_back(i);
				}
			}
			if (randomEnemy.size() == 0)
			{
				return;
			}
			int ran = rand() % (randomEnemy.size());
			m_Enemies[randomEnemy[ran]]->Activate();
		}
	}
	else
	{
		for (int i = 0; i < (int)m_Enemies.size(); i++)
		{
			if (!m_Enemies[i]->GetIsActive())
			{
				m_InactiveEnemy = true;
				m_Elapsed = 0.0f;
			}
		}
	}
}

bool qbert::EnemyManagerComponent::HandleCollision(position pos, float width, float height)
{
	for (auto comp : m_Enemies)
	{
		if (comp->HandleColision(pos, width, height))
		{
			return true;
		}
	}
	return false;
}

void qbert::EnemyManagerComponent::Reset()
{
	for (auto element : m_Enemies)
	{
		element->Deactivate();
	}
}


