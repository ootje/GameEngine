#include "MiniginPCH.h"
#include "InputManager.h"

dae::InputManager::InputManager()
{
	for (int i = 0; i < (int)ControllerButton::ButtonMax; i++)
	{
		m_ButtonsVector.push_back(CButton(ControllerButton(i)));
	}
	m_pInput = new XINPUT_STATE();
}

dae::InputManager::~InputManager()
{
	delete(m_pInput);
}

bool dae::InputManager::ProcessInput()
{
	// todo: read the input
	if (XInputGetState(0, m_pInput) == ERROR_DEVICE_NOT_CONNECTED)
	{
		//return;
	}
	WORD wButtons = m_pInput->Gamepad.wButtons;
	InputManager::HandleInput(wButtons);

	return !IsPressed(ControllerButton::ButtonX);
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	auto iterator = std::find_if(m_ButtonsVector.begin(), m_ButtonsVector.end(), [&button](const CButton& targetButton) {return targetButton.button == button; });
	return iterator->isPressed;
}

void dae::InputManager::AddCommand(Command* pNewCommand, ControllerButton cButton)
{
	auto iterator = std::find_if(m_ButtonsVector.begin(), m_ButtonsVector.end(), [&cButton](const CButton& targetButton) {return targetButton.button == cButton; });
	iterator->pCommand = pNewCommand;
}

void dae::InputManager::HandleInput(WORD wButton)
{
	InputManager::HandleButton(XINPUT_GAMEPAD_A, ControllerButton::ButtonA, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_B, ControllerButton::ButtonB, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_X, ControllerButton::ButtonX, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_Y, ControllerButton::ButtonY, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_DPAD_RIGHT, ControllerButton::ButtonDpadRight, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_DPAD_LEFT, ControllerButton::ButtonDPadLeft, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_DPAD_UP, ControllerButton::ButtonDPadUp, wButton);
	InputManager::HandleButton(XINPUT_GAMEPAD_DPAD_DOWN, ControllerButton::ButtonDPadDown, wButton);

	for (int i = 0; i < (int)ControllerButton::ButtonMax; i++)
	{
		if (m_ButtonsVector[i].isPressed)
		{
			if (m_ButtonsVector[i].pCommand != nullptr)
			{
				m_ButtonsVector[i].pCommand->Execute();
			}
		}
	}
}

void dae::InputManager::HandleButton(int bitmask, ControllerButton cButton, WORD wButton)
{
	if ((bitmask & wButton) != 0)
	{
		if (m_ButtonsVector[int(cButton)].isPressed || m_ButtonsVector[int(cButton)].isDown)
		{
			if (m_ButtonsVector[int(cButton)].isPressed)
			{
				m_ButtonsVector[int(cButton)].isDown = true;
				m_ButtonsVector[int(cButton)].isPressed = false;
			}
		}
		else
		{
			m_ButtonsVector[int(cButton)].isPressed = true;
		}
	}
	else
	{
		m_ButtonsVector[int(cButton)].isPressed = false;
		m_ButtonsVector[int(cButton)].isDown = false;
	}
}

//bool dae::InputManager::IsPressed(ControllerButton button) const
//{
//	WORD wButton = XINPUT_GAMEPAD_A;
//	
//	// todo: return whether the given button is pressed or not.
//	switch (button)
//	{
//	case dae::ControllerButton::ButtonA:
//		wButton = XINPUT_GAMEPAD_A;
//		break;
//	case dae::ControllerButton::ButtonB:
//		wButton = XINPUT_GAMEPAD_B;
//		break;
//	case dae::ControllerButton::ButtonX:
//		wButton = XINPUT_GAMEPAD_X;
//		break;
//	case dae::ControllerButton::ButtonY:
//		wButton = XINPUT_GAMEPAD_Y;
//		break;
//	default:
//		break;
//	}
//
//	bool result = (m_WordButtons & wButton) != 0;
//	return result;
//}
