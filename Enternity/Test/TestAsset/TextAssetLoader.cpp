#include "TextAssetLoader.h"
#include "Core/Blob/Blob.h"
#include <fstream>

#include <Windows.h>

namespace Enternity
{
	Blob* TextAssetLoader::doLoad(const std::string& assetID)
	{
		Sleep(2000);
		std::ifstream ifs(assetID, std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			return nullptr;
		}

		std::filebuf* pFilebuf = ifs.rdbuf();
		size_t size = pFilebuf->pubseekoff(0, ifs.end, ifs.in);
		pFilebuf->pubseekpos(0, ifs.in);

		Blob* blob = new Blob(size);
		pFilebuf->sgetn((char*)blob->getData(), blob->getLength());

		ifs.close();

		return blob;
	}
}