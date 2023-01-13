#include <iostream>
#include "Engine/Engine.h"
#include "File/FileOperation.h"
#include <glm/glm.hpp>
using namespace Enternity;
int main()
{	

    struct VertexPosTex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texcoord;
    };

    std::vector<VertexPosTex> vertices;
    vertices.resize(24);
    vertices[0].position = glm::vec3(1, -1, 1);
    vertices[1].position = glm::vec3(1, 1, 1);
    vertices[2].position = glm::vec3(1, 1, -1);
    vertices[3].position = glm::vec3(1, -1, -1);

    vertices[4].position = glm::vec3(-1, -1, -1);
    vertices[5].position = glm::vec3(-1, 1, -1);
    vertices[6].position = glm::vec3(-1, 1, 1);
    vertices[7].position = glm::vec3(-1, -1, 1);

    vertices[8].position = glm::vec3(-1, 1, 1);
    vertices[9].position = glm::vec3(-1, 1, -1);
    vertices[10].position = glm::vec3(1, 1, -1);
    vertices[11].position = glm::vec3(1, 1, 1);

    vertices[12].position = glm::vec3(1, -1, 1);
    vertices[13].position = glm::vec3(1, -1, -1);
    vertices[14].position = glm::vec3(-1, -1, -1);
    vertices[15].position = glm::vec3(-1, -1, 1);

    vertices[16].position = glm::vec3(1, -1, -1);
    vertices[17].position = glm::vec3(1, 1, -1);
    vertices[18].position = glm::vec3(-1, 1, -1);
    vertices[19].position = glm::vec3(-1, -1, -1);

    vertices[20].position = glm::vec3(-1, -1, 1);
    vertices[21].position = glm::vec3(-1, 1, 1);
    vertices[22].position = glm::vec3(1, 1, 1);
    vertices[23].position = glm::vec3(1, -1, 1);

    for (UINT i = 0; i < 4; ++i)
    {
        vertices[i].normal = glm::vec3(1.0f, 0.0f, 0.0f);

        vertices[i + 4].normal = glm::vec3(-1.0f, 0.0f, 0.0f);

        vertices[i + 8].normal = glm::vec3(0.0f, 1.0f, 0.0f);

        vertices[i + 12].normal = glm::vec3(0.0f, -1.0f, 0.0f);

        vertices[i + 16].normal = glm::vec3(0.0f, 0.0f, -1.0f);

        vertices[i + 20].normal = glm::vec3(0.0f, 0.0f, 1.0f);
    }

    for (UINT i = 0; i < 6; ++i)
    {
        vertices[i * 4].texcoord = glm::vec2(0.0f, 0.0f);
        vertices[i * 4 + 1].texcoord = glm::vec2(0.0f, 1.0f);
        vertices[i * 4 + 2].texcoord = glm::vec2(1.0f, 1.0f);
        vertices[i * 4 + 3].texcoord = glm::vec2(1.0f, 0.0f);
    }

    //index buffer
    unsigned int indices[] =
    {
        0, 1, 2, 2, 3, 0,
        4, 5, 6, 6, 7, 4,
        8, 9, 10, 10, 11, 8,
        12, 13, 14, 14, 15, 12,
        16, 17, 18, 18, 19, 16,
        20, 21, 22, 22, 23, 20
    };

    unsigned int vertexcount = vertices.size();
    unsigned int indexcount = sizeof(indices) / sizeof(unsigned int);
	Enternity::Blob blob(8 + vertices.size() * sizeof(VertexPosTex) + sizeof(indices) );


	memcpy_s(blob.GetData(), sizeof(unsigned int), &vertexcount, sizeof(unsigned int));
	memcpy_s((char*)blob.GetData() + sizeof(unsigned int), sizeof(unsigned int), &indexcount, sizeof(unsigned int));
    memcpy_s((char*)blob.GetData() + 2 * sizeof(unsigned int), vertexcount* sizeof(VertexPosTex), vertices.data(), vertexcount* sizeof(VertexPosTex));
    memcpy_s((char*)blob.GetData() + 2 * sizeof(unsigned int) + vertexcount * sizeof(VertexPosTex), sizeof(indices), indices, sizeof(indices));

	Enternity::FileOperation::WriteFile(blob, "assets/model/cube.bin");




	Enternity::Blob blob2(4096);
	Enternity::FileOperation::ReadFile(blob2, "assets/model/cube.bin");

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

	//if (Enternity::Engine::GetInstance().Initialize())
	//{
	//	Enternity::Engine::GetInstance().Run();
	//}

	return 0;
}