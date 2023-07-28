#pragma warning(disable:4312) 

#include "AssetPanel.h"
#include "Engine/Engine.h"
#include "Engine/AssetLoader.h"
#include "Graphics/RHI/Texture/Texture.h"
#include "Common/Macro.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"

#define CONTENT_BROWSER_DIRECTORRY "assets"

namespace Enternity
{
	AssetPanel::AssetPanel()
	{
		m_path = CONTENT_BROWSER_DIRECTORRY;

		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/logo/filelogo.png",
			[=](Asset* asset)
			{
				m_fileTexture = dynamic_cast<Texture2D*>(asset);
			});
		Engine::GetInstance().getAssetLoader()->getAsset("texture://TEXTURE_2D?assets/textures/logo/directorylogo.png",
			[=](Asset* asset)
			{
				m_directoryTexture = dynamic_cast<Texture2D*>(asset);
			});
	}

	AssetPanel::~AssetPanel()
	{
		SAFE_DELETE_SET_NULL(m_fileTexture);
		SAFE_DELETE_SET_NULL(m_directoryTexture);
	}

	void AssetPanel::draw()
	{
		ImGui::Begin("Asset");

		if (m_path != std::filesystem::path(CONTENT_BROWSER_DIRECTORRY))
		{
			if (ImGui::Button("<---"))
			{
				m_path = m_path.parent_path();
			}
		}

		static float padding = 16.0f;
		static float thumbnailSize = 70.0f;
		float cellSize = thumbnailSize + padding;
		static float buttonSize = 70.0f;
		float panelWidth = ImGui::GetContentRegionAvail().x;
		int columnCount = (int)(panelWidth / cellSize);
		if (columnCount < 1)
			columnCount = 1;

		ImGui::Columns(columnCount, 0, false);

		for (auto& p : std::filesystem::directory_iterator(m_path))
		{
			const auto& path = p.path();
			auto relativePath = std::filesystem::relative(path, CONTENT_BROWSER_DIRECTORRY);
			std::string fileNameString = relativePath.filename().string();

			ImGui::PushID(fileNameString.c_str());
			auto texture = p.is_directory() ? m_directoryTexture : m_fileTexture;
			ImGui::PushStyleColor(ImGuiCol_Button, { 0, 0, 0, 0 });
			if (texture)
			{
				ImGui::ImageButton((ImTextureID)texture->getRenderId(), { buttonSize, buttonSize }, { 0, 1 }, { 1, 0 });
			}
			
			if (!p.is_directory() && ImGui::BeginDragDropSource())
			{
				std::string cString = path.string();
				std::replace(cString.begin(), cString.end(), '\\', '/');

				//LOG_INFO(cString.c_str()+ "    size:" + std::to_string(cString.size()));
				ImGui::SetDragDropPayload("ASSET_BROWSER_ITEM", cString.c_str(), cString.size(), ImGuiCond_Once);
				ImGui::EndDragDropSource();
			}
			ImGui::PopStyleColor();
			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				if (p.is_directory())
				{
					m_path /= path.filename();
				}
			}
			ImGui::TextWrapped(fileNameString.c_str());
			ImGui::NextColumn();
			ImGui::PopID();
		}

		ImGui::Columns(1);
		ImGui::SliderFloat("Button Size", &buttonSize, 16, 512);
		ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		ImGui::SliderFloat("Padding", &padding, 0, 32);

		ImGui::End();
	}
}