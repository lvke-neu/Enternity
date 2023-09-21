#pragma once
#include "Engine/Component.h"
#include <vector>

namespace Enternity
{
	class Visual3D;
	class Model;
	class Model3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Model3DComponent() = default;
		Model3DComponent(Model* model);
		virtual ~Model3DComponent();
	public:
		GET_CLASS_NAME(Model3DComponent);
	public:
		GET_SET(std::vector<Visual3D*>, visual3Ds);
		GET_SET(bool, wireFrame);
	public:
		virtual void command() override;
		virtual void onAttachToNode(Node* node) override;		
	private:
		bool m_wireFrame;
		std::vector<Visual3D*> m_visual3Ds;
	};
}