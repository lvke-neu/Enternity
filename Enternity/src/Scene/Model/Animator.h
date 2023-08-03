#pragma once
#include "AnimationDefine.h"

namespace Enternity
{
	class Animation;
	class Animator
	{
	public:
		Animator(Animation* animation);
		void UpdateAnimation(float dt);
		void PlayAnimation(Animation* pAnimation);
		void CalculateBoneTransform(const AssimpNodeData* node, glm::mat4 parentTransform);
		std::vector<glm::mat4> GetFinalBoneMatrices();

		Animation* getAnimation();
	private:
		std::vector<glm::mat4> m_FinalBoneMatrices;
		Animation* m_CurrentAnimation;
		float m_CurrentTime;
		float m_DeltaTime;
	};

	inline Animation* Animator::getAnimation()
	{
		return m_CurrentAnimation;
	}
}