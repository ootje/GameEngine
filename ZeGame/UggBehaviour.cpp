#include "UggBehaviour.h"

qbert::UggBehaviour::UggBehaviour(bool moveLeftUp)
	:m_MoveUpLeft(moveLeftUp)
{
	
}

qbert::UggBehaviour::~UggBehaviour()
{
	
}

qbert::id qbert::UggBehaviour::CalculateNextMove(id currentId) const
{
	id output = currentId;
	bool isXorY = bool(rand() % 1);
	if (isXorY)
	{
		//X
		if (m_MoveUpLeft)
		{
			output.x -= 1;
		}
		else
		{
			output.x += 1;
		}
	}
	else
	{
		//Y
		if (m_MoveUpLeft)
		{
			output.x -= 1;
			output.y += 1;
		}
		else
		{
			output.y += 1;
		}
	}
	
	return output;
}
