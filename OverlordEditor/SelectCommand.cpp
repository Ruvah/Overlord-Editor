#include "stdafx.h"
#include "SelectCommand.h"



SelectCommand::SelectCommand(UINT currentObj, UINT newObj):
	m_NewObj(newObj),m_PrevObj(currentObj),m_Curr(newObj)
{
}

void SelectCommand::Execute()
{
	Command::Execute();
	m_Curr = m_NewObj;
	Notify(OVLEvent::GameObjectSelected, this);
}

void SelectCommand::Undo()
{
	Command::Undo();

	m_Curr = m_PrevObj;
	Notify(OVLEvent::GameObjectSelected, this);

}
