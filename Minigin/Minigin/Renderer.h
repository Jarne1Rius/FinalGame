#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Singleton.h"

namespace Rius
{
	class Texture2D;
	
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(unsigned int width, unsigned int height);
		void Render() const;
		void Input();
		GLFWwindow* getWindow() { return m_pWindow; }
		~Renderer();
		void Destroy();

	private:
		friend class Singleton<Renderer>;
		Renderer() = default;
		unsigned int m_Width = 0;
		unsigned int m_Height = 0;
		GLFWwindow* m_pWindow = nullptr;
		
	};
	void processInput(GLFWwindow* window);
	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
}
