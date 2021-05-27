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
		qbert = 6,
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
	
	position IdToPositionConverter(int id);

	bool IsValidIdPosition(int id);
	bool IsOnTeleport(int id);
}
