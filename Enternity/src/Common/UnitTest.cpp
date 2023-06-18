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
	MeshAsset ma("assets/models/2nrtbod1out/2nrtbod1out.obj");
	ma.load();

	Texture* tex = Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTexture("assets/textures/skybox.jpeg");
	Renderer* renderer = Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRenderer("assets/shaders/Phong.vert", "assets/shaders/Phong.frag");


	//while (true)
	//{
	//	if (ma.getLoadingState() == Asset::loading_state_succeeded)
	//	{
	//		Mesh mesh(&ma);
	//		int i = 0;
	//		i++;
	//	}
	//}

	int i = 0;
	i++;
}