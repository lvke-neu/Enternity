#include "ShaderBlobHolder.h"
#include "Engine/Blob.h"
#include "Engine/Log.h"
#include <fstream>

namespace Enternity
{
	ShaderBlobHolder::ShaderBlobHolder(const AssetID& assetID) : BlobHolder(assetID)
	{

	}

	void ShaderBlobHolder::doLoad()
	{
		std::ifstream ifs(m_assetID.normalize(), std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			m_state = loading_state_failed;
			LOG_ERROR("load failed \"{0}\"", m_assetID.getPath());
			return;
		}

		SAFE_DELETE_SET_NULL(m_blob);

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		m_blob = new Blob(size);
		pFilebuf->sgetn((char*)m_blob->getData(), m_blob->getLength());

		ifs.close();

		m_state = loading_state_succeeded;
	}
}

