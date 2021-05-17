#include "LevelManager.h"


#include "SceneManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "Helpers.h"


void qbert::LevelManager::LoadLevel()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Qbert");

	const float size = 60.0f;
	const int startingWidth = 7;
	position basePosition{ 20.0f,400.0f };
	position offsetPosition = basePosition;
	for (int width = 0; width < startingWidth; width++)
	{
		for (int i = 0; i < startingWidth-width; i++)
		{
			auto tile = std::make_shared<dae::GameObject>();
			qbert::AddTileComponents(tile, "Orange", offsetPosition.x, offsetPosition.y, size, width,i); // should read from file

			m_TileVector.push_back(tile);
			scene.Add(tile);
			offsetPosition.x += 30.f/35.f*size;
		}
		basePosition.x += 30.f/70.f*size;
		basePosition.y -= 0.75f*size;
		offsetPosition = basePosition;
	}
}

