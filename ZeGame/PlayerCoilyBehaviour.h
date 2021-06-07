#pragma once
#include "EnemyBehaviour.h"

namespace qbert
{
	class PlayerCoilyBehaviour final : public EnemyBehaviour
	{
	public:
		PlayerCoilyBehaviour();
		~PlayerCoilyBehaviour(){};
		id CalculateNextMove(id currentId) override;
		int EventOnDeath() override;
	private:
		bool m_HasTransformed;
	};
}

