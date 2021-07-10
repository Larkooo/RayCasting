#pragma once

#include <string>

class Texture
{
	std::string m_Path;
	uint8_t* m_Data = nullptr;
	int m_Width, m_Height;

public:
	Texture(const std::string& path);
	~Texture();

	uint8_t* GetData() const { return m_Data; }
	
	const std::string& GetPath() { return m_Path; }
	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Width; }
};