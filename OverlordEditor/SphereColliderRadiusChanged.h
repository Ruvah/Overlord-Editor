#pragma once
#include "Command.h"
class SphereColliderComponent;
class SphereColliderRadiusChanged :
	public Command
{
public:
	SphereColliderRadiusChanged(float newRad, SphereColliderComponent* pComp);
	virtual ~SphereColliderRadiusChanged()=default;

	virtual void Execute() override;
	virtual void Undo() override;

private:
	float m_New, m_Old;
	UINT m_ID;
};

