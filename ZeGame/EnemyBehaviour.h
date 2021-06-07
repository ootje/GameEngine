#pragma once
#include "Helpers.h"

namespace qbert
{
	class EnemyBehaviour
	{
	public:
		EnemyBehaviour() = default;
		virtual ~EnemyBehaviour() {};
		virtual id CalculateNextMove(id currentId) = 0;
		virtual int EventOnDeath() = 0;
	};
}

