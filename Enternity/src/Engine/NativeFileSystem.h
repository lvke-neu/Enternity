#pragma once

namespace Enternity
{
	class Blob;
	class NativeFileSystem
	{
	public:
		void read(Blob*& blob, const char* path);
	};
}