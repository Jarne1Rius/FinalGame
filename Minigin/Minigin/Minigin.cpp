#include "MiniginPCH.h"
#include "Minigin.h"


#include <chrono>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

#include "imgui.h"
#include <glm/gtc/matrix_transform.hpp>

#pragma warning( push )
#pragma warning( disable : 4201)
#include <glm/gtc/type_ptr.hpp>
#pragma warning( pop ) 
#include <ft2build.h>
#include "Time.h"

#include "GameInstance.h"
#include "MaterialManager.h"

#include FT_FREETYPE_H

using namespace std;
using namespace std::chrono;
int Rius::Minigin::m_Height = 672;
float Rius::Minigin::m_TileHeight = 672 / 33.f;
float Rius::Minigin::m_TileWidth = 768 / 33.f;
int Rius::Minigin::m_Width = 768;
//Rius::FiniteStateMachine* Rius::Minigin::m_FSM = new Rius::FiniteStateMachine{};
Rius::UndoSystem  Rius::Minigin::m_UndoSystem{};
struct Character {
	unsigned int TextureID; // ID handle of the glyph texture
	glm::ivec2   Size;      // Size of glyph
	glm::ivec2   Bearing;   // Offset from baseline to left/top of glyph
	unsigned int Advance;   // Horizontal offset to advance to next glyph
};

unsigned int VAO, VBO;

void Rius::Minigin::Initialize()
{
	Rius::Renderer::GetInstance().Init(m_Width, m_Height);
	//glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	ResourceManager::m_ProjectionMatrix = glm::ortho(0.0f, static_cast<GLfloat>(m_Width), static_cast<GLfloat>(m_Height), 0.0f, -1.0f, 1.0f);

}


void Rius::Minigin::Cleanup()
{
	//	delete m_Sprite;
	Renderer::GetInstance().Destroy();
	ResourceManager::Clear();
	MaterialManager::Clear();
	UI::GetInstance().Cleanup();
}

void Rius::Minigin::Run()
{

	auto& sceneManager = SceneManager::GetInstance();
	auto& input = InputManager::GetInstance();

	auto lastTime = std::chrono::high_resolution_clock::now();
	double lag = 0.0f;

	while (!glfwWindowShouldClose(Renderer::GetInstance().getWindow()))
	{
		/*ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();*/

		const auto currentTime = high_resolution_clock::now();
		Renderer::GetInstance().Input();
		
		double deltaTime = duration<double>(currentTime - lastTime).count();
		lastTime = currentTime;
		lag += deltaTime;
		//doContinue = input.ProcessInput();
		input.Test();
		while (lag >= MsPerFrame/1000.f)
		{
			sceneManager.Update(MsPerFrame/1000.f);
			lag -= MsPerFrame / 1000.f;
		}
		//For LateUpdate
		//m_Sprite->Update();
		sceneManager.LateUpdate();
		Time::UpdateTimer(float(deltaTime));
		GameInstance::GetInstance().Update();
		//GameInstance::GetInstance().Update();
		glClearColor(0,0,0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		sceneManager.Render();
		/*

		bool show_demo_window = true;
		bool show_another_window = false;
		ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);*/
		//StartViewEngine();
		Renderer::GetInstance().Render();

	}
	sceneManager.CleanUp();
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

