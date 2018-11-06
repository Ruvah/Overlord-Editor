#pragma once
#include "..\OverlordEngine\Material.h"

class ColorMaterial_Deferred: public Material
{
public:
	ColorMaterial_Deferred();
	~ColorMaterial_Deferred();

protected:
	virtual void LoadEffectVariables();
	virtual void UpdateEffectVariables(const GameContext& gameContext, ModelComponent* pModelComponent);

private:

private:
	// -------------------------
	// Disabling default copy constructor and default 
	// assignment operator.
	// -------------------------
	ColorMaterial_Deferred(const ColorMaterial_Deferred &obj);
	ColorMaterial_Deferred& operator=(const ColorMaterial_Deferred& obj);
};

