/***************************************************************************************
Author: lvke
Date:2022/12/31 16:30
Description:
Vertex Array
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"
#include "VertexBuffer.h"
#include <vector>


BEGIN_ENTERNITY

struct LayouElement
{
	unsigned int index;
	unsigned int count;
	unsigned int type;
	bool normalized;
	int stride;
	long long start;
};

class VertexBufferLayout
{
public:
	void Push(const LayouElement& layouElement)
	{
		m_layoutElements.push_back(layouElement);
	}
	std::vector<LayouElement> GetElements() const
	{
		return m_layoutElements;
	}
private:
	std::vector<LayouElement> m_layoutElements;
};


class VertexArray : public IBindable
{
public:
	VertexArray();
	~VertexArray();

	void Add(const VertexBuffer& vertexBuffer, const VertexBufferLayout& vertexBufferLayout);
	virtual void Bind() const override;
	virtual void UnBind() const override;
};

END_ENTERNITY