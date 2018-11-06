#include "stdafx.h"
#include "TrnsfCompRotChangeCmd.h"
#include <TransformComponent.h>


TrnsfCompRotChangeCmd::TrnsfCompRotChangeCmd(DirectX::XMFLOAT3 newrot, TransformComponent * pTrnsf):
	m_ID{ pTrnsf->GetID() },
	m_New{ newrot },
	m_Old{pTrnsf->GetRotationEuler()}
{
}
void TrnsfCompRotChangeCmd::Execute()
{
	Command::Execute();
	TransformComponent* pTransf(BaseComponent::GetComponent<TransformComponent>(m_ID));
	pTransf->Rotate(m_New,true);
	Notify(OVLEvent::TransformCompChanged);
}

void TrnsfCompRotChangeCmd::Undo()
{
	Command::Undo();
	TransformComponent* pTransf(TransformComponent::GetComponent<TransformComponent>(m_ID));
	pTransf->Rotate(m_Old,true);
	Notify(OVLEvent::TransformCompChanged);
}