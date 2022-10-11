#pragma once

#include "Texture.h"

class OGTexture : public Texture
{
public:
	OGTexture() {}
	OGTexture(const std::string& path);
	~OGTexture();

	virtual void LoadTexture(const std::string& path) override;
	virtual void InitTexture() override {}

public:
	void BindTexture() const override;
	void UnBindTexture() const override;
};