#pragma once

#include "Macro/Macro.h"
#include "Blob.h"
#include <string>

BEGIN_ENTERNITY

class FileOperation
{
public:
	static void ReadFile(Blob& blob, const std::string& filePath);
	static void WriteFile(const Blob& blob, const std::string& filePath);
};

END_ENTERNITY