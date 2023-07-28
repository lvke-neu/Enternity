#pragma once
#include <filesystem>

namespace Enternity
{
	class Texture2D;
	class AssetPanel
	{
	public:
		AssetPanel();
		~AssetPanel();
	public:
		void draw();
	private:
		std::filesystem::path m_path;
		Texture2D* m_fileTexture{ nullptr };
		Texture2D* m_directoryTexture{ nullptr };
	};
}