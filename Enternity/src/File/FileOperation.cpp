#include "FileOperation.h"
#include <fstream>

BEGIN_ENTERNITY

void FileOperation::ReadFile(Blob& blob, const std::string& filePath)
{
	std::ifstream ifs(filePath, std::ios::out | std::ios::binary);
	ifs.read((char*)blob.GetData(), blob.GetLength());
	ifs.close();
}

void FileOperation::WriteFile(const Blob& blob, const std::string& filePath)
{
	std::ofstream ofs(filePath, std::ios::out | std::ios::binary);
	ofs.write((char*)blob.GetData(), blob.GetLength());
	ofs.close();
}

END_ENTERNITY

//void writeBinFile()
//{
//	Student student;
//	student.age = 16;
//	student.n = 250;
//
//	std::ofstream outBinFile("student.dat", std::ios::out | std::ios::binary);
//	outBinFile.write((char*)&student, sizeof(student));
//
//	outBinFile.close();
//}
//
//void readBinFile()
//{
//	Student student;
//	std::ifstream inBinFile("student.dat", std::ios::in | std::ios::binary);
//
//	while (inBinFile.read((char*)&student, sizeof(student))) {
//		inBinFile.gcount();
//		std::cout << student.age << " " << student.n << std::endl;
//	}
//
//}


