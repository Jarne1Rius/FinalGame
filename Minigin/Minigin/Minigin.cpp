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
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include "vld.h"
#endif
#include <glm/gtc/matrix_transform.hpp>
#include <SDL_mixer.h>
#include "Shader.h"

using namespace std;
using namespace std::chrono;
int Rius::Minigin::m_Height = 600;
int Rius::Minigin::m_Width = 800;


void Rius::Minigin::Initialize()
{
	Rius::Renderer::GetInstance().Init(m_Width, m_Height);
	ResourceManager::m_ProjectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
}


void Rius::Minigin::Cleanup()
{
	delete m_Sprite;
	Renderer::GetInstance().Destroy();
	ResourceManager::Clear();
	Mix_Quit();
}

void Rius::Minigin::Run()
{
	//auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	bool doContinue = true;
	auto lastTime = std::chrono::high_resolution_clock::now();
	float lag = 0.0f;

	while (!glfwWindowShouldClose(Renderer::GetInstance().getWindow()))
	{
		Renderer::GetInstance().Input();
		const auto currentTime = high_resolution_clock::now();
		auto deltaTime = duration<float>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		doContinue = input.ProcessInput();
		int frames{ 0 };
		lag *= 1000.f;
		while (lag > MsPerFrame)
		{
			sceneManager.Update();
			lag -= MsPerFrame;
		}
		//For LateUpdate
		//m_Sprite->Update();
		sceneManager.LateUpdate();
		frames++;
		Time::UpdateTimer(deltaTime, frames);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		sceneManager.Render();
		//m_Sprite->Render();
		Renderer::GetInstance().Render();
	}
	Cleanup();
}
