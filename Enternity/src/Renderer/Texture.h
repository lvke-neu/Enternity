/***************************************************************************************
Author: lvke
Date:2022/12/31 21:50
Description:
Encapsulate  Texture
****************************************************************************************/
#pragma once

#include "Interface/BindableInterface.h"
#include <string>

BEGIN_ENTERNITY

class Texture : public IBindable
{
public:
	Texture() = default;
	Texture(const std::string& filePath);
	virtual ~Texture();
	
	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;
private:
	unsigned char* m_localBuffer{ nullptr };
	int m_width{ 0 };
	int m_height{ 0 };
	int m_channels{ 0 };
};

END_ENTERNITY
