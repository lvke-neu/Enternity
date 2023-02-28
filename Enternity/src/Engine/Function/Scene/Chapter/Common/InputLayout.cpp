#include "InputLayout.h"

namespace Enternity
{
	bool InputLayout::bInit = false;
	VertexBufferLayout InputLayout::VertexBufferLayout_POS_COLOR;

	void InputLayout::Init()
	{
		if (bInit)
			return;

		bInit = true;

		VertexBufferLayout_POS_COLOR.push({ 0, 3, GL_FLOAT, false,  6 * sizeof(float), 0 });
		VertexBufferLayout_POS_COLOR.push({ 1, 3, GL_FLOAT, false,  6 * sizeof(float), 3 * sizeof(float) });	
	}
}