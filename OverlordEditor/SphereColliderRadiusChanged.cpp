#include "stdafx.h"
#include "SphereColliderRadiusChanged.h"
#include <SphereColliderComponent.h>

SphereColliderRadiusChanged::SphereColliderRadiusChanged(float newRad, SphereColliderComponent * pComp)
	:m_ID{ pComp->GetID() },
	m_New{ newRad },
	m_Old{pComp->GetRadius()}
{

}

void SphereColliderRadiusChanged::Execute()
{
	Command::Execute();
	SphereColliderComponent* pComp(BaseComponent::GetComponent<SphereColliderComponent>(m_ID));
	pComp->SetRadius(m_New);
	Notify(OVLEvent::ColliderCompChanged);

}

void SphereColliderRadiusChanged::Undo()
{
	Command::Undo();
	SphereColliderComponent* pComp(BaseComponent::GetComponent<SphereColliderComponent>(m_ID));
	pComp->SetRadius(m_Old);
	Notify(OVLEvent::ColliderCompChanged);
}
