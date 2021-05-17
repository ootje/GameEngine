#include "MiniginPCH.h"
#include "SoundServiceLocator.h"

dae::NullSoundSystem dae::SoundServiceLocator::m_NullSoundSystem;
dae::SoundSystem* dae::SoundServiceLocator::m_pSoundsystem = &m_NullSoundSystem;

dae::SoundServiceLocator::~SoundServiceLocator()
{
	delete(m_pSoundsystem);
	m_pSoundsystem = nullptr;
}

void dae::SoundServiceLocator::SetSoundSystem(SoundSystem* pNewSoundSystem)
{
	m_pSoundsystem = pNewSoundSystem;
}

dae::SoundSystem& dae::SoundServiceLocator::GetSoundSystem()
{
	return *m_pSoundsystem;
}