
#include "stdafx.h"

#include "SkyBoxMaterial.h"

#include "..\OverlordEngine\ContentManager.h"
#include "..\OverlordEngine\TextureData.h"

ID3DX11EffectShaderResourceVariable* SkyBoxMaterial::m_pCubeSRVvariable = nullptr;

SkyBoxMaterial::SkyBoxMaterial() : Material(L"./Resources/Effects/SkyBox.fx"),
	m_pCubeTexture(nullptr)
{
}


SkyBoxMaterial::~SkyBoxMaterial()
{

}

void SkyBoxMaterial::SetCubeMapTexture(const std::wstring& assetFile)
{
	m_pCubeTexture = ContentManager::Load<TextureData>(assetFile);
}

void SkyBoxMaterial::LoadEffectVariables()
{
	if (!m_pCubeSRVvariable)
	{
		m_pCubeSRVvariable = GetEffect()->GetVariableByName("m_CubeMap")->AsShaderResource();
		if (!m_pCubeSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'m_CubeMap\' variable not found!");
			m_pCubeSRVvariable = nullptr;
		}
	}
}

void SkyBoxMaterial::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pCubeTexture && m_pCubeSRVvariable)
	{
		m_pCubeSRVvariable->SetResource(m_pCubeTexture->GetShaderResourceView());
	}
}