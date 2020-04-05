#pragma once
#include "SDL_audio.h"
#include  "SDL_mixer.h"

namespace Rius
{

	class Audio
	{
	public:
		Audio(int loops);
		virtual ~Audio() = default;
		virtual void PlaySound() = 0;
		virtual void StopSound() = 0;
		virtual void ResumePauseSound() = 0;
		virtual void SetVolume(int addVolume) = 0;
	protected:
		int m_Volume = 128;
		int m_Loops = -1;
	};

	class SoundEffect : public Audio
	{
	public:
		SoundEffect(std::string& fileName, int loops);
		~SoundEffect();
		void PlaySound() override;
		void StopSound() override;
		void ResumePauseSound() override;
		void SetVolume(int addVolume) override;
	private:
		int m_ChannelInUse;
		Mix_Chunk* m_Effect;
	};

	class BackGroundMusic : public Audio
	{
	public:
		BackGroundMusic(std::string& fileName, int loops = -1, bool fade = false, int msFade = 0);
		~BackGroundMusic();
		void PlaySound() override;
		void StopSound() override;
		void ResumePauseSound() override;
		void SetVolume(int addVolume) override;
	private:
		Mix_Music* m_Music;
		bool m_Fade;
		int m_MsFade;
	};



}