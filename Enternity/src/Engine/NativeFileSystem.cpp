#include "NativeFileSystem.h"
#include "Blob.h"
#include "Log.h"
#include <fstream>

namespace Enternity
{
	void NativeFileSystem::read(Blob*& blob, const char* path)
	{		
		std::ifstream ifs;
		ifs.open(path, std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
			LOG_ERROR("Read file failed:{0}", path);
			return;
		}

		ifs.seekg(0, std::ios::end);
		auto length = ifs.tellg();
		ifs.seekg(0, std::ios::beg);

		SAFE_DELETE_SET_NULL(blob);
		blob = new Blob(length);

		ifs.read((char*)blob->getData(), blob->getLength());

		ifs.close();
	}
}