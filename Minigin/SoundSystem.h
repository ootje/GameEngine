#pragma once

class SoundSystem
{
public:
	SoundSystem() = default;
	virtual ~SoundSystem() = default;

	virtual void Update() = 0;
	virtual void PlaySound(const std::string& path, int volume) = 0;
	virtual void SetMuted(bool isMuted = true) = 0;
	
	SoundSystem(SoundSystem const& other) = delete;
	SoundSystem& operator=(SoundSystem const& other) = delete;
	SoundSystem(SoundSystem&& other) = delete;
	SoundSystem& operator=(SoundSystem&& other) = delete;
};

class NullSoundSystem final : public SoundSystem
{
public:
	NullSoundSystem() = default;
	~NullSoundSystem() = default;

	void Update() override {};
	void PlaySound(const std::string &, int) override {};
	void SetMuted(bool = true) override {};

	NullSoundSystem(NullSoundSystem const& other) = delete;
	NullSoundSystem& operator=(NullSoundSystem const& other) = delete;
	NullSoundSystem(NullSoundSystem&& other) = delete;
	NullSoundSystem& operator=(NullSoundSystem&& other) = delete;
};
