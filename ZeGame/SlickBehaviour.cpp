#include "SlickBehaviour.h"

qbert::SlickBehaviour::~SlickBehaviour()
{
	
}

qbert::id qbert::SlickBehaviour::CalculateNextMove(id currentId) 
{
	id output = currentId;
	bool isRightDown = bool(rand() % 2);
	output.y -= 1;
	if (isRightDown)
	{
		output.x += 1;
	}
	return output;
}

int qbert::SlickBehaviour::EventOnDeath()
{
	return (int)qbertEvents::ADD_SCORE_300;
}

