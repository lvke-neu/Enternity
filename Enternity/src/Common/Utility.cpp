#include "Utility.h"
#include <windows.h>
#include <stdio.h>

namespace Enternity
{
	const char* Utility::GenerateUUID()
	{
		GUID guid;
		CoCreateGuid(&guid);
		const UINT bufferLength = 256;
		char* guidStr = new char[bufferLength];
		_snprintf_s(guidStr, bufferLength, bufferLength - 1,
			"%08X-%04X-%04x-%02X%02X-%02X%02X%02X%02X%02X%02X",
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2],
			guid.Data4[3], guid.Data4[4], guid.Data4[5],
			guid.Data4[6], guid.Data4[7]);
		return guidStr;
	}
}

