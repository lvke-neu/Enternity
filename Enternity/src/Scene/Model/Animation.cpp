#include "Animation.h"
#include "ModelBlobHolder.h"
#include <assimp/scene.h>

namespace Enternity
{
	Animation::Animation(const aiScene* scene, int animationIndex, const std::map<std::string, BoneInfo>& boneInfoMap, int boneCounter)
	{
		if (animationIndex < 0 || (unsigned int)animationIndex > (scene->mNumAnimations - 1))
		{
			return;
		}

		auto animation = scene->mAnimations[animationIndex];
		m_Duration = (float)animation->mDuration;
		m_TicksPerSecond = (int)animation->mTicksPerSecond;
		aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
		globalTransformation = globalTransformation.Inverse();
		ReadHierarchyData(m_RootNode, scene->mRootNode);
		ReadMissingBones(animation, boneInfoMap, boneCounter);
	}

	Bone* Animation::FindBone(const std::string& name)
	{
		auto iter = std::find_if(m_Bones.begin(), m_Bones.end(),
			[&](const Bone& Bone)
			{
				return Bone.GetBoneName() == name;
			}
		);
		if (iter == m_Bones.end()) return nullptr;
		else return &(*iter);
	}

	Animation* Animation::clone()
	{
		Animation* animation = new Animation;
		animation->m_Duration = this->m_Duration;
		animation->m_TicksPerSecond = this->m_TicksPerSecond;
		animation->m_Bones = this->m_Bones;
		animation->m_RootNode = this->m_RootNode;
		animation->m_BoneInfoMap = this->m_BoneInfoMap;


		return animation;
	}

	void Animation::ReadMissingBones(const aiAnimation* animation, const std::map<std::string, BoneInfo>& boneInfoMap, int boneCounter)
	{
		int size = animation->mNumChannels;

		std::map<std::string, BoneInfo> tmpBoneInfoMap = boneInfoMap;


		//reading channels(bones engaged in an animation and their keyframes)
		for (int i = 0; i < size; i++)
		{
			auto channel = animation->mChannels[i];
			std::string boneName = channel->mNodeName.data;

			if (tmpBoneInfoMap.find(boneName) == tmpBoneInfoMap.end())
			{
				tmpBoneInfoMap[boneName].id = boneCounter;
				boneCounter++;
			}
			m_Bones.push_back(Bone(channel->mNodeName.data,
				tmpBoneInfoMap[channel->mNodeName.data].id, channel));
		}

		m_BoneInfoMap = tmpBoneInfoMap;
	}

	void Animation::ReadHierarchyData(AssimpNodeData& dest, const aiNode* src)
	{
		dest.name = src->mName.data;
		dest.transformation = AssimpGLMHelpers::ConvertMatrixToGLMFormat(src->mTransformation);
		dest.childrenCount = src->mNumChildren;

		for (unsigned int i = 0; i < src->mNumChildren; i++)
		{
			AssimpNodeData newData;
			ReadHierarchyData(newData, src->mChildren[i]);
			dest.children.push_back(newData);
		}
	}
}