#pragma warning(disable:4312) 

#include "ViewPortPanel.h"
#include "Engine/Engine.h"
#include "Engine/RenderView.h"
#include "Engine/EventSystem.h"
#include "Graphics/GraphicsSystem.h"
#include "Graphics/RHI/FrameBuffer/FrameBuffer.h"
#include "Scene/Scene.h"
#include "Scene/SceneManager.h"
#include "Scene/ECS/TransformComponent.h"
#include "Scene/ECS/CameraComponent.h"
#include "Scene/ECS/SunLightComponent.h"
#include "Pick/PickSystem.h"
#include "Imgui/imgui.h"
#include "Imgui/imgui_internal.h"
#include "Imgui/imgui_impl_glfw.h"
#include "Imgui/imgui_impl_opengl3.h"
#include "ImGui/ImGuizmo.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_decompose.hpp>

namespace Enternity
{
	bool DecomposeTransform(const glm::mat4& transform, glm::vec3& translation, glm::vec3& rotation, glm::vec3& scale)
	{
		// From glm::decompose in matrix_decompose.inl

		using namespace glm;
		using T = float;

		mat4 LocalMatrix(transform);

		// Normalize the matrix.
		if (epsilonEqual(LocalMatrix[3][3], static_cast<float>(0), epsilon<T>()))
			return false;

		// First, isolate perspective.  This is the messiest.
		if (
			epsilonNotEqual(LocalMatrix[0][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[1][3], static_cast<T>(0), epsilon<T>()) ||
			epsilonNotEqual(LocalMatrix[2][3], static_cast<T>(0), epsilon<T>()))
		{
			// Clear the perspective partition
			LocalMatrix[0][3] = LocalMatrix[1][3] = LocalMatrix[2][3] = static_cast<T>(0);
			LocalMatrix[3][3] = static_cast<T>(1);
		}

		// Next take care of translation (easy).
		translation = vec3(LocalMatrix[3]);
		LocalMatrix[3] = vec4(0, 0, 0, LocalMatrix[3].w);

		vec3 Row[3];

		// Now get scale and shear.
		for (length_t i = 0; i < 3; ++i)
			for (length_t j = 0; j < 3; ++j)
				Row[i][j] = LocalMatrix[i][j];

		// Compute X scale factor and normalize first row.
		scale.x = length(Row[0]);
		Row[0] = detail::scale(Row[0], static_cast<T>(1));
		scale.y = length(Row[1]);
		Row[1] = detail::scale(Row[1], static_cast<T>(1));
		scale.z = length(Row[2]);
		Row[2] = detail::scale(Row[2], static_cast<T>(1));

		// At this point, the matrix (in rows[]) is orthonormal.
		// Check for a coordinate system flip.  If the determinant
		// is -1, then negate the matrix and the scaling factors.

		rotation.y = asin(-Row[0][2]);
		if (cos(rotation.y) != 0) {
			rotation.x = atan2(Row[1][2], Row[2][2]);
			rotation.z = atan2(Row[0][1], Row[0][0]);
		}
		else {
			rotation.x = atan2(-Row[2][0], Row[1][1]);
			rotation.z = 0;
		}


		return true;
	}

	void ViewPortPanel::draw()
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 0, 0 });

		ImGui::Begin("Viewport");

		Engine::GetInstance().getEventSystem()->setIsDispatchInputEvent(ImGui::IsWindowHovered());

		onViewPortResize();

		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::D1))
		{
			m_gizmoOperation = ImGuizmo::TRANSLATE;
		}
		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::D2))
		{
			m_gizmoOperation = ImGuizmo::ROTATE;
		}
		if (Engine::GetInstance().getEventSystem()->isKeyPressed(KeyCode::D3))
		{
			m_gizmoOperation = ImGuizmo::SCALE;
		}
		//if (ImGui::RadioButton("TRANSLATE", m_gizmoOperation == ImGuizmo::TRANSLATE)) { m_gizmoOperation = ImGuizmo::TRANSLATE; } ImGui::SameLine();
		//if (ImGui::RadioButton("ROTATE", m_gizmoOperation == ImGuizmo::ROTATE)) { m_gizmoOperation = ImGuizmo::ROTATE; } ImGui::SameLine();
		//if (ImGui::RadioButton("SCALE", m_gizmoOperation == ImGuizmo::SCALE)) { m_gizmoOperation = ImGuizmo::SCALE; }

		auto id = Engine::GetInstance().getGraphicsSystem()->getPostprocessFrameBuffer()->getTextureId(0);
		ImGui::Image((void*)id, ImGui::GetContentRegionAvail(), { 0, 1 }, { 1, 0 });
		
		onSelectEntityInPanel();
		//onSelectEntityInScene();
		
		ImGui::End();

		ImGui::PopStyleVar();
	}

	void ViewPortPanel::onViewPortResize()
	{
		auto viewport = ImGui::GetContentRegionAvail();
		if (m_width != viewport.x || m_height != viewport.y)
		{
			m_width = (unsigned int)viewport.x;
			m_height = (unsigned int)viewport.y;
			Engine::GetInstance().getRenderView()->Resize(m_width, m_height);
		}
	}

	void ViewPortPanel::onSelectEntityInScene()
	{
		auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
		auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
		auto viewportOffset = ImGui::GetWindowPos();

		glm::vec2 viewportBounds[2];
		viewportBounds[0] = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
		viewportBounds[1] = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };

		auto[mx, my] = ImGui::GetMousePos();

		mx -= viewportBounds[0].x;
		my -= viewportBounds[0].y;

		int mouseX = (int)mx;
		int mouseY = (int)my;

		auto viewportSizeX = viewportBounds[1].x - viewportBounds[0].x;
		auto viewportSizeY = viewportBounds[1].y - viewportBounds[0].y;
		mouseY = int(viewportSizeY - my);

		if (mouseX >= 0 && mouseY >= 0 && mouseX <= viewportSizeX && mouseY <= viewportSizeY &&
			!ImGuizmo::IsUsing() &&
			Engine::GetInstance().getEventSystem()->isMousePressed(MouseCode::ButtonLeft))
		{
			int id;
			Engine::GetInstance().getGraphicsSystem()->getColorFrameBuffer()->readPixelInt(2, mouseX, mouseY, &id);
			Engine::GetInstance().getPickSystem()->setPickEntityId(id);
		}
	}

	void ViewPortPanel::onSelectEntityInPanel()
	{
		int selectedEntityId = Engine::GetInstance().getPickSystem()->getPickEntityId();

		Entity selectedEntity = Engine::GetInstance().getSceneManager()->getCurrentScene()->getEntity((entt::entity)selectedEntityId);
		if (!selectedEntity.isValidEntity())
			return;

		Entity cameraEntity = Engine::GetInstance().getSceneManager()->getCurrentScene()->getSceneCamera();

		const auto& viewMatrix = cameraEntity.getComponent<TransformComponent>().getInverseWorldMatrix();
		const auto& projMatrix = cameraEntity.getComponent<CameraComponent>().getProjectionMatrix();

		ImGuizmo::SetOrthographic(false);
		ImGuizmo::SetDrawlist();

		float windowWidth = (float)ImGui::GetWindowWidth();
		float windowHeight = (float)ImGui::GetWindowHeight();
		ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);

		if (selectedEntity.hasComponent<TransformComponent>())
		{
			auto modelMatrix = selectedEntity.getComponent<TransformComponent>().getWorldMatrix();

			ImGuizmo::Manipulate(&viewMatrix[0][0], &projMatrix[0][0], (ImGuizmo::OPERATION)m_gizmoOperation, ImGuizmo::MODE::LOCAL, &modelMatrix[0][0]);

			if (ImGuizmo::IsUsing())
			{
				auto& tc = selectedEntity.getComponent<TransformComponent>();
				DecomposeTransform(modelMatrix, tc.translation, tc.rotation, tc.scale);
				tc.rotation = glm::degrees(tc.rotation);
			}
		}
		else if (selectedEntity.hasComponent<SunLightComponent>())
		{
			TransformComponent tc;
			tc.translation = selectedEntity.getComponent<SunLightComponent>().direction;
			auto modelMatrix = tc.getWorldMatrix();
			ImGuizmo::Manipulate(&viewMatrix[0][0], &projMatrix[0][0], (ImGuizmo::OPERATION)m_gizmoOperation, ImGuizmo::MODE::LOCAL, &modelMatrix[0][0]);

			if (ImGuizmo::IsUsing())
			{
				DecomposeTransform(modelMatrix, selectedEntity.getComponent<SunLightComponent>().direction, tc.rotation, tc.scale);
			}
		}
	}
}