#pragma once
#include <memory>
#include <vector>

#include "Singleton.h"


namespace dae {
	class GameObject;
}

namespace qbert
{
	class LevelManager final : public dae::Singleton<LevelManager>
	{
	public:
		void LoadLevel();


	private:
		friend class Singleton<LevelManager>;
		LevelManager() = default;
		
		std::vector<std::shared_ptr<dae::GameObject>> m_TileVector;
	};

}
