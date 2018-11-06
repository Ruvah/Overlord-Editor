#pragma once
#include "..\OverlordEngine\Material.h"

class TextureData;

class DiffuseMaterial_Deferred : public Material
{
public:
	DiffuseMaterial_Deferred();
	~DiffuseMaterial_Deferred();

	void SetDiffuseTexture(const std::wstring& assetFile);

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

	TextureData* m_pDiffuseTexture;
	static ID3DX11EffectShaderResourceVariable* m_pDiffuseSRVvariable;

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	DiffuseMaterial_Deferred(const DiffuseMaterial_Deferred &obj);
	DiffuseMaterial_Deferred& operator=(const DiffuseMaterial_Deferred& obj);
};

