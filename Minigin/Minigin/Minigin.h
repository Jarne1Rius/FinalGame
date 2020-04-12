#pragma once
#include "SpriteRenderer.h"
struct SDL_Window;
namespace Rius
{
	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SpriteRenderer* m_Sprite;
	};
}