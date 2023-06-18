#include "UnitTest.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/Texture/TextureProvider.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Graphics/RHI/Renderer/RendererProvider.h"
#include "Graphics/RHI/Renderer/Renderer.h"

using namespace Enternity;
void UnitTest::Test()
{
	Texture* tex = Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTexture("assets/textures/skybox.jpega");
	Renderer* renderer = Engine::GetInstance().getGraphicsSystem()->getRendererProvider()->getRenderer("assets/shaders/Phong.verta", "assets/shaders/Phong.frag");

	int i = 0;
	i++;
}