#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "GameObject.h"
#include "Scene.h"
#include "time.h"

#include "TextComponent.h"
#include "TextureComponent.h"

using namespace std;
using namespace std::chrono;


void Rius::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr)
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

	ResourceManager::GetInstance().Init("../Data/");
}


void Rius::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Rius::Minigin::Run()
{
	auto& time = Time::GetInstance();
	auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;
	
	while (doContinue)
	{
		const auto currentTime = high_resolution_clock::now();
		auto deltaTime = duration<float>(currentTime - lastTime).count() ;
		lastTime = currentTime;
		lag += deltaTime;
		doContinue = input.ProcessInput();
		int frames{0};
		lag *= 1000.f;
		while (lag > MsPerFrame)
		{
			sceneManager.Update();
			lag -= MsPerFrame;
		}
		frames++;
		time.UpdateTimer(deltaTime, frames);
		renderer.Render();
	}

	Cleanup();
}
