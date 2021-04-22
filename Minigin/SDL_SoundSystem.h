#pragma once
#include <mutex>
#include <queue>
#include <thread>

#include "SoundSystem.h"


class SDL_Sound final
{
public:
	explicit SDL_Sound(const std::string& path, int volume);
	void Play();
private:
	std::string m_Path;
	int m_Volume;
};


class SDL_SoundSystem final : public SoundSystem
{
public:
	explicit SDL_SoundSystem();
	~SDL_SoundSystem() override;
	void Update() override;
	void PlaySound(const std::string& path, int volume) override;
	void SetMuted(bool isMuted = true) override;

	SDL_SoundSystem(SDL_SoundSystem const& other) = delete;
	SDL_SoundSystem& operator=(SDL_SoundSystem const& other) = delete;
	SDL_SoundSystem(SDL_SoundSystem&& other) = delete;
	SDL_SoundSystem& operator=(SDL_SoundSystem&& other) = delete;

private:
	std::queue<SDL_Sound> m_PlayQue;
	std::thread m_SoundThread;
	std::condition_variable m_Condition;
	
	std::mutex m_Mutex;

	bool m_Muted;
};