#pragma once

namespace Enternity
{
	class Mesh;
	class MeshProvider
	{
	public:
		Mesh* getMesh(const char* fullPath);
	};
}