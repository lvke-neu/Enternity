/***************************************************************************************
Author: lvke
Date:2023/2/20 21:10
Description:
AssetDefinition
****************************************************************************************/
#pragma once
#include <string>
#include <vector>
#include "Core/Math/Vector3.h"
#include "Core/Math/Vector2.h"

namespace Enternity
{
	enum class AssetType
	{
		Shader,
		Texture,
		Mesh
	};

	enum class AssetLoadState
	{
		Success,
		Failure,
		Unloaded
	};

	enum class AssetLoadType
	{
		Sync,
		Asyn
	};

	struct AssetDescription
	{
		std::string assetID;
		AssetType assetType;
		AssetLoadType assetLoadType;
	};

	struct VertexPosNorTex
	{
		Vector3f position;
		Vector3f normal;
		Vector2f texcoord;
	};

	struct Mesh
	{
		std::vector<VertexPosNorTex> vertices;
		std::vector<unsigned int> indices;
	};
}