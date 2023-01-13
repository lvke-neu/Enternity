#include <iostream>
#include "Engine/Engine.h"
#include "File/FileOperation.h"
#include <glm/glm.hpp>
using namespace Enternity;
int main()
{	
	if (Enternity::Engine::GetInstance().Initialize())
	{
		Enternity::Engine::GetInstance().Run();
	}


 //   struct VertexPosTex
 //   {
 //       glm::vec3 position;
 //       glm::vec3 normal;
 //       glm::vec2 texcoord;
 //   };

 //   std::vector<VertexPosTex> vertices;
 //   vertices.resize(4);
 //   vertices[0].position = glm::vec3(-1, 0, 1);
 //   vertices[1].position = glm::vec3(1, 0, 1);
 //   vertices[2].position = glm::vec3(1, 0, -1);
 //   vertices[3].position = glm::vec3(-1, 0, -1);


 //   for (UINT i = 0; i < 4; ++i)
 //   {
 //       vertices[i].normal = glm::vec3(0.0f, 1.0f, 0.0f);
 //   }

 //   vertices[0].texcoord = glm::vec2(0.0f, 0.0f);
 //   vertices[1].texcoord = glm::vec2(1.0f, 0.0f);
 //   vertices[2].texcoord = glm::vec2(1.0f, 1.0f);
 //   vertices[3].texcoord = glm::vec2(0.0f, 1.0f);
 //

 //   //index buffer
 //   unsigned int indices[] =
 //   {
 //       0, 1, 2, 2, 3, 0,
 //   };

 //   unsigned int vertexcount = vertices.size();
 //   unsigned int indexcount = sizeof(indices) / sizeof(unsigned int);
	//Enternity::Blob blob(8 + vertices.size() * sizeof(VertexPosTex) + sizeof(indices) );


	//memcpy_s(blob.GetData(), sizeof(unsigned int), &vertexcount, sizeof(unsigned int));
	//memcpy_s((char*)blob.GetData() + sizeof(unsigned int), sizeof(unsigned int), &indexcount, sizeof(unsigned int));
 //   memcpy_s((char*)blob.GetData() + 2 * sizeof(unsigned int), vertexcount* sizeof(VertexPosTex), vertices.data(), vertexcount* sizeof(VertexPosTex));
 //   memcpy_s((char*)blob.GetData() + 2 * sizeof(unsigned int) + vertexcount * sizeof(VertexPosTex), sizeof(indices), indices, sizeof(indices));

	//Enternity::FileOperation::WriteFile(blob, "assets/model/plane_mesh.bin");




	//Enternity::Blob blob2(4096);
	//Enternity::FileOperation::ReadFile(blob2, "assets/model/plane_mesh.bin");

 //   unsigned int vertexcount2; 
 //   unsigned int indexcount2; 
 //   memcpy_s(&vertexcount2, sizeof(unsigned int), blob2.GetData(), sizeof(unsigned int));
 //   memcpy_s(&indexcount2, sizeof(unsigned int), (char*)blob2.GetData() + sizeof(unsigned int), sizeof(unsigned int));

 //   VertexPosTex* vpt = new VertexPosTex[vertexcount2];
 //   unsigned int* indices2 = new unsigned int[indexcount2];
 //   memcpy_s(vpt, vertexcount2 * sizeof(VertexPosTex), (char*)blob2.GetData() + 2 * sizeof(unsigned int), vertexcount2 * sizeof(VertexPosTex));
 //   memcpy_s(indices2, indexcount2 * sizeof(unsigned int), (char*)blob2.GetData() + 2 * sizeof(unsigned int) + vertexcount2 * sizeof(VertexPosTex), indexcount2 * sizeof(unsigned int));

 //  


	//int i = 0;
	//i++;

 //   delete[] vpt;
 //   delete[] indices2;



	return 0;
}