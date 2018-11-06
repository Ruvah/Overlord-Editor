
#include "stdafx.h"

#include "ColorMaterial_Deferred.h"


ColorMaterial_Deferred::ColorMaterial_Deferred() :
	Material(L"./Resources/Effects/Deferred/PosNormCol3D_Deferred.fx")
{
}


ColorMaterial_Deferred::~ColorMaterial_Deferred()
{
}

void ColorMaterial_Deferred::LoadEffectVariables()
{

}

void ColorMaterial_Deferred::UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent)
{
	UNREFERENCED_PARAMETER(gameContext);
	UNREFERENCED_PARAMETER(pModelComponent);
}
