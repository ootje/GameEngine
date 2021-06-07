#pragma once
#include "EnemyBehaviour.h"

namespace qbert
{
	class UggBehaviour final :public EnemyBehaviour
	{
	public:
		UggBehaviour(bool moveLeftUp);
		~UggBehaviour();
		id CalculateNextMove(id currentId) override;
		int EventOnDeath() override;
	private:
		bool m_MoveUpLeft;//if false moverightup
	};
}

