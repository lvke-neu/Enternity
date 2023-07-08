#include "TextureAsset.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include "stb_image.h"

namespace Enternity
{
	std::mutex mtx;
	TextureAsset::TextureAsset(const std::string& fullPath, bool slip) :
		m_fullPath(fullPath)
	{
		m_bSlip = slip;
	}

	TextureAsset::TextureAsset(Blob* data, int width, int height, int channels) :
		m_width(width), m_height(height), m_channels(channels)
	{
		if (!data)
			return;

		m_content = new Blob(data->getLength());
		memcpy_s(m_content->getData(), m_content->getLength(), data->getData(), data->getLength());
		m_state = loading_state_succeeded;
	}

	TextureAsset::~TextureAsset()
	{
		SAFE_DELETE_SET_NULL(m_content);
	}

	void TextureAsset::doLoad()
	{
		mtx.lock();

		unsigned char* tmpTexture;

		stbi_set_flip_vertically_on_load(m_bSlip);
		tmpTexture = stbi_load(m_fullPath.c_str(), &m_width, &m_height, &m_channels, 0);
		if (!tmpTexture)
		{
			m_state = loading_state_failed;
			LOG_ERROR("Texture load failed:{0}", m_fullPath);
			mtx.unlock();
			return;
		}

		SAFE_DELETE_SET_NULL(m_content);
		m_content = new Blob(m_width * m_height * m_channels);
		memcpy_s(m_content->getData(), m_content->getLength(), tmpTexture, m_content->getLength());

		stbi_image_free(tmpTexture);

		m_state = loading_state_succeeded;

		mtx.unlock();
	}
}