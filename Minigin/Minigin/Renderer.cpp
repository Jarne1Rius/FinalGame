#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>

#include "SceneManager.h"
#include "Texture2D.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"
#include "Shader.h"
#include <fstream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>


void Rius::Renderer::Init(unsigned int width, unsigned int height)
{
	//const char* glsl_version = "#version 130";
	//ImGui::CreateContext();
	//ImGuiIO& io = ImGui::GetIO(); (void)io;
	//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	//io.ConfigWindowsMoveFromTitleBarOnly = true;
	//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	//ImGui::StyleColorsDark();
	m_Height = height;
	m_Width = width;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_pWindow = glfwCreateWindow(m_Width, m_Height, "Testing", NULL, NULL);
	if (m_pWindow == NULL)
	{
		std::cout << "Failed to create GLFW m_pWindow" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(m_pWindow);
	glfwSetFramebufferSizeCallback(m_pWindow, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}


	//ImGui_ImplGlfw_InitForOpenGL(m_pWindow, true);
	//ImGui_ImplOpenGL3_Init(glsl_version);
}

void Rius::Renderer::Render() const
{
	/*ImGui::Render();
	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());*/
	//processInput(m_pWindow);
	glfwSwapBuffers(m_pWindow);
	glfwPollEvents();
}

void Rius::Renderer::Input()
{
	processInput(m_pWindow);
}

Rius::Renderer::~Renderer()
{
}

void Rius::Renderer::Destroy()
{
	
	glfwTerminate();
}
void Rius::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Rius::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
