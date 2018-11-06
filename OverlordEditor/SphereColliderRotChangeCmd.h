#pragma once
#include "Command.h"
class SphereColliderComponent;
class SphereColliderRotChangeCmd :
	public Command
{
public:
	SphereColliderRotChangeCmd(physx::PxVec3 newrot, SphereColliderComponent*pComp);
	virtual ~SphereColliderRotChangeCmd() = default;

	virtual void Execute() override;
	virtual void Undo() override;

private:
	physx::PxVec3 m_Old, m_New;
	UINT m_ID;
};

