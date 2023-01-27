#include "RenderSystem.h"
#include "Scene/ShadowMap/ShadowMapManager.h"


BEGIN_ENTERNITY

#define ORTHO_LENGTH 10.0f

RenderSystem::RenderSystem()
{
	m_ShadowMapShader = new Shader("assets/shaders/ShadowMap.glsl");
	m_LightOrthoProjectMatrix = glm::ortho(-ORTHO_LENGTH, ORTHO_LENGTH, -ORTHO_LENGTH, ORTHO_LENGTH, 1.0f, 100.0f);
}

RenderSystem::~RenderSystem()
{
	SAFE_DELETE_SET_NULL(m_ShadowMapShader);
}

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

void RenderSystem::DrawShadowMap(Entity& entity, const Entity& lightEntity)
{
	//draw simple entity
	if (entity.HasComponent<TransformComponent>() && entity.HasComponent<MeshComponent>() && entity.HasComponent<MaterialComponent>())
	{
		glm::mat4 viewMatrix = glm::lookAt(lightEntity.GetComponent<TransformComponent>().m_Translation, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


		auto& transformComponent = entity.GetComponent<TransformComponent>();
		auto& meshComponent = entity.GetComponent<MeshComponent>();
		auto& materialComponent = entity.GetComponent<MaterialComponent>();

		if (meshComponent.m_VertexArray)
			meshComponent.m_VertexArray->Bind();

		
		m_ShadowMapShader->Bind();
		m_ShadowMapShader->SetMat4f("u_mvp", m_LightOrthoProjectMatrix * viewMatrix * transformComponent.GetWorldMatrix());

		if (meshComponent.m_Indexbuffer)
		{
			meshComponent.m_Indexbuffer->Bind();
			CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
		}
		//unbind
		if (meshComponent.m_VertexArray)
			meshComponent.m_VertexArray->UnBind();

		m_ShadowMapShader->UnBind();

		if (meshComponent.m_Indexbuffer)
		{
			meshComponent.m_Indexbuffer->UnBind();
		}
	}


	//draw model entity
	if (entity.HasComponent<ModelComponent>() && entity.HasComponent<TransformComponent>())
	{
		glm::mat4 viewMatrix = glm::lookAt(lightEntity.GetComponent<TransformComponent>().m_Translation, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));


		auto& transformComponent = entity.GetComponent<TransformComponent>();
		auto& modelc = entity.GetComponent<ModelComponent>();
		unsigned int subModelCount = (unsigned int)modelc.m_Mesh.size();

		for (unsigned int i = 0; i < subModelCount; i++)
		{
			auto& meshComponent = modelc.m_Mesh[i];
			auto& materialComponent = modelc.m_Material[i];

			if (meshComponent.m_VertexArray)
				meshComponent.m_VertexArray->Bind();


			m_ShadowMapShader->Bind();
			m_ShadowMapShader->SetMat4f("u_mvp", m_LightOrthoProjectMatrix * viewMatrix * transformComponent.GetWorldMatrix());

			if (meshComponent.m_Indexbuffer)
			{
				meshComponent.m_Indexbuffer->Bind();
				CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, meshComponent.m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
			}
			//unbind
			if (meshComponent.m_VertexArray)
				meshComponent.m_VertexArray->UnBind();

			m_ShadowMapShader->UnBind();

			if (meshComponent.m_Indexbuffer)
			{
				meshComponent.m_Indexbuffer->UnBind();
			}
		}
	}
}

void RenderSystem::DrawEntity(Entity& cameraEntity, Entity& entity, const Entity& lightEntity)
{
	if (cameraEntity.HasComponent<TransformComponent>()
		&& cameraEntity.HasComponent<CameraComponent>())
	{
		auto& cameraTransformComponent = cameraEntity.GetComponent<TransformComponent>();
		auto& cameraCameraComponent = cameraEntity.GetComponent<CameraComponent>();


		//draw model
		if (entity.HasComponent<ModelComponent>() && entity.HasComponent<TransformComponent>())
		{
			auto& modelc = entity.GetComponent<ModelComponent>();
			auto& transc = entity.GetComponent<TransformComponent>();
			glm::mat4 viewMatrix = glm::lookAt(lightEntity.GetComponent<TransformComponent>().m_Translation, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

			unsigned int subModelCount = (unsigned int)modelc.m_Mesh.size();

			for (unsigned int i = 0; i < subModelCount; i++)
			{
				if (modelc.m_Mesh[i].m_VertexArray)
					modelc.m_Mesh[i].m_VertexArray->Bind();


				if (modelc.m_Material[i].m_Shader)
				{
					modelc.m_Material[i].m_Shader->Bind();
					modelc.m_Material[i].m_Shader->SetMat4f("u_mvp", cameraCameraComponent.m_ProjectMatrix * cameraTransformComponent.GetInverseWorldMatrix() * transc.GetWorldMatrix());
					modelc.m_Material[i].m_Shader->SetInteger1("u_entityId", entity.GetEntityUid());

					modelc.m_Material[i].m_Shader->SetMat4f("u_m", transc.GetWorldMatrix());
					modelc.m_Material[i].m_Shader->SetMat4f("u_inverseTransposeM", glm::transpose(glm::inverse(transc.GetWorldMatrix())));

					if (lightEntity.IsValidEntity())
					{
						modelc.m_Material[i].m_Shader->SetFloat3("u_lightPos", lightEntity.GetComponent<TransformComponent>().m_Translation);
						modelc.m_Material[i].m_Shader->SetFloat4("u_lightSpecular", lightEntity.GetComponent<MaterialComponent>().m_Specular);
						modelc.m_Material[i].m_Shader->SetFloat4("u_lightDiffuse", lightEntity.GetComponent<MaterialComponent>().m_Diffuse);
						modelc.m_Material[i].m_Shader->SetFloat4("u_lightAmbient", lightEntity.GetComponent<MaterialComponent>().m_Ambient);
					}


					modelc.m_Material[i].m_Shader->SetFloat3("u_cameraPos", cameraTransformComponent.m_Translation);
					modelc.m_Material[i].m_Shader->SetFloat4("u_entityAmbient", modelc.m_Material[i].m_Ambient);
					modelc.m_Material[i].m_Shader->SetFloat4("u_entityDiffuse", modelc.m_Material[i].m_Diffuse);
					modelc.m_Material[i].m_Shader->SetFloat4("u_entitySpecular", modelc.m_Material[i].m_Specular);
					modelc.m_Material[i].m_Shader->SetInteger1("u_shininess", (int)modelc.m_Material[i].m_Shininess);

					//shadow map u_lightSpaceMatrix
					modelc.m_Material[i].m_Shader->SetMat4f("u_lightSpaceMatrix", m_LightOrthoProjectMatrix * viewMatrix);
					ShadowMapManager::GetInstance().BindShadowMap(2);

				}


				if (modelc.m_Material[i].m_DiffuseTexture)
					modelc.m_Material[i].m_DiffuseTexture->Bind(0);
				if (modelc.m_Material[i].m_SpecularTexture)
					modelc.m_Material[i].m_SpecularTexture->Bind(1);


				if (modelc.m_Mesh[i].m_Indexbuffer)
				{
					modelc.m_Mesh[i].m_Indexbuffer->Bind();
					CHECK_GL_CALL(glDrawElements(GL_TRIANGLES, modelc.m_Mesh[i].m_Indexbuffer->GetCount(), GL_UNSIGNED_INT, (void*)0));
				}

				//unbind
				if (modelc.m_Mesh[i].m_VertexArray)
					modelc.m_Mesh[i].m_VertexArray->UnBind();

				if (modelc.m_Material[i].m_Shader)
				{
					modelc.m_Material[i].m_Shader->UnBind();
				}

				if (modelc.m_Material[i].m_DiffuseTexture)
					modelc.m_Material[i].m_DiffuseTexture->UnBind();
				if (modelc.m_Material[i].m_SpecularTexture)
					modelc.m_Material[i].m_SpecularTexture->UnBind();
				if (modelc.m_Mesh[i].m_Indexbuffer)
				{
					modelc.m_Mesh[i].m_Indexbuffer->UnBind();
				}
			}
			return;
		}

		//draw simple entity
		if (entity.HasComponent<TransformComponent>() && entity.HasComponent<MeshComponent>() && entity.HasComponent<MaterialComponent>())
		{
			auto& transformComponent = entity.GetComponent<TransformComponent>();
			auto& meshComponent = entity.GetComponent<MeshComponent>();
			auto& materialComponent = entity.GetComponent<MaterialComponent>();

			glm::mat4 viewMatrix = glm::lookAt(lightEntity.GetComponent<TransformComponent>().m_Translation, glm::vec3(0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

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

				//shadow map u_lightSpaceMatrix
				materialComponent.m_Shader->SetMat4f("u_lightSpaceMatrix", m_LightOrthoProjectMatrix * viewMatrix);
				ShadowMapManager::GetInstance().BindShadowMap(2);

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