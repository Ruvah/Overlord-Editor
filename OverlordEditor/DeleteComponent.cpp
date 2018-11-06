#include "stdafx.h"
#include "DeleteComponent.h"
#include <ComponentInspector.h>




DeleteComponent::DeleteComponent(ComponentInspector * pInsp):
	m_ID{pInsp->GetID()}
{
}

DeleteComponent::~DeleteComponent()
{
	auto pComp =BaseComponent::GetComponent<BaseComponent>(m_ID);
	if (pComp)
		delete pComp;
}

void DeleteComponent::Execute()
{
	Command::Execute();


	Notify(OVLEvent::ComponentDeleted, this);
}

void DeleteComponent::Undo()
{
	Command::Undo();


	Notify(OVLEvent::ComponentAdded, this);
}
