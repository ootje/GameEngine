#include "MiniginPCH.h"
#include "SoundServiceLocator.h"

NullSoundSystem SoundServiceLocator::m_NullSoundSystem;
SoundSystem* SoundServiceLocator::m_pSoundsystem = &m_NullSoundSystem;

SoundServiceLocator::~SoundServiceLocator()
{
	delete(m_pSoundsystem);
	m_pSoundsystem = nullptr;
}

void SoundServiceLocator::SetSoundSystem(SoundSystem* pNewSoundSystem)
{
	m_pSoundsystem = pNewSoundSystem;
}
SoundSystem& SoundServiceLocator::GetSoundSystem()
{
	return *m_pSoundsystem;
}