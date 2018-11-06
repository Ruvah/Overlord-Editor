#include "stdafx.h"
#include "SphereColliderRotChangeCmd.h"
#include <SphereColliderComponent.h>


SphereColliderRotChangeCmd::SphereColliderRotChangeCmd(physx::PxVec3 newrot, SphereColliderComponent * pComp)
	: m_ID{ pComp->GetID() },
	m_New{ newrot },
	m_Old{ pComp->GetRotation() }
{
}

void SphereColliderRotChangeCmd::Execute()
{
	Command::Execute();
	SphereColliderComponent* pComp(BaseComponent::GetComponent<SphereColliderComponent>(m_ID));
	pComp->SetAngles(m_New);
	Notify(OVLEvent::ColliderCompChanged);

}

void SphereColliderRotChangeCmd::Undo()
{
	Command::Undo();
	SphereColliderComponent* pComp(BaseComponent::GetComponent<SphereColliderComponent>(m_ID));
	pComp->SetAngles(m_New);
	Notify(OVLEvent::ColliderCompChanged);
}
