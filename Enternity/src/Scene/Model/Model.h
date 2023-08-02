#pragma once
#include "Engine/Asset.h"
#include <string>
#include <vector>

namespace Enternity
{
	class Mesh;
	class Animation;
	class Animator;
	class Model : public Asset
	{
	public:
		virtual ~Model();
	public:
		virtual void load(BlobHolder* blobHolder) override;
		virtual void unload() override;
		void draw();
		const std::string& getPath();
		Animator* getAnimator();
	private:
		std::vector<Mesh*> m_meshs;
		std::string m_path;
		Animation* m_animation{ nullptr };
		Animator* m_animator{ nullptr };
	};

	inline const std::string& Model::getPath()
	{
		return m_path;
	}

	inline Animator* Model::getAnimator()
	{
		return m_animator;
	}
}