#include "UnitTest.h"
#include "Engine/Engine.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/TextureProvider.h"
#include "Graphics/RHI/Texture.h"

using namespace Enternity;
void UnitTest::Test()
{
	Texture* tex = Engine::GetInstance().getGraphicsSystem()->getTextureProvider()->getTexture("assets/textures/skybox.jpeg");

	int i = 0;
	i++;
}