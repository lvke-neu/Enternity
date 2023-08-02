#pragma once
#include "bone.h"
#include "AnimationDefine.h"
#include <map>

struct aiScene;
namespace Enternity
{
	class ModelBlobHolder;
	class Animation
	{
	public:
		Animation() = default;
		Animation(const aiScene* scene, ModelBlobHolder* modelBlobHolder);
	public:
		Bone* FindBone(const std::string& name);

		inline float GetTicksPerSecond() { return m_TicksPerSecond; }
		inline float GetDuration() { return m_Duration; }
		inline const AssimpNodeData& GetRootNode() { return m_RootNode; }
		inline const std::map<std::string, BoneInfo>& GetBoneIDMap() { return m_BoneInfoMap; }

		Animation* clone();
	private:
		void ReadMissingBones(const aiAnimation* animation, ModelBlobHolder* modelBlobHolder);
		void ReadHierarchyData(AssimpNodeData& dest, const aiNode* src);
	private:
		float m_Duration;
		int m_TicksPerSecond;
		std::vector<Bone> m_Bones;
		AssimpNodeData m_RootNode;
		std::map<std::string, BoneInfo> m_BoneInfoMap;
	};
}