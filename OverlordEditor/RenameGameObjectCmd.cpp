#include "stdafx.h"
#include "RenameGameObjectCmd.h"
#include <GameObject.h>




RenameGameObjectCmd::RenameGameObjectCmd(UINT tagID, QString newName):
	m_TagID(tagID),m_NewName(newName)
{
}

RenameGameObjectCmd::~RenameGameObjectCmd()
{
}

void RenameGameObjectCmd::Execute()
{
	Command::Execute();

	m_pGameObject = GameObject::GetGameObject(m_TagID);

	m_OldName = QString::fromStdWString(m_pGameObject->GetTag());
	m_pGameObject->SetTag(m_NewName.toStdWString());
	Notify(OVLEvent::GameObjectNameChange, this);
}




void RenameGameObjectCmd::Undo()
{
	Command::Undo();

	m_pGameObject = GameObject::GetGameObject(m_TagID);

	m_pGameObject->SetTag(m_OldName.toStdWString());
	Notify(OVLEvent::GameObjectNameChange, this);
}

GameObject * RenameGameObjectCmd::GetGameObject()
{
	return m_pGameObject;
}
