#pragma once
#include "Singleton.h"

namespace dae
{
	class InputManager_Impl;
	class Command;
	
	enum class CB
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonStart,
		ButtonBack,
		ButtonLeftThumb,
		ButtonRightThumb,
		ButtonDPadUp,
		ButtonDPadDown,
		ButtonDPadLeft,
		ButtonDpadRight,
		ButtonLeftShoulder,
		ButtonRightShoulder
	};
	
	class InputManager final : public Singleton<InputManager>
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		bool IsPressed(CB button) const;
		void AddCommand(Command* pNewCommand, CB cButton);

	private:
		friend class Singleton<InputManager>;
		InputManager_Impl* m_Impl;
		
	};
}
