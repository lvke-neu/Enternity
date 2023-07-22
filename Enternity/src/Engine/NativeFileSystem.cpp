#include "NativeFileSystem.h"
#include "Blob.h"
#include "Common/Macro.h"
#include <fstream>

namespace Enternity
{
	void NativeFileSystem::read(Blob*& blob, const char* path)
	{		
		std::ifstream ifs;
		ifs.open(path, std::ios::in | std::ios::binary);
		if (!ifs.is_open())
		{
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