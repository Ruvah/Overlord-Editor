#include "stdafx.h"
#include "TrnsfCompScaleChangeCmd.h"
#include <TransformComponent.h>
TrnsfCompScaleChangeCmd::TrnsfCompScaleChangeCmd(DirectX::XMFLOAT3 newscale, TransformComponent * pTrnsf) :
	m_ID{ pTrnsf->GetID() },
	m_New{ newscale },
	m_Old{pTrnsf->GetScale()}
{
}
void TrnsfCompScaleChangeCmd::Execute()
{
	Command::Execute();
	TransformComponent* pTransf(BaseComponent::GetComponent<TransformComponent>(m_ID));
	pTransf->Scale(m_New);
}

void TrnsfCompScaleChangeCmd::Undo()
{
	Command::Undo();
	TransformComponent* pTransf(TransformComponent::GetComponent<TransformComponent>(m_ID));
	pTransf->Scale(m_Old);
	Notify(OVLEvent::TransformCompChanged);
}
