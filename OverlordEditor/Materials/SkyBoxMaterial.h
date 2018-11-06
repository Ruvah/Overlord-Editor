#pragma once
#include "..\OverlordEngine\Material.h"

class TextureData;

class SkyBoxMaterial : public Material
{
public:
	SkyBoxMaterial();
	~SkyBoxMaterial();

	void SetCubeMapTexture(const std::wstring& assetFile);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	TextureData* m_pCubeTexture;
	static ID3DX11EffectShaderResourceVariable* m_pCubeSRVvariable;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	SkyBoxMaterial(const SkyBoxMaterial &obj);
	SkyBoxMaterial& operator=(const SkyBoxMaterial& obj);
};

