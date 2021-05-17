#pragma once

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
		ButtonRightShoulder,
		ButtonMax
		//todo: add the other buttons
	};
	
	class InputManager final
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		bool IsPressed(CB button) const;
		void AddCommand(Command* pNewCommand, CB cButton);

	private:
		InputManager_Impl* m_Impl;
		
	};
}