#pragma once

namespace Enternity
{
	class Texture2D;
	class Renderer;
	struct PBRMaterialComponent
	{
		Renderer* renderer{ nullptr };

		Texture2D* albedo{ nullptr };
		Texture2D* normal{ nullptr };
		Texture2D* metallic{ nullptr };
		Texture2D* roughness{ nullptr };
		Texture2D* ao{ nullptr };

		void unload();
	};
}