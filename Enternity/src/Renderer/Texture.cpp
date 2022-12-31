#include "Texture.h"
#include "Stb_Image/stb_image.h"

BEGIN_ENTERNITY

Texture::Texture(const std::string& filePath)
{
	stbi_set_flip_vertically_on_load(1);
	m_localBuffer = stbi_load(filePath.c_str(), &m_width, &m_height, &m_bpp, 4);

	CHECK_GL_CALL(glGenTextures(1, &m_rendererId));
	CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));

	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	CHECK_GL_CALL(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));


	CHECK_GL_CALL(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_localBuffer));

	if (m_localBuffer)
		stbi_image_free(m_localBuffer);
}

Texture::~Texture()
{
	CHECK_GL_CALL(glDeleteTextures(1, &m_rendererId));
}

void Texture::Bind(unsigned int slot)
{
	CHECK_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
	CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, m_rendererId));
}


void Texture::UnBind() const
{
	CHECK_GL_CALL(glBindTexture(GL_TEXTURE_2D, 0));
}

END_ENTERNITY