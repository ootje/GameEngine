#pragma once
#include "EnemyBehaviour.h"

namespace qbert
{
	class CoilyBehaviour final : public EnemyBehaviour
	{
	public:
		CoilyBehaviour();
		~CoilyBehaviour() override;
		id CalculateNextMove(id currentId) const override;
	private:
		bool m_HasTransformed;
	};
}

