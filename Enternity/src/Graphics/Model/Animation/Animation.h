#pragma once
#include "bone.h"
#include "AnimationDefine.h"
#include <map>

struct aiScene;
namespace Enternity
{
	class Animation
	{
	public:
		Animation() = default;
		Animation(const aiScene* scene, int animationIndex, const std::map<std::string, BoneInfo>& boneInfoMap, int boneCounter);
	public:
		Bone* FindBone(const std::string& name);

		inline float GetTicksPerSecond() { return m_TicksPerSecond * m_coefficient; }
		inline float GetDuration() { return m_Duration; }
		inline const AssimpNodeData& GetRootNode() { return m_RootNode; }
		inline const std::map<std::string, BoneInfo>& GetBoneIDMap() { return m_BoneInfoMap; }

		Animation* clone();
	public:
		inline float getCoefficient() { return m_coefficient; }
		inline void setCoefficient(float coefficient) { m_coefficient = coefficient; }
	private:
		void ReadMissingBones(const aiAnimation* animation, const std::map<std::string, BoneInfo>& boneInfoMap, int boneCounter);
		void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);
	private:
		float m_Duration;
		int m_TicksPerSecond;
		std::vector<Bone> m_Bones;
		AssimpNodeData m_RootNode;
		std::map<std::string, BoneInfo> m_BoneInfoMap;
		float m_coefficient = 1.0f;
	};
}