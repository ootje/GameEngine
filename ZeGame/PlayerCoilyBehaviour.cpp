#include "PlayerCoilyBehaviour.h"

#include "LevelManager.h"
#include "../SDL2/include/SDL.h"

qbert::PlayerCoilyBehaviour::PlayerCoilyBehaviour()
	:m_HasTransformed(false)
{
	SDL_Init(SDL_INIT_VIDEO);
}

qbert::id qbert::PlayerCoilyBehaviour::CalculateNextMove(id currentId)
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
		SDL_Event e;
		while (SDL_PollEvent(&e))
		{
		}
		const Uint8* pStates = SDL_GetKeyboardState(nullptr);
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			return id{ currentId.x + 1,currentId.y - 1 };
		}
		else if (pStates[SDL_SCANCODE_UP])
		{
			return id{ currentId.x,currentId.y + 1 };
		}
		else if (pStates[SDL_SCANCODE_DOWN])
		{
			return id{ currentId.x,currentId.y - 1 };
		}
		else if (pStates[SDL_SCANCODE_LEFT])
		{
			return id{ currentId.x - 1,currentId.y + 1 };
		}
	}
	return output;
}

int qbert::PlayerCoilyBehaviour::EventOnDeath()
{
    return (int)qbertEvents::ADD_SCORE_500;
}
