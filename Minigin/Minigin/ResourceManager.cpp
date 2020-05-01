#include "MiniginPCH.h"
#include "ResourceManager.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "Renderer.h"
#include "Texture2D.h"
#include "Font.h"
#include "stb_image.h"

std::map<std::string, Rius::Texture2D*> Rius::ResourceManager::M_Textures;
std::map<std::string, Rius::Shader*> Rius::ResourceManager::m_Shaders;
glm::mat4 Rius::ResourceManager::m_ProjectionMatrix;

Rius::Shader* Rius::ResourceManager::LoadShader(const GLchar* vShaderFile, const GLchar* fShaderFile, std::string name)
{
	m_Shaders[name] = LoadShaderFromFile(vShaderFile, fShaderFile);
	return m_Shaders[name];
}

Rius::Shader* Rius::ResourceManager::GetShader(std::string name)
{
	return m_Shaders[name];
}

Rius::Texture2D* Rius::ResourceManager::LoadTexture(const GLchar* file, GLboolean alpha, std::string name)
{
	M_Textures[name] = LoadTextureFromFile(file, alpha);
	return M_Textures[name];
}

Rius::Texture2D* Rius::ResourceManager::GetTexture(std::string name)
{
	return M_Textures[name];
}

void Rius::ResourceManager::Clear()
{
	for (auto shader : m_Shaders)
	{
		glDeleteProgram(shader.second->ID);
		delete shader.second;
	}
	for (auto texture : M_Textures)
	{
		glDeleteTextures(1, &texture.second->ID);
		delete texture.second;
	}
}

void Rius::ResourceManager::ClearTexture(Texture2D* pTexture2D)
{
	for (auto texture : M_Textures)
	{
		if (texture.second == pTexture2D)
		{
			glDeleteTextures(1, &texture.second->ID);
			delete texture.second;
		}

	}
}

Rius::Shader* Rius::ResourceManager::LoadShaderFromFile(const GLchar* vShaderFile, const GLchar* fShaderFile)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// Open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// Read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// Convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
		// If geometry shader path is present, also load a geometry shader
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const GLchar* vShaderCode = vertexCode.c_str();
	const GLchar* fShaderCode = fragmentCode.c_str();
	const GLchar* gShaderCode = geometryCode.c_str();
	// 2. Now create shader object from source code
	Shader* shader = new Shader();
	shader->Compile(vShaderCode, fShaderCode);
	return shader;
}

Rius::Texture2D* Rius::ResourceManager::LoadTextureFromFile(const GLchar* file, GLboolean alpha)
{
	Texture2D* texture = new Texture2D();
	if (alpha)
	{
		texture->Internal_Format = GL_RGBA;
		texture->Image_Format = GL_RGBA;
	}
	// Load image
	int width, height;
	unsigned char* image = stbi_load(file, &width, &height, 0, texture->Image_Format == GL_RGBA ? STBI_rgb_alpha : STBI_rgb);
	// Now generate texture
	texture->Generate(width, height, image);
	// And finally free image data
	stbi_image_free(image);
	return texture;
}
