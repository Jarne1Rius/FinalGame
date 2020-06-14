#pragma once
namespace Rius
{
	class Texture2D
	{
    public:
        unsigned int m_Id;
        // Texture image dimensions
        unsigned int m_Width, m_Height; // Width and height of loaded image in pixels
        // Texture Format
        unsigned int m_InternalFormat; // Format of texture object
        unsigned int m_ImageFormat; // Format of loaded image
        // Texture configuration
        unsigned int m_WrapS; // Wrapping mode on S axis
        unsigned int m_WrapT; // Wrapping mode on T axis
        unsigned int m_FilterMin; // Filtering mode if texture pixels < screen pixels
        unsigned int m_FilterMax; // Filtering mode if texture pixels > screen pixels
        // Constructor (sets default texture modes)
        Texture2D();
        // Generates texture from image data
        void Generate(unsigned int width, unsigned int height, unsigned char* data);
        // Binds the texture as the current active GL_TEXTURE_2D texture object
        void Bind() const;
	};
}
