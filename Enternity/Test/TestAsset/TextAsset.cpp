#include "TextAsset.h"
#include "Core/Blob/Blob.h"
#include <fstream>
#include <Windows.h>


namespace Enternity
{

	TextAsset::~TextAsset()
	{
		SAFE_DELETE_SET_NULL(m_data);
	}

	void TextAsset::doLoad()
	{
		Sleep(2000);
		std::ifstream ifs(m_path, std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			m_data = nullptr;
			return;
		}

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		m_data = new Blob(size);
		pFilebuf->sgetn((char*)m_data->getData(), m_data->getLength());
	}

}