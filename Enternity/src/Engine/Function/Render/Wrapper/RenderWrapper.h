/***************************************************************************************
Author: lvke
Date:
Description:
Render Wrapper
****************************************************************************************/
#pragma once
#include "Core/Basic/Macro.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Texture.h"
#include "Shader.h"

namespace Enternity
{
	class RenderWrapper
	{
	public:
		template<typename T>
		static T* Create();

		template<typename T>
		static void Destroy(T*& t);
	};

	template<typename T>
	T* RenderWrapper::Create()
	{
		return new T;
	}

	template<typename T>
	void RenderWrapper::Destroy(T*& t)
	{
		if(t)
			t->Destroy();
		SAFE_DELETE_SET_NULL(t);
	}
}