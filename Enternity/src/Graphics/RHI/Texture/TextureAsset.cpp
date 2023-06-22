#include "TextureAsset.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "stb_image.h"

namespace Enternity
{
	TextureAsset::TextureAsset(const std::string& fullPath, bool slip) :
		m_fullPath(fullPath)
	{
		m_bSlip = slip;
	}

	TextureAsset::~TextureAsset()
	{
		SAFE_DELETE_SET_NULL(m_content);
	}

	void TextureAsset::doLoad()
	{
		unsigned char* tmpTexture;

		stbi_set_flip_vertically_on_load(m_bSlip);
		tmpTexture = stbi_load(m_fullPath.c_str(), &m_width, &m_height, &m_channels, 0);
		if (!tmpTexture)
		{
			m_state = loading_state_failed;
			LOG_ERROR("Texture load failed:{0}", m_fullPath);
			return;
		}

		SAFE_DELETE_SET_NULL(m_content);
		m_content = new Blob(m_width * m_height * m_channels);
		memcpy_s(m_content->getData(), m_content->getLength(), tmpTexture, m_content->getLength());

		stbi_image_free(tmpTexture);

		m_state = loading_state_succeeded;
	}
}