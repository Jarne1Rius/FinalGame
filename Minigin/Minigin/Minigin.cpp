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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "UndoSystem.h"
using namespace std;
using namespace std::chrono;
int Rius::Minigin::m_Height = 720;
int Rius::Minigin::m_Width = 1280;


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
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
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
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

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
		//sceneManager.Render();
		//m_Sprite->Render();

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
		StartViewEngine();
		//if (show_demo_window)
		//	ImGui::ShowDemoWindow(&show_demo_window);

		//static float f = 0.0f;
		//static int counter = 0;

		//ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		//ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		//ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		//ImGui::Checkbox("Another Window", &show_another_window);

		//ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		//ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		//if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
		//	counter++;
		//ImGui::SameLine();
		//ImGui::Text("counter = %d", counter);

		//ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		//ImGui::End();


		Renderer::GetInstance().Render();

	}
	Cleanup();
}

void Rius::Minigin::StartViewEngine()
{
	static ImGuiID dockSpaceID = 0;
	if (ImGui::Begin(" ", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize))
	{
		dockSpaceID = ImGui::GetID("HUB_DockSpace");
		ImGui::DockSpace(dockSpaceID, ImVec2(0, 0), ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoResize);
		ImGui::SetWindowSize(ImVec2{ float(m_Width),float(m_Height) });
		ImGui::SetWindowPos(ImVec2(0, -100));

	}
	ImGui::End();
	ImGui::SetNextWindowDockID(dockSpaceID, ImGuiCond_FirstUseEver);
	ImGui::Begin("Rius - Engine");
	ImGui::End();
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			//ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("GameComponent"))
		{
			ShowAllComponents();
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void Rius::Minigin::ShowAllComponents()
{

	bool boxCollider2D{};
	bool circleCollider2D{};
	bool rigidBody{};
	bool spriteRenderer{};
	bool spriteSheet{};
	ImGui::MenuItem("BoxCollider", nullptr, &boxCollider2D);
	ImGui::MenuItem("CircleCollider2D", nullptr, &circleCollider2D);
	ImGui::Separator();
	ImGui::MenuItem("RigidBody", nullptr, &rigidBody);
	ImGui::MenuItem("SpriteRenderer", nullptr, &spriteRenderer);
	ImGui::MenuItem("SpriteSheet", nullptr, &spriteSheet);
	
}

