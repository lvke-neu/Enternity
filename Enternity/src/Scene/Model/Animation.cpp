#include "Animation.h"
#include "ModelBlobHolder.h"
#include <assimp/scene.h>

namespace Enternity
{
	Animation::Animation(const aiScene* scene, ModelBlobHolder* modelBlobHolder)
	{
		if (scene->mNumAnimations == 0)
		{
			return;
		}

		auto animation = scene->mAnimations[0];
		m_Duration = (float)animation->mDuration;
		m_TicksPerSecond = (float)animation->mTicksPerSecond;
		aiMatrix4x4 globalTransformation = scene->mRootNode->mTransformation;
		globalTransformation = globalTransformation.Inverse();
		ReadHierarchyData(m_RootNode, scene->mRootNode);
		ReadMissingBones(animation, modelBlobHolder);
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

	void Animation::ReadMissingBones(const aiAnimation* animation, ModelBlobHolder* modelBlobHolder)
	{
		int size = animation->mNumChannels;

		auto& boneInfoMap = modelBlobHolder->m_boneInfoMap;//getting m_BoneInfoMap from Model class
		int& boneCount = modelBlobHolder->m_boneCounter; //getting the m_BoneCounter from Model class

		//reading channels(bones engaged in an animation and their keyframes)
		for (int i = 0; i < size; i++)
		{
			auto channel = animation->mChannels[i];
			std::string boneName = channel->mNodeName.data;

			if (boneInfoMap.find(boneName) == boneInfoMap.end())
			{
				boneInfoMap[boneName].id = boneCount;
				boneCount++;
			}
			m_Bones.push_back(Bone(channel->mNodeName.data,
				boneInfoMap[channel->mNodeName.data].id, channel));
		}

		m_BoneInfoMap = boneInfoMap;
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