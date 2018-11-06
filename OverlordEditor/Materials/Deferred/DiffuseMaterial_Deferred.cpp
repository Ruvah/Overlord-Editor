
#include "stdafx.h"

#include "DiffuseMaterial_Deferred.h"

#include "..\OverlordEngine\ContentManager.h"
#include "..\OverlordEngine\TextureData.h"

ID3DX11EffectShaderResourceVariable* DiffuseMaterial_Deferred::m_pDiffuseSRVvariable = nullptr;

DiffuseMaterial_Deferred::DiffuseMaterial_Deferred() : 
	Material(L"./Resources/Effects/Deferred/PosNormTex3D_Deferred.fx"),
	m_pDiffuseTexture(nullptr)
{
}


DiffuseMaterial_Deferred::~DiffuseMaterial_Deferred()
{

}

void DiffuseMaterial_Deferred::SetDiffuseTexture(const std::wstring& assetFile)
{
	m_pDiffuseTexture = ContentManager::Load<TextureData>(assetFile);
}

void DiffuseMaterial_Deferred::LoadEffectVariables()
{
	if (!m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable = GetEffect()->GetVariableByName("gDiffuseMap")->AsShaderResource();
		if (!m_pDiffuseSRVvariable->IsValid())
		{
			Logger::LogWarning(L"DiffuseMaterial::LoadEffectVariables() > \'gDiffuseMap\' variable not found!");
			m_pDiffuseSRVvariable = nullptr;
		}
	}
}

void DiffuseMaterial_Deferred::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);

	if (m_pDiffuseTexture && m_pDiffuseSRVvariable)
	{
		m_pDiffuseSRVvariable->SetResource(m_pDiffuseTexture->GetShaderResourceView());
	}
}