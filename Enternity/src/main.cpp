#include "Engine/Engine.h"

int main(int argc, const char** argv) {

	Enternity::Engine::GetInstance().initialize();
	Enternity::Engine::GetInstance().run();
	Enternity::Engine::GetInstance().uninitialize();


	return 0;
}


//#include "Scene/SceneGraph/3D/Node3D.h"


//class hhh
//{
//public:
//	int m_num = 0;
//};
//

//#include <Scene/SceneGraph/Visual3D.h>
//#include "Graphics/Material.h"
//#include "Graphics/RHI/Mesh/Mesh.h"
//#include "Graphics/RHI/Renderer/Renderer.h"
//
//using namespace Enternity;
//int main(int argc, const char** argv) {
//
//	Mesh* mesh = new Mesh;
//
//
//	std::shared_ptr<Mesh> sp(mesh);
//
//	Visual3D v3d;
//	v3d.set_mesh(sp);
//
//
//	Visual3D v3d2;
//	v3d2.set_mesh(sp);
//
//	return 0;
//}