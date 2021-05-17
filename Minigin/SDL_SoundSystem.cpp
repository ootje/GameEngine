#include "MiniginPCH.h"
#include "SDL_SoundSystem.h"
//#include <SDL.h>
#include "audio.h"
#include "audio.c"

dae::SDL_Sound::SDL_Sound(const std::string& path, int volume)
	:m_Path(path)
	, m_Volume(volume)
{
}
void dae::SDL_Sound::Play()
{
	playSound(m_Path.c_str(), m_Volume);
}


dae::SDL_SoundSystem::SDL_SoundSystem()
	:m_Mutex{}
{
	m_PlayQue = std::queue<SDL_Sound>();
	m_SoundThread = std::thread([this] {Update(); });
	m_Muted = false;
	initAudio();
}
dae::SDL_SoundSystem::~SDL_SoundSystem()
{
	if (m_SoundThread.joinable())
	{
		m_SoundThread.join();
	}
}
void dae::SDL_SoundSystem::Update()
{
	do
	{
		std::unique_lock<std::mutex> lock{ m_Mutex };
		if (m_PlayQue.empty())
		{
			m_Condition.wait(lock);
		}
		SDL_Sound sound = m_PlayQue.front();
		m_PlayQue.pop();
		sound.Play();
	} while (true);//!m_PlayQue.empty());
}
void dae::SDL_SoundSystem::PlaySound(const std::string& path, int volume)
{
	SDL_Sound newSound = SDL_Sound(path, volume);
	std::lock_guard<std::mutex> lock{ m_Mutex };
	m_PlayQue.push(newSound);
	m_Condition.notify_one();
}

void dae::SDL_SoundSystem::SetMuted(bool isMuted)
{
	m_Muted = isMuted;
}