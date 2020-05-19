#pragma once
#include "SpriteSheetComponent.h"
#include "UndoSystem.h"
#include "FiniteStateMachine.h"
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
		static float m_TileHeight;
		static float m_TileWidth;
		static int m_Height;
		static UndoSystem m_UndoSystem;
		//static FiniteStateMachine* m_FSM;
	private:
		void StartViewEngine();
		void ShowAllComponents();
		static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
		SpriteSheetComponent* m_Sprite;
		
	};
}