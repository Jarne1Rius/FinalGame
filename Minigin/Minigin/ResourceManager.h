#pragma once
#include <map>


#include "Shader.h"
#include "Texture2D.h"
#include "Singleton.h"

namespace Rius
{
	class ResourceManager final
	{
	public:

		static Shader* LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, std::string name);
		// Retrieves a stored sader
		static Shader* GetShader(std::string name);
		// Loads (and generates) a texture from file
		static Texture2D* LoadTexture(const GLchar* file, GLboolean alpha, std::string name);
		// Retrieves a stored texture
		static Texture2D* GetTexture(std::string name);
		// Properly de-allocates all loaded resources
		static void Clear();
		static void ClearTexture(Texture2D* pTexture);
		static glm::mat4 m_ProjectionMatrix;
	private:
		static std::map<std::string, Shader*>    m_Shaders;
		static std::map<std::string, Texture2D*> M_Textures;
		ResourceManager() = default;
		// Loads and generates a shader from file
		static Shader* LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile);
		// Loads a single texture from file
		static Texture2D* LoadTextureFromFile(const GLchar* file, GLboolean alpha);

	};
}
