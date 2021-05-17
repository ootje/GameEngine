#pragma once
#include <iostream>
#include "Qbert.h"
#include "SoundSystem.h"

namespace dae
{
	class Command
	{
	public:
		Command() {};
		virtual ~Command() {};
		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};
}

	/*class Die final : public Command
	{
	public:
		Die(Qbert* qbert) { qBert = qbert; };
		~Die() override {};
		void Undo() override {};
		void Execute() override
		{
			qBert->Die();
		}
	private:
		Qbert* qBert;
	};

	class Point25 final : public Command
	{
	public:
		Point25(Qbert* qbert) { qBert = qbert; };
		~Point25() override {};
		void Undo() override {};
		void Execute() override
		{
			qBert->GetPoint();
		}
	private:
		Qbert* qBert;
	};

	class BasicSound final : public Command
	{
	public:
		BasicSound(SoundSystem* pSoundSystem) { m_pSoundSystem = pSoundSystem; };
		~BasicSound() override {};
		void Undo() override {};
		void Execute() override
		{
			m_pSoundSystem->PlaySound("../Data/door1.wav",50);
		}
	private:
		SoundSystem* m_pSoundSystem;
	};
}*/
