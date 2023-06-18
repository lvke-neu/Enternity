#include "RendererAsset.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include <fstream>

namespace Enternity
{
	RendererAsset::RendererAsset(const std::string& fullPath) :
		m_fullPath(fullPath)
	{

	}

	RendererAsset::~RendererAsset()
	{
		SAFE_DELETE_SET_NULL(m_content);
	}

	void RendererAsset::doLoad()
	{
		std::ifstream ifs(m_fullPath, std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			m_state = loading_state_failed;
			LOG_ERROR("RendererAsset load failed:{0}", m_fullPath);
			return;
		}

		SAFE_DELETE_SET_NULL(m_content);

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		m_content = new Blob(size);
		pFilebuf->sgetn((char*)m_content->getData(), m_content->getLength());

		ifs.close();

		m_state = loading_state_succeeded;
	}
}