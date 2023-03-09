#include "SceneAsset.h"
#include "Utility/Utility.h"
#include "Core/Blob/Blob.h"

namespace Enternity
{

	SceneAsset::~SceneAsset()
	{
		SAFE_DELETE_SET_NULL(m_data);
	}

	void SceneAsset::doLoad()
	{
		m_data = ReadFile(m_path.c_str());
	}

	void SceneAsset::callBack()
	{
		printf("SceneAsset load finished");
	}
}