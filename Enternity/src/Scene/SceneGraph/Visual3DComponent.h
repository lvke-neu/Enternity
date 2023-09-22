#pragma once
#include "Engine/Component.h"

namespace Enternity
{
	class Visual3D;
	class Visual3DComponent : public Component
	{
		RTTR_ENABLE(Component);
	public:
		Visual3DComponent() = default;
		Visual3DComponent(Visual3D* visual3D);
		virtual ~Visual3DComponent();
	public:
		GET_CLASS_NAME(Visual3DComponent);
	public:
		GET_SET(Visual3D*, visual3D);
	public:
		virtual void command() override;
		virtual void onAttachToNode(Node* node) override;
	protected:
		Visual3D* m_visual3D;
	};
}