#include <iostream>
#include "Engine/Engine.h"
#include "File/FileOperation.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
using namespace Enternity;

void GenerateMeshFile()
{
	struct VertexPosTex
	{
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec2 texcoord;
	};

	std::vector<VertexPosTex> vertices;

	const float radius = 1.0f;
	const UINT levels = 20;
	const UINT slices = 20;

	const UINT vertexCount = 2 + (levels - 1) * (slices + 1);
	vertices.resize(vertexCount);

	DWORD vIndex = 0, iIndex = 0;

	float phi = 0.0f, theta = 0.0f;
	float per_phi = glm::pi<float>() / levels;
	float per_theta = 2 * glm::pi<float>() / slices;
	float x, y, z;

	vertices[vIndex++] = VertexPosTex({ glm::vec3(0.0f, radius, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec2(0.0f, 1.0f) });

	for (UINT i = 1; i < levels; ++i)
	{
		phi = per_phi * i;

		for (UINT j = 0; j <= slices; ++j)
		{
			theta = per_theta * j;
			x = radius * sinf(phi) * cosf(theta);
			y = radius * cosf(phi);
			z = radius * sinf(phi) * sinf(theta);

			glm::vec3 pos = glm::vec3(x, y, -z), normal;
			normal = glm::normalize(pos);

			vertices[vIndex++] = VertexPosTex({ pos, normal,  glm::vec2(theta / (2 * glm::pi<float>()), -phi / glm::pi<float>() + 1) });
		}
	}
	vertices[vIndex++] = VertexPosTex({ glm::vec3(0.0f, -radius, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) });



	//index buffer
	std::vector<unsigned int> indices;
	indices.resize(6 * (levels - 1) * slices);

	if (levels > 1)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			indices[iIndex++] = 0;
			indices[iIndex++] = j % (slices + 1) + 1;
			indices[iIndex++] = j;
		}
	}

	for (UINT i = 1; i < levels - 1; ++i)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			indices[iIndex++] = (i - 1) * (slices + 1) + j;
			indices[iIndex++] = (i - 1) * (slices + 1) + j % (slices + 1) + 1;
			indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;

			indices[iIndex++] = i * (slices + 1) + j % (slices + 1) + 1;
			indices[iIndex++] = i * (slices + 1) + j;
			indices[iIndex++] = (i - 1) * (slices + 1) + j;
		}
	}

	if (levels > 1)
	{
		for (UINT j = 1; j <= slices; ++j)
		{
			indices[iIndex++] = (levels - 2) * (slices + 1) + j;
			indices[iIndex++] = (levels - 2) * (slices + 1) + j % (slices + 1) + 1;
			indices[iIndex++] = (levels - 1) * (slices + 1) + 1;
		}
	}

	unsigned int vertexcount = (unsigned int)vertices.size();
	unsigned int indexcount = (unsigned int)indices.size();
	Enternity::Blob blob((unsigned int)(8 + vertices.size() * sizeof(VertexPosTex) + indices.size() * sizeof(unsigned int)));


	memcpy_s(blob.GetData(), sizeof(unsigned int), &vertexcount, sizeof(unsigned int));
	memcpy_s((char*)blob.GetData() + sizeof(unsigned int), sizeof(unsigned int), &indexcount, sizeof(unsigned int));
	memcpy_s((char*)blob.GetData() + 2 * sizeof(unsigned int), vertexcount * sizeof(VertexPosTex), vertices.data(), vertexcount * sizeof(VertexPosTex));
	memcpy_s((char*)blob.GetData() + 2 * sizeof(unsigned int) + vertexcount * sizeof(VertexPosTex), indexcount * sizeof(unsigned int), indices.data(), indexcount * sizeof(unsigned int));

	Enternity::FileOperation::WriteFile(blob, "assets/model/sphere_mesh.bin");




	Enternity::Blob blob2(4096);
	Enternity::FileOperation::ReadFile(blob2, "assets/model/sphere_mesh.bin");

	unsigned int vertexcount2;
	unsigned int indexcount2;
	memcpy_s(&vertexcount2, sizeof(unsigned int), blob2.GetData(), sizeof(unsigned int));
	memcpy_s(&indexcount2, sizeof(unsigned int), (char*)blob2.GetData() + sizeof(unsigned int), sizeof(unsigned int));

	VertexPosTex* vpt = new VertexPosTex[vertexcount2];
	unsigned int* indices2 = new unsigned int[indexcount2];
	memcpy_s(vpt, vertexcount2 * sizeof(VertexPosTex), (char*)blob2.GetData() + 2 * sizeof(unsigned int), vertexcount2 * sizeof(VertexPosTex));
	memcpy_s(indices2, indexcount2 * sizeof(unsigned int), (char*)blob2.GetData() + 2 * sizeof(unsigned int) + vertexcount2 * sizeof(VertexPosTex), indexcount2 * sizeof(unsigned int));




	int i = 0;
	i++;


	delete[] vpt;
	delete[] indices2;




}


int main()
{	
	//GenerateMeshFile();
	if (Enternity::Engine::GetInstance().Initialize())
	{
		Enternity::Engine::GetInstance().Run();
	}

	return 0;
}