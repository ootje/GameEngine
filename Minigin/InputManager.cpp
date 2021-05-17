#include "MiniginPCH.h"
#include "InputManager.h"

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
		ButtonA = XINPUT_GAMEPAD_A,
		ButtonB = XINPUT_GAMEPAD_B,
		ButtonX = XINPUT_GAMEPAD_X,
		ButtonY = XINPUT_GAMEPAD_Y,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonBack = XINPUT_GAMEPAD_BACK,
		ButtonLeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
		ButtonRightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
		ButtonDPadUp = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDPadDown = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonDPadLeft = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonDpadRight = XINPUT_GAMEPAD_DPAD_RIGHT,
		ButtonLeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		ButtonMax
	};

	ControllerButton static ConvertFromCB(CB button)
	{
		switch (button)
		{
		case CB::ButtonA:
			return ControllerButton::ButtonA;
		case CB::ButtonB:
			return ControllerButton::ButtonB;
		case CB::ButtonX:
			return ControllerButton::ButtonX;
		case CB::ButtonY:
			return ControllerButton::ButtonY;
		case CB::ButtonDPadUp:
			return ControllerButton::ButtonDPadUp;
		case CB::ButtonDPadDown:
			return ControllerButton::ButtonDPadDown;
		case CB::ButtonDPadLeft:
			return ControllerButton::ButtonDPadLeft;
		case CB::ButtonDpadRight:
			return ControllerButton::ButtonDpadRight;
		case CB::ButtonRightShoulder:
			return ControllerButton::ButtonRightShoulder;
		case CB::ButtonRightThumb:
			return ControllerButton::ButtonRightThumb;
		case CB::ButtonLeftShoulder:
			return ControllerButton::ButtonLeftShoulder;
		case CB::ButtonLeftThumb:
			return ControllerButton::ButtonLeftThumb;
		case CB::ButtonStart:
			return ControllerButton::ButtonStart;
		case CB::ButtonBack:
			return ControllerButton::ButtonBack;
		default:
			return ControllerButton::ButtonMax;
		}
	}

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

	class InputManager_Impl final
	{
	public:
		InputManager_Impl()
		{
			int i = (int)ControllerButton::ButtonY;
			while (true)
			{
				i = (int)ControllerButton(i >> 1);
				if (i == 0X0400 || i == 0x0800)
				{
					continue;
				}
				m_ButtonsVector.push_back(CButton(ControllerButton(i)));
				if (i == 1)
				{
					break;
				}
			}

			m_pInput = new XINPUT_STATE();
		}
		~InputManager_Impl()
		{
			delete(m_pInput);
		}
		bool ProcessInput()
		{
			// todo: read the input
			if (XInputGetState(0, m_pInput) == ERROR_DEVICE_NOT_CONNECTED)
			{
				//return;
			}
			WORD wButtons = m_pInput->Gamepad.wButtons;
			HandleInput(wButtons);

			return !IsPressed(ControllerButton::ButtonBack);
		}
		bool IsPressed(ControllerButton button) const
		{
			auto iterator = std::find_if(m_ButtonsVector.begin(), m_ButtonsVector.end(), [&button](const CButton& targetButton) {return targetButton.button == button; });
			return iterator->isPressed;
		}
		void AddCommand(Command* pNewCommand, ControllerButton cButton)
		{
			auto iterator = std::find_if(m_ButtonsVector.begin(), m_ButtonsVector.end(), [&cButton](const CButton& targetButton) {return targetButton.button == cButton; });
			iterator->pCommand = pNewCommand;
		}
	private:
		void HandleInput(WORD wButton)
		{
			for (auto& element : m_ButtonsVector)
			{
				HandleButton(element, wButton);
				if (element.isPressed)
				{
					if (element.pCommand != nullptr)
					{
						element.pCommand->Execute();
					}
				}
			}
		}
		void HandleButton(CButton& cButton, WORD wButton)
		{
			if (((int)cButton.button & wButton) != 0)
			{
				if (cButton.isPressed || cButton.isDown)
				{
					if (cButton.isPressed)
					{
						cButton.isDown = true;
						cButton.isPressed = false;
					}
				}
				else
				{
					cButton.isPressed = true;
				}
			}
			else
			{
				cButton.isPressed = false;
				cButton.isDown = false;
			}
		}
		
		std::vector<CButton> m_ButtonsVector;
		XINPUT_STATE* m_pInput;
	};
}

dae::InputManager::InputManager()
{
	m_Impl = new InputManager_Impl();
}

dae::InputManager::~InputManager()
{
	delete(m_Impl);
}
bool dae::InputManager::ProcessInput()
{
	return m_Impl->ProcessInput();
}
bool dae::InputManager::IsPressed(CB button) const
{
	return m_Impl->IsPressed(ConvertFromCB(button));
}
void dae::InputManager::AddCommand(Command* pNewCommand, CB cButton)
{
	m_Impl->AddCommand(pNewCommand, ConvertFromCB(cButton));
}
