#include "SkyBoxTexture.h"
#include "Stb_Image/stb_image.h"

BEGIN_ENTERNITY

SkyBoxTexture::SkyBoxTexture(const std::vector<std::string>& filePaths)
{
	CHECK_GL_CALL(glGenTextures(1, &m_rendererId));
	CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId));

	unsigned char* data;
	int height;
	int width;
	int channels;
	for (int i = 0; i < filePaths.size(); ++i)
	{
		data = stbi_load(filePaths[i].c_str(), &width, &height, &channels, 0);
		CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data));
		stbi_image_free(data);
	}

	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE));
}

SkyBoxTexture::~SkyBoxTexture()
{
	glDeleteTextures(1, &m_rendererId);
}

void SkyBoxTexture::Bind(unsigned int slot) const
{
	CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, m_rendererId));
}

void SkyBoxTexture::UnBind() const
{
	CHECK_GL_CALL(glBindTexture(GL_TEXTURE_CUBE_MAP, 0));
}

END_ENTERNITY

