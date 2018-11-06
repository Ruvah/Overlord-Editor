#include "stdafx.h"
#include "SphereColliderTriggerChange.h"
#include <SphereColliderComponent.h>

SphereColliderTriggerChange::SphereColliderTriggerChange(bool val, SphereColliderComponent * pComp)
	:m_ID{ pComp->GetID() },
	m_New{val}
{
}

void SphereColliderTriggerChange::Execute()
{
	Command::Execute();
	SphereColliderComponent* pComp(BaseComponent::GetComponent<SphereColliderComponent>(m_ID));
	pComp->SetTrigger(m_New);
	Notify(OVLEvent::ColliderCompChanged);
}

void SphereColliderTriggerChange::Undo()
{
	Command::Undo();
	SphereColliderComponent* pComp(BaseComponent::GetComponent<SphereColliderComponent>(m_ID));
	pComp->SetTrigger(!m_New);
	Notify(OVLEvent::ColliderCompChanged);
}
