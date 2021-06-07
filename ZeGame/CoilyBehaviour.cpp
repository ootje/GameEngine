#include "CoilyBehaviour.h"

#include "LevelManager.h"


qbert::CoilyBehaviour::CoilyBehaviour()
	:m_HasTransformed(false)
{
	
}

qbert::CoilyBehaviour::~CoilyBehaviour()
{
	
}

qbert::id qbert::CoilyBehaviour::CalculateNextMove(id currentId)
{
	id output = currentId;
	if (!m_HasTransformed)
	{
		if (currentId.y == 1)
		{
			m_HasTransformed = true;
			return output;
		}
		bool isRightDown = bool(rand() % 2);
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

int qbert::CoilyBehaviour::EventOnDeath()
{
	return (int)qbertEvents::ADD_SCORE_500;
}

