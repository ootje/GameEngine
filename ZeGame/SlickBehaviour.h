#pragma once
#include "EnemyBehaviour.h"

namespace qbert
{
	class SlickBehaviour final : public EnemyBehaviour
	{
	public:
		SlickBehaviour() = default;
		~SlickBehaviour();
		id CalculateNextMove(id currentId) const override;
	};
}

