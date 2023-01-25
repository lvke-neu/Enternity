#include "RenderSystem.h"

BEGIN_ENTERNITY

void RenderSystem::DrawSkyBox(Entity& cameraEntity, Entity& entity)
{
	
	if (cameraEntity.HasComponent<TransformComponent>()
		&& cameraEntity.HasComponent<CameraComponent>())
	{
		glDepthFunc(GL_LEQUAL);

		auto& cameraTransformComponent = cameraEntity.GetComponent<TransformComponent>();
		auto& cameraCameraComponent = cameraEntity.GetComponent<CameraComponent>();

		auto& meshComponent = entity.GetComponent<MeshComponent>();
		auto& skyboxComponet = entity.GetComponent<SkyBoxComponent>();
		skyboxComponet.m_Shader->Bind();
		skyboxComponet.m_SkyBoxTexture->Bind();
		skyboxComponet.m_Shader->SetInteger1("skybox", 0);
		skyboxComponet.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * glm::mat4(glm::mat3(cameraTransformComponent.GetInverseWorldMatrix())));
		meshComponent.m_VertexArray->Bind();
		meshComponent.m_Indexbuffer->Bind();
		CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
		glDepthFunc(GL_LESS);
	}

}

void RenderSystem::DrawEntity(Entity& cameraEntity, Entity& entity, const Entity& lightEntity)
{
	if (cameraEntity.HasComponent<TransformComponent>()
		&& cameraEntity.HasComponent<CameraComponent>())
	{
		auto& cameraTransformComponent = cameraEntity.GetComponent<TransformComponent>();
		auto& cameraCameraComponent = cameraEntity.GetComponent<CameraComponent>();

		if (entity.HasComponent<TransformComponent>() && entity.HasComponent<MeshComponent>() && entity.HasComponent<MaterialComponent>())
		{
			auto& transformComponent = entity.GetComponent<TransformComponent>();
			auto& meshComponent = entity.GetComponent<MeshComponent>();
			auto& materialComponent = entity.GetComponent<MaterialComponent>();

			if (meshComponent.m_VertexArray)
				meshComponent.m_VertexArray->Bind();

			if (materialComponent.m_Shader)
			{
				materialComponent.m_Shader->Bind();
				materialComponent.m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * transformComponent.GetWorldMatrix());
				materialComponent.m_Shader->SetInteger1("u_entityId", entity.GetEntityUid());

				materialComponent.m_Shader->SetMat4f("u_m", transformComponent.GetWorldMatrix());
				materialComponent.m_Shader->SetMat4f("u_inverseTransposeM", glm::transpose(glm::inverse(transformComponent.GetWorldMatrix())));
				
				if (lightEntity.IsValidEntity())
				{
					materialComponent.m_Shader->SetFloat3("u_lightPos", lightEntity.GetComponent<TransformComponent>().m_Translation);
					materialComponent.m_Shader->SetFloat4("u_lightSpecular", lightEntity.GetComponent<MaterialComponent>().m_Specular);
					materialComponent.m_Shader->SetFloat4("u_lightDiffuse", lightEntity.GetComponent<MaterialComponent>().m_Diffuse);
					materialComponent.m_Shader->SetFloat4("u_lightAmbient", lightEntity.GetComponent<MaterialComponent>().m_Ambient);
				}
			

				materialComponent.m_Shader->SetFloat3("u_cameraPos", cameraTransformComponent.m_Translation);
				materialComponent.m_Shader->SetFloat4("u_entityAmbient", materialComponent.m_Ambient);
				materialComponent.m_Shader->SetFloat4("u_entityDiffuse", materialComponent.m_Diffuse);
				materialComponent.m_Shader->SetFloat4("u_entitySpecular", materialComponent.m_Specular);
				materialComponent.m_Shader->SetInteger1("u_shininess", (int)materialComponent.m_Shininess);

			}

			if (materialComponent.m_DiffuseTexture)
				materialComponent.m_DiffuseTexture->Bind(0);
			if (materialComponent.m_SpecularTexture)
				materialComponent.m_SpecularTexture->Bind(1);


			if (meshComponent.m_Indexbuffer)
			{
				meshComponent.m_Indexbuffer->Bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
			}
			//unbind
			if (meshComponent.m_VertexArray)
				meshComponent.m_VertexArray->UnBind();

			if (materialComponent.m_Shader)
			{
				materialComponent.m_Shader->UnBind();
			}
			if (materialComponent.m_DiffuseTexture)
				materialComponent.m_DiffuseTexture->UnBind();
			if (materialComponent.m_SpecularTexture)
				materialComponent.m_SpecularTexture->UnBind();
			if (meshComponent.m_Indexbuffer)
			{
				meshComponent.m_Indexbuffer->UnBind();
			}
		}

	}	
}

void RenderSystem::DrawColliderShape(Entity& cameraEntity, Entity& entity, const Entity& lightEntity)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	DrawEntity(cameraEntity, entity, lightEntity);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

END_ENTERNITY