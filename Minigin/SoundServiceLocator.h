#pragma once
#include "SoundSystem.h"


class SoundServiceLocator final
{
	static SoundSystem* m_pSoundsystem;
	static NullSoundSystem m_NullSoundSystem;
	
public:
	static void SetSoundSystem(SoundSystem* pNewSoundSystem);
	static SoundSystem& GetSoundSystem();

	~SoundServiceLocator();
};

