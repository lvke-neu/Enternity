#pragma warning(disable:4312) 

#include "ContentBrowserPanel.h"

BEGIN_ENTERNITY

#define CONTENT_BROWSER_DIRECTORRY "assets"

ContentBrowserPanel::ContentBrowserPanel():
	m_Path(CONTENT_BROWSER_DIRECTORRY)
{
	m_FileTexture = new Texture("Resource/FileIcon.png");
	m_DirectoryTexture = new Texture("Resource/DirectoryIcon.png");

	ImguiDrawEventManager::GetInstance().RegisterEvent(this);
}

ContentBrowserPanel::~ContentBrowserPanel()
{
	ImguiDrawEventManager::GetInstance().UnRegisterEvent(this);
	SAFE_DELETE_SET_NULL(m_FileTexture);
	SAFE_DELETE_SET_NULL(m_DirectoryTexture);
}

void ContentBrowserPanel::ImguiDraw()
{
	ImGui::Begin(("Content Browser"));

	if (m_Path != std::filesystem::path(CONTENT_BROWSER_DIRECTORRY))
	{
		if (ImGui::Button("<---"))
		{
			m_Path = m_Path.parent_path();
		}
	}

	static float padding = 16.0f;
	static float thumbnailSize = 107.0f;
	float cellSize = thumbnailSize + padding;
	static float buttonSize = 70.0f;
	float panelWidth = ImGui::GetContentRegionAvail().x;
	int columnCount = (int)(panelWidth / cellSize);
	if (columnCount < 1)
		columnCount = 1;

	ImGui::Columns(columnCount, 0, false);

	for (auto& p : std::filesystem::directory_iterator(m_Path))
	{
		const auto& path = p.path();
		auto relativePath = std::filesystem::relative(path, CONTENT_BROWSER_DIRECTORRY);
		std::string fileNameString = relativePath.filename().string();

		ImGui::PushID(fileNameString.c_str());
		auto texture = p.is_directory() ? m_DirectoryTexture : m_FileTexture;
		ImGui::PushStyleColor(ImGuiCol_Button, { 0, 0, 0, 0 });
		ImGui::ImageButton((ImTextureID)texture->GetRendererId(), { buttonSize, buttonSize }, { 0, 1 }, { 1, 0 });

		if (!p.is_directory() && ImGui::BeginDragDropSource())
		{
			std::string cString = path.string();
			//LOG_INFO(cString.c_str()+ "    size:" + std::to_string(cString.size()));
			ImGui::SetDragDropPayload("CONTENT_BROWSER_ITEM", cString.c_str(), cString.size(), ImGuiCond_Once);
			ImGui::EndDragDropSource();
		}
		ImGui::PopStyleColor();
		if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
		{
			if (p.is_directory())
			{
				m_Path /= path.filename();	
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

END_ENTERNITY

