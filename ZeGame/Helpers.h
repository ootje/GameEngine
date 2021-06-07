#pragma once
#include <memory>
#include <string>

/*
Components id
base = 0
render = 1
text = 2
 */




namespace dae {
	class GameObject;
}

namespace qbert
{
	enum class expandedComponentID
	{
		tile = 5,
		tileRender = 6,
		qbert = 7,
		score = 8,
		lives = 9,
		enemyComp = 10,
		enemyMan = 11,
	};

	enum class qbertEvents
	{
		ADD_SCORE_25 = 1,
		ADD_SCORE_50 = 2,
		ADD_SCORE_300 = 3,
		ADD_SCORE_500 = 4,
		LOSE_LIFE = 5
	};
	
	struct id
	{
		int x;
		int y;
		bool operator==(const id& other) const
		{
			return (x == other.x) && (y == other.y);
		}
		bool operator<(const id& other) const
		{
			if (y > other.y)
			{
				return false;
			}
			if (y < other.y)
			{
				return true;
			}
			return x < other.x;
		}
	};

	struct position
	{
		float x;
		float y;

		/*inline position operator+(position&& other) const
		{
			position output{ 0,0 };
			output.x = x + other.x;
			output.y = y + other.y;
			return output;
		}*/
	};
	
	position IdToPositionConverter(id testId);

	bool IsValidIdPosition(id id);
	bool IsValidIdPositionEnemy(id id);

	bool IsOnTeleport(id id);
}
