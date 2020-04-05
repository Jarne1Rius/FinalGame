#include "MiniginPCH.h"
#include "Audio.h"

namespace Rius
{

	Audio::Audio(int loops)
		:m_Loops{ loops }
	{

	}


	//Effect
	SoundEffect::SoundEffect(std::string& fileName, int loops)
		:Audio(loops), m_ChannelInUse(-1)
	{
		m_Effect = Mix_LoadWAV(fileName.c_str());
		if (m_Effect == nullptr) printf("Failed to load Effect! SDL_mixer Error: %s\n", Mix_GetError());
	}

	SoundEffect::~SoundEffect()
	{
		StopSound();
		Mix_FreeChunk(m_Effect);
		m_Effect = nullptr;
	}

	void SoundEffect::PlaySound()
	{
		m_ChannelInUse = Mix_PlayChannel(-1, m_Effect, 0);
	}

	void SoundEffect::StopSound()
	{

		Mix_HaltChannel(m_ChannelInUse);
	}

	void SoundEffect::ResumePauseSound()
	{
		if (Mix_Playing(m_ChannelInUse) == 1)
			Mix_Resume(m_ChannelInUse);
		else
			Mix_Pause(m_ChannelInUse);
	}

	void SoundEffect::SetVolume(int addVolume)
	{
		if (m_ChannelInUse != -1)
		{
			m_Volume += addVolume;
			Mix_Volume(m_ChannelInUse, m_Volume);
		}
		else
			printf("NoChannel \n");
	}

	//BackGround

	BackGroundMusic::BackGroundMusic(std::string& fileName, int loops, bool fade, int msFade)
		:Audio(loops), m_Fade(fade), m_MsFade(msFade)
	{
		m_Music = Mix_LoadMUS(fileName.c_str());
		if (m_Music == nullptr) printf("Failed to load sound!SDL_mixer Error: %s\n", Mix_GetError());
	}

	BackGroundMusic::~BackGroundMusic()
	{
		StopSound();
		Mix_FreeMusic(m_Music);
		m_Music = nullptr;
	}

	void BackGroundMusic::PlaySound()
	{
		if (Mix_PlayingMusic() == 0)
		{
			if (m_Fade) Mix_FadeInMusic(m_Music, m_Loops, m_MsFade);
			else Mix_PlayMusic(m_Music, m_Loops);

		}
	}

	void BackGroundMusic::StopSound()
	{
		Mix_HaltMusic();
	}

	void BackGroundMusic::ResumePauseSound()
	{
		if (Mix_PausedMusic() == 1)
		{
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			Mix_PauseMusic();
		}

	}

	void BackGroundMusic::SetVolume(int addVolume)
	{
	}


}
