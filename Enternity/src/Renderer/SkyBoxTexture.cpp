#include "SkyBoxTexture.h"
#include "Stb_Image/stb_image.h"

BEGIN_ENTERNITY

SkyBoxTexture::SkyBoxTexture(const std::vector<std::string>& filePaths)
{
	glGenTextures(1, &m_rendererId);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId);

	unsigned char* data;
	int height;
	int width;
	int channels;
	for (int i = 0; i < filePaths.size(); ++i)
	{
		data = stbi_load(filePaths[i].c_str(), &width, &height, &channels, 0);
		glTexImage2D(GL_TEXTURE_CUBE_MAP, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		stbi_image_free(data);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
}

SkyBoxTexture::~SkyBoxTexture()
{
	glDeleteTextures(1, &m_rendererId);
}

void SkyBoxTexture::Bind(unsigned int slot) const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId);
}

void SkyBoxTexture::UnBind() const
{
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

END_ENTERNITY

