#pragma once
#include <windows.h>
#include <xinput.h>

#pragma comment(lib,"XInput.lib")
#pragma comment(lib,"Xinput9_1_0.lib")
//#include <memory>
#include <vector>
#include "Command.h"


namespace dae
{
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY,
		ButtonDPadUp,
		ButtonDPadDown,
		ButtonDPadLeft,
		ButtonDpadRight,
		ButtonMax
		//todo: add the other buttons
	};

	struct CButton
	{
		CButton(ControllerButton targetButton)
		{
			button = targetButton;
			isPressed = false;
			isDown = false;
			pCommand = nullptr;
		}
		~CButton()
		{
			if (pCommand != nullptr)
			{
				delete(pCommand);
				pCommand = nullptr;
			}
		}
		ControllerButton button;
		bool isPressed;
		bool isDown;
		Command* pCommand;
	};

	class InputManager final
	{
	public:
		InputManager();
		~InputManager();
		bool ProcessInput();
		bool IsPressed(ControllerButton button) const;
		void AddCommand(Command* pNewCommand, ControllerButton cButton);

	private:

		void HandleInput(WORD wButton);
		void HandleButton(int bitmask, ControllerButton cButton, WORD wButton);
		std::vector<CButton> m_ButtonsVector;
		XINPUT_STATE* m_pInput;
	};
}