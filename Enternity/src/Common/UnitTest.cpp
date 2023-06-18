#include "UnitTest.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Texture/TextureProvider.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Texture/TextureAsset.h"
#include "Graphics/RHI/Renderer/RendererProvider.h"
#include "Graphics/RHI/Renderer/Renderer.h"
#include "Graphics/RHI/Renderer/RendererAsset.h"
#include "Graphics/RHI/Mesh/MeshProvider.h"
#include "Graphics/RHI/Mesh/Mesh.h"
#include "Graphics/RHI/Mesh/MeshAsset.h"

using namespace Enternity;
void UnitTest::Test()
{
	Mesh* mesh = Engine::GetInstance().getGraphicsSystem()->getMeshProvider()->getMesh("assets/models/2nrtbod1out/2nrtbod1out.obj");
	Texture* texture = Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTexture("assets/textures/skybox.jpeg");
	Renderer* renderer = Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRenderer("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");

	//MeshAsset ma("assets/models/2nrtbod1out/2nrtbod1out.obj");
	//ma.load();
	//while (true)
	//{
	//	if (ma.getLoadingState() == Asset::loading_state_succeeded)
	//	{
	//		Mesh mesh(&ma);
	//		int i = 0;
	//		i++;
	//	}
	//}


	SAFE_DELETE_SET_NULL(mesh);
	SAFE_DELETE_SET_NULL(texture);
	SAFE_DELETE_SET_NULL(renderer);
}