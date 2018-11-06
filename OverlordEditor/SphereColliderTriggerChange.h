#pragma once
#include "Command.h"
class SphereColliderComponent;
class SphereColliderTriggerChange :
	public Command
{
public:
	SphereColliderTriggerChange(bool val, SphereColliderComponent* pComp);
	virtual ~SphereColliderTriggerChange()= default;

	virtual void Execute() override;
	virtual void Undo() override;
private:

	bool m_New;
	UINT m_ID;
};

