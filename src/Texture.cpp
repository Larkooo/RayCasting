#include "Texture.h"

#include "stb_image.h"

Texture::Texture(const std::string& path)
{
	m_Path = path;

	int channels;
	m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &channels, STBI_rgb);
}

Texture::~Texture()
{
	stbi_image_free(m_Data);
}
