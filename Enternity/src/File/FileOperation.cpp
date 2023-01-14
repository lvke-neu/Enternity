#include "FileOperation.h"
#include <fstream>

BEGIN_ENTERNITY

bool FileOperation::ReadFile(Blob& blob, const std::string& filePath)
{
	std::ifstream ifs(filePath, std::ios::out | std::ios::binary);
	if (!ifs.is_open())
		return false;

	ifs.read((char*)blob.GetData(), blob.GetLength());
	ifs.close();
	return true;
}

void FileOperation::WriteFile(const Blob& blob, const std::string& filePath)
{
	std::ofstream ofs(filePath, std::ios::out | std::ios::binary);
	ofs.write((char*)blob.GetData(), blob.GetLength());
	ofs.close();
}

END_ENTERNITY


