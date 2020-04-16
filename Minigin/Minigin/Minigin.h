#pragma once
#include "SpriteSheetComponent.h"
struct SDL_Window;
namespace Rius
{
	class Minigin
	{
	public:
		void Initialize();
		void Cleanup();
		void Run();
		static int m_Width;
		static int m_Height;
	private:
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SpriteSheetComponent* m_Sprite;
	};
}