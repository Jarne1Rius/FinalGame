#include "MiniginPCH.h"
#include "Renderer.h"

#include "SceneManager.h"
#include "stb_image.h"
#include "imgui.h"


void Rius::Renderer::Init(unsigned int width, unsigned int height)
{
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


}

void Rius::Renderer::Render() const
{
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
	
	//glfwTerminate();
}
void Rius::framebuffer_size_callback(GLFWwindow*, int width, int height)
{
	glViewport(0, 0, width, height);
}

void Rius::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
