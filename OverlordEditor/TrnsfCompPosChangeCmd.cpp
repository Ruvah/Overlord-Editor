#include "stdafx.h"
#include "TrnsfCompPosChangeCmd.h"
#include <TransformComponent.h>
TrnsfCompPosChangeCmd::TrnsfCompPosChangeCmd(DirectX::XMFLOAT3 newPos, TransformComponent * pTrnsf):
	m_ID{pTrnsf->GetID()},
	m_New{newPos},
	m_Old{pTrnsf->GetPosition()}
{
}
void TrnsfCompPosChangeCmd::Execute()
{
	Command::Execute();
	TransformComponent* pTransf (BaseComponent::GetComponent<TransformComponent>(m_ID));
	pTransf->Translate(m_New);
	Notify(OVLEvent::TransformCompChanged);

}

void TrnsfCompPosChangeCmd::Undo()
{
	Command::Undo();
	TransformComponent* pTransf(TransformComponent::GetComponent<TransformComponent>(m_ID));
	pTransf->Translate(m_Old);
	Notify(OVLEvent::TransformCompChanged);
}
