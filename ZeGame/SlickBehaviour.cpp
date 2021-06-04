#include "SlickBehaviour.h"

qbert::SlickBehaviour::~SlickBehaviour()
{
	
}

qbert::id qbert::SlickBehaviour::CalculateNextMove(id currentId) const
{
	id output = currentId;
	bool isRightDown = bool(rand() % 1);
	output.y -= 1;
	if (isRightDown)
	{
		output.x += 1;
	}
	return output;
}

