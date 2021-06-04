#include "CoilyBehaviour.h"

#include "LevelManager.h"


qbert::CoilyBehaviour::CoilyBehaviour()
	:m_HasTransformed(false)
{
	
}

qbert::CoilyBehaviour::~CoilyBehaviour()
{
	
}

qbert::id qbert::CoilyBehaviour::CalculateNextMove(id currentId) const
{
	id output = currentId;
	if (!m_HasTransformed)
	{
		bool isRightDown = bool(rand() % 1);
		output.y -= 1;
		if (isRightDown)
		{
			output.x += 1;
		}
	}
	else
	{
		id qbertPos = LevelManager::GetInstance().GetPlayerId();
		if (qbertPos.y < currentId.y)
		{
			//Move Down
			output.y -= 1;
			if (qbertPos.x > currentId.x)
			{
				output.x += 1;
			}
		}
		else
		{
			//Move Up
			output.y += 1;
			if (qbertPos.x < currentId.x)
			{
				output.x -= 1;
			}
		}
	}

	
	return output;
}


