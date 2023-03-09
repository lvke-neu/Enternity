#include "TextAsset.h"
#include "RuntimeModule/Graphics/GraphicsManager.h"
#include "Engine/Engine.h"
#include "Utility/Utility.h"
#include "Core/Blob/Blob.h"

#include <Windows.h>
namespace Enternity
{

	TextAsset::~TextAsset()
	{
		SAFE_DELETE_SET_NULL(m_data);
	}

	void TextAsset::doLoad()
	{
		Sleep(2000);
		
		m_data = ReadFile(m_path.c_str());
	}

	void TextAsset::callBack()
	{
		printf("TextAsset load finished");
		GraphicsManager* graphicsManager = (GraphicsManager*)Engine::GetInstance().GetRuntimeModule("GraphicsManager");
		graphicsManager->setClearColor({ 0.2f, 0.3f, 0.4f });
	}
}