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


void Rius::Minigin::Initialize()
{
	
	//m_Sprite = new SpriteRenderer(a);
	Rius::Renderer::GetInstance().Init(800, 600);
	Rius::ResourceManager::GetInstance().LoadShader("Shader/SpriteTexture.vs", "Shader/SpriteTexture.fs", "Sprite");
	glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(800), static_cast<GLfloat>(600), 0.0f, -1.0f, 1.0f);
	Rius::ResourceManager::GetInstance().GetShader("Sprite")->Use().SetInt("image", 0);
	Rius::ResourceManager::GetInstance().GetShader("Sprite")->SetMat4("projection", projection);

	Rius::Texture2D* texture = Rius::ResourceManager::GetInstance().LoadTexture("Resources/awesomeface.png", GL_FALSE, "BackGround");
	Rius::Shader* a = Rius::ResourceManager::GetInstance().GetShader("Sprite");

	m_Sprite = new Rius::SpriteRenderer(a, Rius::Rectangle2D(0, 0, 100, 100), Rius::Rectangle2D(0, 0, 1,1));
	m_Sprite->SetTexture(texture);
}


void Rius::Minigin::Cleanup()
{
	delete m_Sprite;
	Renderer::GetInstance().Destroy();
	ResourceManager::GetInstance().Clear();
	Mix_Quit();
}

void Rius::Minigin::Run()
{
	auto& time = Time::GetInstance();
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		sceneManager.Render();
		Texture2D* texture = ResourceManager::GetInstance().GetTexture("BackGround");
		m_Sprite->Render();
		Renderer::GetInstance().Render();
	}
	Cleanup();
}
