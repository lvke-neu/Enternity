/***************************************************************************************
Author: lvke
Date:
Description:
Encapsulate  SkyBox Texture
****************************************************************************************/
#pragma once

#include "Texture.h"

BEGIN_ENTERNITY

class SkyBoxTexture : public Texture
{
public:
	SkyBoxTexture(const std::vector<std::string>& filePaths);
	virtual ~SkyBoxTexture();

	virtual void Bind(unsigned int slot = 0) const override;
	virtual void UnBind() const override;
};

END_ENTERNITY