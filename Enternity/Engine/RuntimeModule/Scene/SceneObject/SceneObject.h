#pragma once
#include "Core/UUID/UUID.h"
#include "Core/Math/Vector.h"
#include <vector>

namespace Enternity
{
	enum class SceneObjectType
	{
		Mesh,
		Material,
		Texture,
		Light,
		Camera,
		Animator,
		Clip
	};

	class SceneObject
	{
	protected:
		SceneObject(SceneObjectType type) :m_type(type)
		{
			m_uuid = UUID::Generate();
		}
	public:
		std::string getUuid() const
		{
			return m_uuid;
		}
		SceneObjectType getType()
		{
			return m_type;
		}
	private:
		std::string m_uuid;
		SceneObjectType m_type;
	};

	class Blob;

	class SceneObjectVertexBuffer : public SceneObject
	{
	protected:
		Blob* m_data;
	};

	class SceneObjectIndexBuffer : public SceneObject
	{
	protected:
		Blob* m_data;
	};

	class SceneObjectMesh : public SceneObject
	{
	public:
		SceneObjectMesh() : SceneObject(SceneObjectType::Mesh)
		{

		}
	protected:
		std::vector<SceneObjectVertexBuffer> m_vertexBuffer;
		std::vector<SceneObjectIndexBuffer> m_indexBuffer;

		bool        m_bVisible = true;
		bool        m_bShadow = false;
		bool        m_bMotionBlur = false;
	};

	class SceneObjectMaterial : public SceneObject
	{
	public:
		SceneObjectMaterial() : SceneObject(SceneObjectType::Material)
		{

		}
	protected:
		std::string m_baseColorTexture;
		std::string m_normalTexture;
		std::string m_metallicTexture;
		std::string m_roughnessTexture;
		Vector4f m_emissive;
		Vector4f m_occlusion;
	};

	class SceneObjectDirectionLight : public SceneObject
	{
	protected:
		SceneObjectDirectionLight() : SceneObject(SceneObjectType::Light)
		{

		}
	protected:
		Vector3f m_direction;
		Vector4f m_color;
	};

	class SceneObjcetCamera : public SceneObject
	{
	protected:
		float m_fov;
		float m_nearZ;
		float m_farZ;
	public:
		SceneObjcetCamera() : SceneObject(SceneObjectType::Camera)
		{

		}
	};
}